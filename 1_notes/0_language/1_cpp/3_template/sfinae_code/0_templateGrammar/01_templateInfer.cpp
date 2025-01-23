// 理解模板类型推导
// 模板类型推导是 C++ 中强大的功能，能够根据调用的实参推导出模板的类型。常见的类型推导方式包括指针、引用、通用引用和传值。

#include <cstddef>
#include <iostream>

namespace Template_Type_Infer {
    // 指针或引用类型
    template <typename T>
    void f(T& param) {
        std::cout << "\tT is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }

    // 通用引用类型
    template <typename T>
    void g(T&& param) {
        std::cout << "\tT is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }

    // 传值类型
    template <typename T>
    void h(T param) {
        std::cout << "\tT is " << typeid(T).name() << ", param is "
                  << typeid(param).name() << std::endl;
    }

    void test() {
        std::cout << "Test Template Type Infer for [1] :" << std::endl;
        // Template_Type_Infer::f(1);  // T是int，param类型为int&&
        Template_Type_Infer::g(1);  // T是int，param类型为int&&
        Template_Type_Infer::h(1);  // T是int，param类型为int&&

        std::cout << "Test Template Type Infer for [int x] :" << std::endl;
        int x = 1;
        Template_Type_Infer::f(x);  // T是int，param类型为int&
        Template_Type_Infer::g(x);  // T是int&，param类型为int&
        Template_Type_Infer::h(x);  // T是int，param类型为int

        std::cout << "Test Template Type Infer for [const int x] :"
                  << std::endl;
        const int cx = x;
        Template_Type_Infer::f(cx);  // T是const int，param类型为const int&
        Template_Type_Infer::g(cx);  // T是const int&，param类型为const int&
        Template_Type_Infer::h(cx);  // T是int，param类型为int

        std::cout << "Test Template Type Infer for [const int& x] :"
                  << std::endl;
        const int& rx = x;
        Template_Type_Infer::f(rx);  // T是const int，param类型为const int&
        Template_Type_Infer::g(rx);  // T是const int&，param类型为const int&
        Template_Type_Infer::h(rx);  // T是int，param类型为int
    }
}  // namespace Template_Type_Infer

namespace Template_Ptr_Infer {

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

    // template <typename T1, typename T2, typename T3>
    // constexpr void test(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1,
    //                     T2& x2, T3&& x3) {
    //     static_assert(A<decltype(a1)>::value == 5);  // A<T*>
    //     static_assert(A<decltype(a2)>::value == 5);  // A<T*>
    //     static_assert(A<decltype(a3)>::value == 2);  // A<T(&)[N]>
    //     static_assert(A<decltype(x0)>::value == 4);  // A<T(&)[]>
    //     static_assert(A<decltype(x1)>::value == 5);  // A<T*>
    //     static_assert(A<decltype(x2)>::value == 4);  // A<T(&)[]>
    //     static_assert(A<decltype(x3)>::value == 4);  // A<T(&)[]>
    // }

    // void test() {
    //     int a[42];
    //     static_assert(Template_Ptr_Infer::A<decltype(a)>::value == 1);
    //     extern int x[];  // 传引用时将变为 int(&)[]
    //     static_assert(Template_Ptr_Infer::A<decltype(x)>::value ==
    //                   3);  // A<T[]>
    //     Template_Ptr_Infer::test(a, a, a, x, x, x, x);
    // }
}  // namespace Template_Ptr_Infer

int main() {
    Template_Type_Infer::test();
    // Template_Ptr_Infer::test();
    return 0;
}