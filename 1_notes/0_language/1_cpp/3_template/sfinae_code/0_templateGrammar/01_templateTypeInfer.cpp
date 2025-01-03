// 理解模板类型推导
// 模板类型推导是 C++ 中强大的功能，能够根据调用的实参推导出模板的类型。常见的类型推导方式包括指针、引用、通用引用和传值。

#include <cstddef>
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

    void test() {
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
    }
}  // namespace type_infer_demo

/*
  ## 模板参数中的常见用法

  1. 模板参数如何接受一个带入参的模板类？
     通过模板模板参数的方式，可以接受一个带入参的模板类。
     例如，下面的 f 函数接受一个容器类，其中的元素类型为 T。
*/

namespace TemplateSpecialization {

    template <typename T>
    struct A;

    template <typename T, std::size_t N>
    struct A<T[N]> {
        static constexpr int value = 1;
    };

    template <typename T, std::size_t N>
    struct A<T (&)[N]> {
        static constexpr int value = 2;
    };

    template <typename T>
    struct A<T[]> {
        static constexpr int value = 3;
    };

    template <typename T>
    struct A<T (&)[]> {
        static constexpr int value = 4;
    };

    template <typename T>
    struct A<T*> {
        static constexpr int value = 5;
    };

    template <typename T1, typename T2, typename T3>
    constexpr void test(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1,
                        T2& x2, T3&& x3) {
        static_assert(A<decltype(a1)>::value == 5);  // A<T*>
        static_assert(A<decltype(a2)>::value == 5);  // A<T*>
        static_assert(A<decltype(a3)>::value == 2);  // A<T(&)[N]>
        static_assert(A<decltype(x0)>::value == 4);  // A<T(&)[]>
        static_assert(A<decltype(x1)>::value == 5);  // A<T*>
        static_assert(A<decltype(x2)>::value == 4);  // A<T(&)[]>
        static_assert(A<decltype(x3)>::value == 4);  // A<T(&)[]>
    }

    void test() {
        int a[42];
        static_assert(TemplateSpecialization::A<decltype(a)>::value == 1);
        extern int x[];  // 传引用时将变为 int(&)[]
        static_assert(TemplateSpecialization::A<decltype(x)>::value ==
                      3);  // A<T[]>
        TemplateSpecialization::test(a, a, a, x, x, x, x);
    }
}  // namespace TemplateSpecialization

int main() {
    type_infer_demo::test();
    TemplateSpecialization::test();
    return 0;
}