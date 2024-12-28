// 理解模板类型推导
// 模板类型推导是 C++ 中强大的功能，能够根据调用的实参推导出模板的类型。常见的类型推导方式包括指针、引用、通用引用和传值。

#include <iostream>

namespace type_infer_demo {
    // 指针或引用类型
    template <typename T>
    void f(T& param) {
        std::cout << "T is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }

    // 通用引用类型
    template <typename T>
    void g(T&& param) {
        std::cout << "T is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }

    // 传值类型
    template <typename T>
    void h(T param) {
        std::cout << "T is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }
}  // namespace type_infer_demo

int main() {
    int x = 27;
    const int cx = x;
    const int& rx = x;

    // 测试指针或引用类型
    type_infer_demo::f(x);   // T是int，param类型为int&
    type_infer_demo::f(cx);  // T是const int，param类型为const int&
    type_infer_demo::f(rx);  // T是const int，param类型为const int&

    // 测试通用引用类型
    type_infer_demo::g(27);  // T是int，param类型为int&&
    type_infer_demo::g(x);   // T是int&，param类型为int&
    type_infer_demo::g(cx);  // T是const int&，param类型为const int&
    type_infer_demo::g(rx);  // T是const int&，param类型为const int&

    // 测试传值类型
    type_infer_demo::h(x);   // T是int，param类型为int
    type_infer_demo::h(cx);  // T是int，param类型为int
    type_infer_demo::h(rx);  // T是int，param类型为int

    return 0;
}