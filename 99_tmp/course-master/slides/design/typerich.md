
## span “胖指针”
---
---
---

假如你手一滑，或者老板需求改变，把 buf 缓冲区少留了两个字节：
```cpp
char buf[30];
read(fd, buf, 32);
```
但你 read 的参数依然是 32，就产生了数组越界，又未定义行为了。

我们采用封装精神，把相关的 buf 和 size 封装成一个参数：
```cpp
struct Span {
    char *data;
    size_t size;
};

ssize_t read(FileHandle fd, Span buf);
```

```cpp
read(fd, Span{buf, 32});
```

注意：Span 不需要以引用形式传入函数！
```cpp
void read(std::string &buf);  // 如果是 string 类型，参数需要为引用，才能让 read 能够修改 buf 字符串
void read(Span buf);          // Span 不需要，因为 Span 并不是独占资源的类，Span 本身就是个轻量级的引用
```
vector 和 string 这种具有“拷贝构造函数”的 RAII 封装类才需要传入引用 `string &buf`，如果直接传入会发生深拷贝，导致 read 内部修改的是 string 的一份拷贝，无法影响到外界原来的 string。
如果是 Span 参数就不需要 `Span &buf` 引用了，Span 并不是 RAII 封装类，并不持有生命周期，并没有“拷贝构造函数”，他只是个对外部已有 vector、string、或 char[] 的引用。或者说 Span 本身就是一个对原缓冲区的引用，直接传入 read 内部一样可以修改你的缓冲区。

---
---
---

用 Span 结构体虽然看起来更明确了，但是依然不解决用户可能手滑写错缓冲区长度的问题：
```cpp
char buf[30];
read(fd, Span{buf, 32});
```

为此，我们在 Span 里加入一个隐式构造函数：
```cpp
struct Span {
    char *data;
    size_t size;

    template <size_t N>
    Span(char (&buf)[N]) : data(buf), size(N) {}
};
```
这将允许 char [N] 隐式转换为 Span，且长度自动就是 N 的值。

此处如果写 `Span(char buf[N])`，会被 C 语言的某条沙雕规则，函数签名会等价于 `Span(char *buf)`，从而只能获取起始地址，而推导不了长度。使用数组引用作为参数 `Span(char (&buf)[N])` 就不会被 C 语言自动退化成起始地址指针了。

用户只需要：
```cpp
char buf[30];
read(fd, Span{buf});
```
等价于 `Span{buf, 30}`，数组长度自动推导，非常方便。

由于我们是隐式构造函数，还可以省略 Span 不写：
```cpp
char buf[30];
read(fd, buf);  // 自动转换成 Span{buf, 30}
```

加入更多类型的支持：
```cpp
struct Span {
    char *data;
    size_t size;

    template <size_t N>
    Span(char (&buf)[N]) : data(buf), size(N) {}

    template <size_t N>
    Span(std::array<char, N> &arr) : data(arr.data()), size(N) {}

    Span(std::vector<charN> &vec) : data(vec.data()), size(vec.size()) {}

    // 如果有需要，也可以显式写出 Span(buf, 30) 从首地址和长度构造出一个 Span 来
    explicit Span(char *data, size_t size) : data(data), size(size) {}
};
```

现在 C 数组、array、vector、都可以隐式转换为 Span 了：
```cpp
char buf1[30];
Span span1 = buf1;

std::array<char, 30> buf2;
Span span2 = buf2;

std::vector<char> buf(30);
Span span3 = buf3;

const char *str = "hello";
Span span4 = Span(str, strlen(str));
```

