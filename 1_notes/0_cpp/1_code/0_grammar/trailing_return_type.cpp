#include <iostream>

void f(...) { std::cout << "fallback\n"; }

template <class T>
auto f(T t) -> decltype((void)(t.x), void()) {
    std::cout << "has x member\n";
}

struct A {
    int x;
};
struct B {};

int main() {
    f(A{});  // 输出 "has x member\n"
    f(B{});  // 输出 "fallback\n"
    return 0;
}

/*
在现代C++中，尾置返回类型（trailing return type）主要用于以下几种情况：

1. 当返回类型依赖于函数参数类型时，尤其是在模板函数中，这可以提供更清晰的语法。
2. 在Lambda表达式中，尤其是当返回类型不容易直接推断时。
3. 当函数返回类型较复杂时，使用尾置返回类型可以提高代码的可读性。
*/