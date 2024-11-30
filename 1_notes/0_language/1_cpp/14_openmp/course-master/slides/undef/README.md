### T 类型指针必须对齐到 alignof(T)

```cpp
struct alignas(64) C { // 假设 alignof(int) 是 4
    int i;
    char c;
};

C *p = (C *)malloc(sizeof(C)); // 错！malloc 产生的指针只保证对齐到 max_align_t（GCC 上是 16 字节）大小，并不保证对齐到 C 所需的 64 字节
C *p = new C;  // 可以，new T 总是保证对齐到 alignof(T)
```

```cpp
char buf[sizeof(int)];
int *p = (int *)buf;  // 错！
```

```cpp
alignas(alignof(int)) char buf[sizeof(int)];
int *p = (int *)buf;  // 可以
```

```cpp
char buf[sizeof(int) * 2];
int *p = (int *)(((uintptr_t)buf + sizeof(int) - 1) & ~(alignof(int) - 1));  // 可以
```

### 左移或右移的位数，不得超过整数类型上限，不得为负

对于有符号整数，左移还不得破坏符号位

```cpp
int i = 0;
i << 1;   // 可以
i << 31;  // 错！
unsigned int u = 0;
u << 31; // 可以
```

如需处理来自用户输入的位移数量，可以先做范围检测

```cpp
int shift;
cin >> shift;

unsigned int u = 0;
int i = 0;
(shift > 0 && shift < 32) ? (u << shift) : 0; // 可以
(shift > 0 && shift < 31) ? (i << shift) : 0; // 可以
```

## 库函数类

### ctype.h 中一系列函数的字符参数，必须在 0~127 范围内（即只支持 ASCII 字符）

```cpp
isdigit('0');    // 可以，返回 true
isdigit('a');    // 可以，返回 false
isdigit('\xef'); // 错！结果未定义，在 MSVC 的 Debug 模式下会产生断言异常

char s[] = "你好A"; // UTF-8 编码的中文
// "你好a"？
std::transform(std::begin(s), std::end(s), std::begin(s), ::tolower); // 错！结果未定义，因为 UTF-8 编码会产生大于 128 的字节
```

MSVC STL 中 is 系列函数的断言：

`assert(-1 <= c && c < 256);`

理论上可以这样断言：

`assert(0 <= c && c <= 127);`

解决方法：要么改用 iswdigit（MSVC：0-65536，GCC：0-0x010ffff）

```cpp
iswdigit('0');       // 可以，返回 true
iswdigit('\xef');    // 可以，返回 false
iswspace(L'\ufeff'); // 可以，UTF-8 locale 时返回 true，ASCII locale 时返回 false
```

要么自己实现判断

```cpp
if ('0' <= c && c <= '9')  // 代替 isdigit(c)
if (strchr(" \n\t\r", c))  // 代替 isspace(c)
```

### memcpy 不能接受带有重叠的 src 和 dst

```cpp
char arr[10];
memcpy(arr, arr + 1, 9); // 错！有的同学，以为这个是对的？错了，memcpy 的 src 和 dst
memcpy(arr + 1, arr, 9); // 错！
memcpy(arr + 5, arr, 5); // 可以
memcpy(arr, arr + 5, 5); // 可以
```

如需拷贝带重复区间的内存，可以用 memmove

```cpp
char arr[10];
memmove(arr, arr + 1, 9); // 可以
memmove(arr + 1, arr, 9); // 可以
memmove(arr + 5, arr, 5); // 可以
memmove(arr, arr + 5, 5); // 可以
```

从 memcpy 的 src 和 dst 指针参数是 restrict 修饰的，而 memmove 没有，就可以看出来，memcpy 不允许任何形式的指针重叠，无论先后顺序

### v.back() 当 v 为空时是未定义行为

```cpp
std::vector<int> v = {};
int i = v.back();                  // 错！back() 并不会对 v 是否有最后一个元素做检查，此处相当于解引用了越界的指针
int i = v.empty() ? 0 : v.back();  // 更安全，当 v 为空时返回 0
```


## 多线程类

### 多个线程同时访问同一个对象，其中至少一个线程的访问为写访问，是未定义行为（俗称数据竞争）

