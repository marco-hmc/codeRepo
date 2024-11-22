
## 拒绝指针！

注意，这里 foo 返回了一个指针！
```cpp
BookInfo * foo(ISBN isbn);
```

他代表什么意思呢？

1. 指向一个内存中已经存在的书目项，由 foo 负责管理这片内存
2. 返回一个 new 出来的 BookInfo 结构体，由用户负责 delete 释放内存
3. 是否还有可能返回 NULL 表示找不到的情况？
4. 甚至有可能返回的是一个 BookInfo 数组？指针指向数组的首个元素，数组长度的判定方式未知...

太多歧义了！

```cpp
BookInfo & foo(ISBN isbn);
```
这就很清楚，foo 会负责管理 BookInfo 对象的生命周期，用户获得的只是一个临时的引用，并不持有所有权。

引用的特点：

1. 一定不会是 NULL（排除可能返回 NULL 的疑虑）
2. 无法 delete 一个引用（排除可能需要用户负责释放内存的疑虑）
3. 不会用于表示数组（排除可能返回数组首元素指针的疑虑）

改用引用返回值，一下子思路就清晰了很多。没有那么多怀疑和猜测了，用途单一，用法明确，引用真是绝绝子。

```cpp
std::unique_ptr<BookInfo> foo(ISBN isbn);
```
这就很清楚，foo 创建了一个新的 BookInfo，并把生命周期的所有权移交给了用户。

unique_ptr 的特点：

1. 独占所有权，不会与其他线程共享（排除可能多线程竞争的疑虑）
2. 生命周期已经移交给用户，unique_ptr 变量离开用户的作用域后会自动释放，无需手动 delete
3. 不会用于表示数组（如果要表示数组，会用 `unique_ptr<BookInfo[]>` 或者 `vector<BookInfo>`）

但是 unique_ptr 有一个致命的焦虑点：他可以为 NULL！
所以当你看到一个函数返回 unique_ptr 或 shared_ptr，尽管减少了很多的疑虑，但“可能为NULL”的担忧仍然存在！
要么 foo 的作者在注释或文档里写明，“foo 不会返回 NULL”或者“foo 找不到时会返回 NULL”，打消你的疑虑。
但我们的诉求是通过类型，一眼就能看出函数所有的可能性，而不要去依赖可能骗人的注释。

