## 万能的 function 容器

std::function 采用了**类型擦除技术**，无需写明仿函数类的具体类型，能容纳任何仿函数或函数指针。

只需在模板参数中写明函数的参数和返回值类型即可，所有具有同样参数和返回值类型的仿函数或函数指针都可以传入。

```cpp
struct twice_t {
    int operator() (int i) {
        return i * 2;
    }
};

function<int (int)> twice = twice_t();  // 没问题，能接受仿函数


int triple(int i) {
    return i * 3;
}

function<int (int)> function_triple = triple; // 没问题，能接受函数指针


struct ntimes_t {
    int scale;

    ntimes_t(int scale) : scale(scale) {}

    int operator() (int i) {
        return i * scale;
    }
};

function<int (int)> quadric = ntimes_t(4); // 没问题，能接受带状态的仿函数
```

可以用 function 容器作为参数，就可以避免使用模板。

```cpp
// 模板：性能优先
template <class Func>
void test(Func func) {
    cout << func(2);
    cout << func(3);
}

// 容器：灵活性优先
void test(function<int (int)> func) {
    cout << func(2);
    cout << func(3);
}
```