```cpp
std::string s;

void t1() {
    s.push_back('a'); // 写访问，出错！
}

void t2() {
    cout << s.size(); // 读访问
}
```

```cpp
std::string s;

void t1() {
    s.push_back('a'); // 写访问，出错！
}

void t2() {
    s.push_back('b'); // 写访问，出错！
}
```

更准确的说法是：多个线程（无 happens before 关系地）访问同一个对象，其中至少一个线程的访问带有副作用（写访问或带有volatile的读访问），是未定义行为

```cpp
// 八股文教材常见的错误写法！volatile 并不保证原子性和内存序，这样写是有未定义行为的。正确的做法是改用 std::atomic<int>
volatile int ready = 0;
int data;

void t1() {
    data = 42;
    ready = 1;
}

void t2() {
    while (ready == 0)
        ;
    printf("%d\n", data);
}
```

建议利用 mutex，counting_semaphore，atomic 等多线程同步工具，保证多个线程访问同一个对象时，顺序有先有后，不会“同时”发生，那就是安全的

```cpp
std::string s;
std::mutex m;

void t1() {
    std::lock_guard l(m);
    s.push_back('a'); // 有 mutex 保护，可以
}

void t2() {
    std::lock_guard l(m);
    s.push_back('b'); // 有 mutex 保护，可以
}
```

在上面的例子中，互斥锁保证了要么 t1 happens before t2，要么 t2 happens before t1，不会“同时”访问，是安全的

```cpp
std::string s;
std::counting_semaphore<1> sem(1);

void t1() {
    s.push_back('a');
    sem.release(); // 令 t2 必须发生在 t1 之后
}

void t2() {
    sem.acquire(); // t2 必须等待 t1 release 后，才能开始执行
    s.push_back('b');
}
```

在上面的例子中，信号量保证了 t1 happens before t2，不会“同时”访问，是安全的

```cpp
std::string s;
std::atomic<bool> ready{false};

void t1() {
    s.push_back('a');
    ready.store(true, std::memory_order_release); // 令 s 的修改对其他 acquire 了 ready 的线程可见
}

void t2() {
    while (!ready.load(std::memory_order_acquire)) // t2 必须等待 t1 store 后，才能开始执行
        ;
    s.push_back('b');
}
```

在上面的例子中，原子变量的 acquire/release 内存序保证了 t1 happens before t2，不会“同时”访问，是安全的

### 多个线程同时对两个 mutex 上锁，但顺序相反，会产生未定义行为（俗称死锁）

```cpp
std::mutex m1, m2;

void t1() {
    m1.lock();
    m2.lock(); // 错！
    m2.unlock();
    m1.unlock();
}

void t2() {
    m2.lock();
    m1.lock(); // 错！
    m1.unlock();
    m2.unlock();
}
```

解决方法：不要在多个 mutex 上同时上锁，如果确实要多个 mutex，保证顺序一致

```cpp
std::mutex m1, m2;

void t1() {
    m1.lock();
    m2.lock();
    m2.unlock();
    m1.unlock();
}

void t2() {
    m1.lock();
    m2.lock();
    m2.unlock();
    m1.unlock();
}
```

或使用 std::lock

```cpp
std::mutex m1, m2;

void t1() {
    std::lock(m1, m2);
    std::unlock(m1, m2);
}

void t2() {
    std::lock(m2, m1);
    std::unlock(m2, m1);
}
```

### 对于非 recursive_mutex，同一个线程对同一个 mutex 重复上锁，会产生未定义行为（俗称递归死锁）

```cpp
std::mutex m;

void t1() {
    m.lock();
    m.lock();     // 错！
    m.try_lock(); // 错！try_lock 也不允许！
    m.unlock();
    m.unlock();
}

void t2() {
    m.try_lock(); // 可以
}
```

解决方法：改用 recursive_mutex，或使用适当的条件变量

```cpp
std::recursive_mutex m;

void t1() {
    m.lock();
    m.lock(); // 可以
    m.try_lock(); // 可以，返回 true
    m.unlock();
    m.unlock();
    m.unlock();
}
```

# 总结
- 不要重复上锁 mutex
- 仔细看库函数的文档