运用模板元编程，自动支持任何具有 data 和 size 成员的各种标准库容器，包括第三方的，只要他提供 data 和 size 函数。
```cpp
template <class Arr>
concept has_data_size = requires (Arr arr) {
    { arr.data() } -> std::convertible_to<char *>;
    { arr.size() } -> std::same_as<size_t>;
};

struct Span {
    char *data;
    size_t size;

    template <size_t N>
    Span(char (&buf)[N]) : data(buf), size(N) {}

    template <has_data_size Arr>
    Span(Arr &&arr) : data(arr.data()), size(arr.size()) {}
    // 满足 has_data_size 的任何类型都可以构造出 Span
    // 而标准库的 vector、string、array 容器都含有 .data() 和 .size() 成员函数
};
```

---
---
---

如果用户确实有修改长度的需要，可以通过 subspan 成员函数实现：
```cpp
char buf[32];
read(fd, Span(buf).subspan(0, 10));  // 只读取前 10 个字节！
```

subspan 内部实现原理：
```cpp
struct Span {
    char *data;
    size_t size;

    Span subspan(size_t start, size_t length = (size_t)-1) const {
        if (start > size)  // 如果起始位置超出范围，则抛出异常
            throw std::out_of_range("subspan start out of range");
        auto restSize = size - start;
        if (length > restSize) // 如果长度超过上限，则自动截断
            length = restSize;
        return Span(data + start, restSize + length);
    }
};
```

---
---
---

可以把 Span 变成模板类，支持任意类型的数组，比如 `Span<int>`。
```cpp
template <class Arr, class T>
concept has_data_size = requires (Arr arr) {
    { std::data(arr) } -> std::convertible_to<T *>;
    { std::size(arr) } -> std::same_as<size_t>;
    // 使用 std::data 而不是 .data() 的好处：
    // std::data 对于 char (&buf)[N] 这种数组类型也有重载！
    // 例如 std::size(buf) 会得到 int buf[N] 的正确长度 N
    // 而 sizeof buf 会得到 N * sizeof(int)
    // 类似于 sizeof(buf) / sizeof(buf[0]) 的效果
    // 不过如果 buf 是普通 int * 指针，会重载失败，直接报错，没有安全隐患
};

template <class T>
struct Span {
    T *data;
    size_t size;

    template <has_data_size<T> Arr>
    Span(Arr &&arr) : data(std::data(arr)), size(std::size(arr)) {}
    // 👆 同时囊括了 vector、string、array、原始数组
};

template <has_data_size Arr>
Span(Arr &&t) -> Span<std::remove_pointer_t<decltype(std::data(std::declval<Arr &&>()))>>;
```

---
---
---

`Span<T>` 表示可读写的数组。
对于只读的数组，用 `Span<const T>` 就可以。
```cpp
ssize_t read(FileHandle fd, Span<char> buf);         // buf 可读写！
ssize_t write(FileHandle fd, Span<const char> buf);  // buf 只读！
```

---
---
---

好消息！这东西在 C++20 已经实装，那就是 std::span。
没有 C++20 开发环境的同学，也可以用 GSL 库的 gsl::span，或者 ABSL 库的 absl::Span 来体验。

C++17 还有专门针对字符串的区间类 std::string_view，可以从 std::string 隐式构造，用法类似，不过切片函数是 substr，还支持 find、find_first_of 等 std::string 有的字符串专属函数。

* `std::span<T>` - 任意类型 T 的可读可写数组
* `std::span<const T>` - 任意类型 T 的只读数组
* `std::string_view` - 任意字符串

在 read 函数内部，可以用 .data() 和 .size() 重新取出独立的首地址指针和缓冲区长度，用于伺候 C 语言的老函数：
```cpp
ssize_t read(FileHandle fd, std::span<char> buf) {
    memset(buf.data(), 0, buf.size());  // 课后作业，用所学知识，优化 C 语言的 memset 函数吧！
    ...
}
```

也可以用 range-based for 循环来遍历：
```cpp
ssize_t read(FileHandle fd, std::span<char> buf) {
    for (auto & c : buf) {  // 注意这里一定要用 auto & 哦！否则无法修改 buf 内容
        c = 'c';
        ...
    }
}
```
---
---
---
