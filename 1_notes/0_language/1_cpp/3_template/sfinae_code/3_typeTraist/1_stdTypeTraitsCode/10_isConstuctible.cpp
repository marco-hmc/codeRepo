#include <iostream>
#include <type_traits>

/*
2. std::is_constructible 怎么用？
    std::is_constructible 是一个模板，用于检查一个类型是否可以使用给定的参数进行构造。
    它可以用于模板元编程中，作为类型特性的检查工具。
*/

namespace isConstructibleUsage {
    template <typename T, typename... Args>
    using is_constructible_t = typename std::is_constructible<T, Args...>::type;

    static_assert(std::is_constructible<int>::value, "int 应该是可默认构造的");
    static_assert(std::is_constructible<int, int>::value,
                  "int 应该是可用 int 构造的");
    static_assert(!std::is_constructible<int, double*>::value,
                  "int 不应该是可用 double* 构造的");

    struct A {
        A(int) {}
    };

    static_assert(std::is_constructible<A, int>::value,
                  "A 应该是可用 int 构造的");
    static_assert(!std::is_constructible<A, double*>::value,
                  "A 不应该是可用 double* 构造的");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "std::is_constructible<int>::value: "
                  << std::is_constructible<int>::value << std::endl;
        std::cout << "std::is_constructible<int, int>::value: "
                  << std::is_constructible<int, int>::value << std::endl;
        std::cout << "std::is_constructible<int, double*>::value: "
                  << std::is_constructible<int, double*>::value << std::endl;
        std::cout << "std::is_constructible<A, int>::value: "
                  << std::is_constructible<A, int>::value << std::endl;
        std::cout << "std::is_constructible<A, double*>::value: "
                  << std::is_constructible<A, double*>::value << std::endl;
    }
}  // namespace isConstructibleUsage

namespace isConstructibleImpl {

    template <typename T, typename... Args>
    struct is_constructible {
      private:
        template <typename U, typename = decltype(U(std::declval<Args>()...))>
        static std::true_type test(void*);

        template <typename>
        static std::false_type test(...);

      public:
        static constexpr bool value = decltype(test<T>(nullptr))::value;
    };

    template <typename T, typename... Args>
    constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

    static_assert(is_constructible_v<int>, "int 应该是可默认构造的");
    static_assert(is_constructible_v<int, int>, "int 应该是可用 int 构造的");
    static_assert(!is_constructible_v<int, double*>,
                  "int 不应该是可用 double* 构造的");

    struct A {
        A(int) {}
    };

    static_assert(is_constructible_v<A, int>, "A 应该是可用 int 构造的");
    static_assert(!is_constructible_v<A, double*>,
                  "A 不应该是可用 double* 构造的");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "is_constructible_v<int>: "
                  << is_constructible_v<int> << std::endl;
        std::cout << "is_constructible_v<int, int>: "
                  << is_constructible_v<int, int> << std::endl;
        std::cout << "is_constructible_v<int, double*>: "
                  << is_constructible_v<int, double*> << std::endl;
        std::cout << "is_constructible_v<A, int>: "
                  << is_constructible_v<A, int> << std::endl;
        std::cout << "is_constructible_v<A, double*>: "
                  << is_constructible_v<A, double*> << std::endl;
    }
}  // namespace isConstructibleImpl

int main() {
    isConstructibleUsage::test();
    isConstructibleImpl::test();
    return 0;
}