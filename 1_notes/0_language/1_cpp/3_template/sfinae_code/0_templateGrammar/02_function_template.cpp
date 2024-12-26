#include <cstddef>

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

}  // namespace TemplateSpecialization

int main() {
    int a[42];
    static_assert(TemplateSpecialization::A<decltype(a)>::value == 1);
    extern int x[];  // 传引用时将变为 int(&)[]
    static_assert(TemplateSpecialization::A<decltype(x)>::value ==
                  3);  // A<T[]>
    TemplateSpecialization::test(a, a, a, x, x, x, x);
    return 0;
}