为此微软实现了 [gsl](https://github.com/microsoft/GSL) 库，通过类型修饰解决指针类语义含糊不清的问题：
他规定，所有套了一层 `gsl::not_null` 的原始指针或智能指针，里面都必然不会为 NULL。
在 not_null 类的构造函数中，有相应的断言检查传入的指针是否为空，如果为空会直接报错退出。
```cpp
gsl::not_null<FILE *> p = nullptr;      // 编译期报错，因为他里面写着 not_null(nullptr_t) = delete;
gsl::not_null<FILE *> p = fopen(...);   // 如果 fopen 打开失败，且为 Debug 构建，运行时会触发断言错误
```

修改后的函数接口如下：
```cpp
gsl::not_null<std::unique_ptr<BookInfo>> foo(ISBN isbn);
```
因为 gsl::not_null 的构造函数中会检测空指针，就向用户保证了我返回的不会是 NULL。

但是，有没有一种可能，你如果要转移所有权的话，我直接返回 BookInfo 本身不就行了？
除非 BookInfo 特别大，大到移动返回的开销都不得了。
直接返回类型本身，就是一定不可能为空的，且也能说明移交了对象所有权给用户。
```cpp
BookInfo foo(ISBN isbn);
```

---
---
---

其实 GSL 里大量都是这种可有可无的玩意，比如 C++20 已经有了 std::span 和 std::byte，但是 GSL 还给你弄了个 gsl::span 和 gsl::byte，主要是为了兼容低版本编译器，如果你在新项目里能直接用上 C++20 标准的话，个人不是很推荐再去用了。

再比如 gsl::czstring 是 const char * 的类型别名，明确表示“0结尾字符串”，为的是和“指针返回仙人”区分开来，有必要吗？有没有一种可能，我们现在 const char * 基本上就“0结尾字符串”一种用法，而且我们大多也都是用 string 就可以了，const char * 又不安全，又语义模棱两可，何必再去为了用它专门引入个库，整个类型别名呢？
```cpp
using czstring = const char *;

void foo(czstring s) {          // 发明 GSL 的人真是个天才！
    if (s == "小彭老师")        // 错误！
    if (strcmp(s, "小彭老师"))  // 错误！
    if (!strcmp(s, "小彭老师")) // 终于正确
    // 然而我完全可以直接用 string，== 的运算符重载能直接比较字符串内容
    // 还能随时随地 substr 切片，find 查找，size 常数复杂度查大小
}
```
---

## 强类型封装

假设你正在学习这个 Linux 系统 API 函数：
```cpp
ssize_t read(int fd, char *buf, size_t len);
// fd - 文件句柄，int 类型
```

但是你没有看他的函数参数类型和名字。你是这样调用的：
```cpp
int fd = open(...);
char buf[32];
read(32, buf, fd);
char buf[32];
read(32, buf, fd);
```

你这里的 32 本意是缓冲区的大小，却不幸地和 fd 参数写错了位置，而编译器毫无报错，你浑然不知。

---
---
---

仅仅只是装模作样的用 typedef 定义个好看的类型别名，并没有任何意义！
他连你的参数名 fd 都能看不见，你觉得他会看到你的参数类型是个别名？

用户一样可以用一个根本不是文件句柄的臭整数来调用你，而得不到任何警告或报错：
```cpp
typedef FileHandle int;
ssize_t read(FileHandle fd, char *buf, size_t len);

read(32, buf, fd); // 照样编译通过！
```

如果我们把文件句柄定义为一个结构体：
```cpp
struct FileHandle {
    int handle;

    explicit FileHandle(int handle) : handle(handle) {}
};

ssize_t read(FileHandle handle, char *buf, size_t len);
```

就能在用户犯马虎的时候，给他弹出一个编译错误：
```cpp
read(32, buf, fd);  // 编译报错：无法将 int 类型的 32 隐式转换为 FileHandle！
```

对于整数类型，也有的人喜欢用 C++11 的强类型枚举：
```cpp
enum class FileHandle : int {};
```

这样一来，如果用户真的是想要读取“32号句柄”的文件，他就必须显式地写出完整类型才能编译通过：
```cpp
read(FileHandle(32), buf, fd);  // 编译通过了
```
强迫你写上类型名，就给了你一次再思考的机会，让你突然惊醒：
哦天哪，我怎么把缓冲区大小当成句柄来传递了！
从而减少睁着眼睛还犯错的可能。

然后，你的 open 函数也返回 FileHandle，整个代码中就不用强制类型转换了。
```cpp
FileHandle fd = open(std::filesystem::path("路径"), OpenFlag::Read);
char buf[32];
read(fd, buf, 32);
```

---
---
---

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

## 空值语义

---
---
---

有的函数，比如刚才的 foo，会需要表示“可能找不到该书本”的情况。
粗糙的 API 设计者会返回一个指针，然后在文档里说“这个函数可能会返回 NULL！”
```cpp
BookInfo *foo(ISBN isbn);
```
如果是这样的函数签名，是不是你很容易忘记 foo 有可能返回 NULL 表示“找不到书本”？

比如 `malloc` 函数在分配失败时，就会返回 NULL 并设置 errno 为 ENOMEM。
在 `man malloc` 文档中写的清清楚楚，但是谁会记得这个设定？
malloc 完随手就直接访问了（空指针解引用属未定义行为）。

在现代 C++17 中引入了 optional，他是个模板类型。
形如 `optional<T>` 的类型有两种可能的状态：

1. 为空（nullopt）
2. 有值（T）

如果一个函数可能成功返回 T，也可能失败，那就可以让他返回 `optional<T>`，用 nullopt 来表示失败。
```cpp
std::optional<BookInfo> foo(ISBN isbn) {
    if (找到了) {
        return BookInfo(...);
    } else {
        return std::nullopt;
    }
}
```
nullopt 和指针的 nullptr 类似，但 optional 的用途更加单一，更具说明性。
如果你返回个指针人家不一定知道你的意思是可能返回 nullptr，可能还以为你是为了返回个 new 出来的数组，语义不明确。

调用的地方这样写：
```cpp
auto book = foo(isbn);
if (book.has_value()) {  // book.has_vlaue() 为 true，则表示有值
    BookInfo realBook = book.value();
    print("找到了:", realBook);
} else {
    print("找不到这本书");
}
```

optional 类型可以在 if 条件中自动转换为 bool，判断是否有值，等价于 `.has_value()`：
```cpp
auto book = foo(isbn);
if (book) {  // (bool)book 为 true，则表示有值
    BookInfo realBook = book.value();
    print("找到了:", realBook);
} else {
    print("找不到这本书");
}
```

可以通过 * 运算符读取其中的值，等价于 `.value()`）：
```cpp
auto book = foo(isbn);
if (book) {
    BookInfo realBook = *book;
    print("找到了:", realBook);
} else {
    print("找不到这本书");
}
```

运用 C++17 的就地 if 语法：
```cpp
if (auto book = foo(isbn); book.has_value()) {
    BookInfo realBook = *book;
    print("找到了:", realBook);
} else {
    print("找不到这本书");
}
```

由于 auto 出来的 optional 变量可以转换为 bool，分号后面的条件可以省略：
```cpp
if (auto book = foo(isbn)) {
    print("找到了:", *book);
} else {
    print("找不到这本书");
}
```

optional 也支持 `->` 运算符访问成员：
```cpp
if (auto book = foo(isbn)) {
    print("找到了:", book->name);
    book->readOnline();
}
```

optional 的 `.value()`，如果没有值，会抛出 `std::bad_optional_access` 异常。
用这个方法可以便捷地把“找不到书本”转换为异常抛出给上游调用者，而不用成堆的 if 判断和返回。
```cpp
BookInfo book = foo(isbn).value();
```

也可以通过 `.value_or(默认值)` 指定“找不到书本”时的默认值：
```cpp
BookInfo defaultBook;
BookInfo book = foo(isbn).value_or(defaultBook);
```

---
---
---

你接手了一个字符串转整数（可能转换失败）的函数 API：
```cpp
// 文档：如果字符串解析失败，会返回 -1 并设置 errno 为 EINVAL！记得检查！若你忘记检查后果自负！
// 当指定 n 为 0 时，str 为 C 语言经典款 0 结尾字符串。
// 当指定 n 不为 0 时，str 的长度固定为 n，用于照顾参数可能不为 0 结尾字符串的情况。
int parseInt(const char *str, size_t n);
```
那么我如果检测到 -1，鬼知道是字符串里的数字就是 -1，还是因为出错才返回 -1？还要我去检查 errno，万一上一个函数出错留下的 EINVAL 呢？万一我忘记检查呢？

运用本期课程所学知识优化：
```cpp
std::optional<int> parseInt(std::string_view str);
```
是不是功能，返回值，可能存在的错误情况，一目了然了？根本不需要什么难懂的注释，文档。

如果调用者想假定字符串解析不会出错：
```cpp
parseInt("233").value();
```

如果调用者想当出错时默认返回 0：
```cpp
parseInt("233").value_or(0);
```

parseInt 内部实现可能如下：
```cpp
std::optional<int> parseInt(std::string_view sv) {
    int value;
    auto result = std::from_chars(str.data(), str.data() + str.size(), std::ref(value));
    if (result.ec == std::errc())
        return value;
    else
        return std::nullopt;
}
```

---
---
---

调用者的参数不论是 string 还是 C 语言风格的 const char *，都能隐式转换为通用的 string_view。
```cpp
parseInt("-1");

string s;
cin >> s;
parseInt(s);

char perfGeek[2] = {'-', '1'};
parseInt(std::string_view{perfGeek, 2});
```

笑点解析：上面的代码有一处错误，你能发觉吗？

---
---
---

```cpp
cin >> s;
```

`cin >>` 可能会失败！没 想 到 吧

要是 int 等 POD 类型，如果不检测，会出现未初始化的 int 值，产生未定义行为！
```cpp
int i;
cin >> i;
return i;  // 如果用户的输入值不是合法的整数，这里会产生典中典之内存中的随机数烫烫烫烤馄饨！
```

官方推荐的做法是每次都要检测是否失败！
```cpp
int i;
if (!(cin >> i)) {
    throw std::runtime_error("读入 int 变量失败！");
}
return i;
```

但是谁记得住？所以从一开始就不要设计这种糟糕的 API。
特别是 `cin >>` 这种通过引用返回 i，却要人记得判断返回 bool 表示成败，忘记判断还会给你留着未初始化的煞笔设计。
如果让我来设计 cin 的话：
```cpp
std::optional<int> readInt();

int i = cin.readInt().value();
```
这样如果用户要读取到值的话，必然要 `.value()`，从而如果 readInt 失败返回的是 nullopt，就必然抛出异常，避免了用户忘记判断错误的可能。

> 在小彭老师自主研发的一款 co_async 协程库中，重新设计了异步的字符流，例如其中 getline 函数会返回 `std::expected<std::string, std::system_error>`。

---
---
---

```cpp
BookInfo * foo(ISBN isbn);
```
这是个返回智能指针的函数，单从函数声明来看，你能否知道他有没有可能返回空指针？不确定。

```cpp
std::optional<BookInfo *> foo(ISBN isbn);
```
现在是不是很明确了，如果返回的是 nullopt，则表示空，然后 optional 内部的 BookInfo *，大概是不会为 NULL 的？

```cpp
std::optional<gsl::not_null<BookInfo *>> foo(ISBN isbn);
```
这下更明确了，如果返回的是 nullopt，则表示空，然后 optional 内部的 BookInfo * 因为套了一层 gsl::not_null，必定不能为 NULL（否则会被 gsl::not_null 的断言检测到），函数的作者是绝对不会故意返回个 NULL 的。
如果失败，会返回 nullopt，而不是意义不明还容易忘记的空指针。

---
---

还是不建议直接用原始指针，建议用智能指针或引用。
```cpp
std::optional<gsl::not_null<std::unique_ptr<BookInfo>>> foo(ISBN isbn);
```
这个函数可能返回 nullopt 表示失败，成功则返回一个享有所有权的独占指针，指向单个对象。

小彭老师，我 `optional<BookInfo &>` 出错了怎么办？
```cpp
std::optional<std::reference_wrapper<BookInfo>> foo(ISBN isbn);
```
这个函数可能返回 nullopt 表示失败，成功则返回一个不享有所有权的引用，指向单个对象。

reference_wrapper 是对引用的包装，可隐式转换为引用：
```cpp
int i;
std::reference_wrapper<int> ref = i;
int &r = ref; // r 指向 i
```
使引用可以存到各种容器里：
且遇到 auto 不会自动退化（decay）：
```cpp
int i;
std::reference_wrapper<int> ref = i;
auto ref2 = ref;  // ref2 推导为 std::reference_wrapper<int>
int &r = i;
auto r2 = r;  // r2 推导为 int
```
且永远不会为 NULL：
```cpp
std::reference_wrapper<int> ref; // 编译错误：引用必须初始化，reference_wrapper 当然也必须初始化
```
也可以通过 `*` 或 `->` 解引用：
```cpp
BookInfo book;
std::reference_wrapper<int> refBook = book;
refBook->readOnline();
BookInfo deepCopyBook = *refBook;
```

---
---
---

注意 `.value()` 和 `*` 是有区别的，`*` 不会检测是否为空，不会抛出异常，但更高效。
```cpp
o.value(); // 如果 o 里没有值，会抛出异常
*o;  // 如果 o 里没有值，会产生未定义行为！
o->readOnline();  // 如果 o 里没有值，会产生未定义行为！
```

因此一般会在判断了 optional 不为空以后才会去访问 `*` 和 `->`。而 `.value()` 可以直接访问。
```cpp
print(foo().value()); // .value() 可以直接使用，不用判断
if (auto o = foo()) {
    // 判断过确认不为空了，才能访问 *o
    // 在已经判断过不为空的 if 分支中，用 * 比 .value() 更高效
    print(*o);
}
```

共享所有权
* n - shared_ptr<T[]>
* 1 - shared_ptr<T>

独占所有权
* n - vector<T>, unique_ptr<T[]>
* 1 - unique_ptr<T>

没所有权
* n - span<T>
* 1 - reference_wrapper<T>, T &

---
---
---

接下来介绍 optional 的一些进阶用法。

```cpp
std::optional<BookInfo> o = BookInfo(1, 2, 3);  // 初始化为 BookInfo 值
std::optional<BookInfo> o;  // 不写时默认初始化为空，等价于 o = std::nullopt
o.emplace(1, 2, 3);  // 就地构造，等价于 o = BookInfo(1, 2, 3); 但不需要移动 BookInfo 了
o.reset();  // 就地销毁，等价于 o = std::nullopt;
```

---
---
---

当不为空时将其中的 int 值加 1，否则保持为空不变，怎么写？
```cpp
std::optional<int> o = cin.readInt();
if (o) {
    o = *o + 1;
}
```

运用 C++23 引入的新函数 transform：
```cpp
std::optional<int> o = cin.readInt();
o = o.transform([] (int n) { return n + 1; });
```

---
---
---

当不为空时将其中的 string 值解析为 int，否则保持为空不变。且解析函数可能失败，失败则也要将 optional 置为空，怎么写？
```cpp
std::optional<string> o = cin.readLine();
std::optional<int> o2;
if (o) {
    o2 = parseInt(*o);
}

std::optional<int> parseInt(std::string_view sv) { ... }
```

运用 C++23 引入的新函数 and_then：
```cpp
auto o = cin.readLine().and_then(parseInt);
```

---
---
---

当找不到指定书籍时，返回一本默认书籍作为替代：
```cpp
auto o = findBook(isbn).value_or(getDefaultBook());
```

缺点：由于 value_or 的参数会提前被求值，即使 findBook 成功找到了书籍，也会执行 getDefaultBook 函数，然后将其作为死亡右值丢弃。如果创建默认书籍的过程很慢，那么就非常低效。

为此，C++23 引入了 or_else 函数。
只有 findBook 找不到时才会执行 lambda 中的函数体：
```cpp
auto o = findBook(isbn).or_else([] -> std::optional<BookInfo> {
    cout << "findBook 出错了，现在开始创建默认书籍，非常慢\n";
    return getDefaultBook();
});
```

---
---
---

此类函数都可以反复嵌套：
```cpp
int i = cin.readLine()
    .or_else(getDefaultLine)
    .and_then(parseInt)
    .transform([] (auto i) { return i * 2; })
    .value_or(0);
```
加入函数式神教吧，函门！

---
---
---


## 枚举类型
小彭老师，我很喜欢强类型枚举这一套，但我的参数不是整数类型，而是 double、string 等类型，怎么办？

```cpp
struct Name {
private:
    std::string value;

public:
    explicit operator std::string() const {
        return value;
    }

    explicit Name(std::string value) : value(value) {}
};
```
这里我们写 explicit 就可以阻止隐式类型转换，起到与强类型枚举类似的作用。

或者运用模板元编程：
```cpp
// 此处使用 CRTP 模式是为了让 Typed 每次都实例化出不同的基类，阻止 object-slicing
template <class CRTP, class T>
struct Typed {
protected:
    T value;

public:
    explicit operator T() const {
        return value;
    }

    explicit Typed(T value) : value(value) {}
};
```

```cpp
struct Name : Typed<Name, T> {};

struct Meter : Typed<Meter, double> {};

struct Kilometer : Typed<Kilometer, double> {
    operator Meter() const {
        // 允许隐式转换为米
        return Meter(value * 1000);
    }
};

Meter m = Kilometer(1);
// m = Meter(1000);
foo(m);
```
