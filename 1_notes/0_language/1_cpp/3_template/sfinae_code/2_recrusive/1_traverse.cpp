#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>

namespace print {

    // 递归打印元组的实现
    template <std::size_t Index, std::size_t N, typename... List>
    struct PrintImpl {
        static void impl(const std::tuple<List...>& t) {
            std::cout << std::get<Index>(t) << " ";
            PrintImpl<Index + 1, N, List...>::impl(t);
        }
    };

    template <std::size_t N, typename... List>
    struct PrintImpl<N, N, List...> {
        static void impl(const std::tuple<List...>& t) {}
    };

    template <typename... List>
    void Print(const std::tuple<List...>& t) {
        PrintImpl<0, sizeof...(List), List...>::impl(t);
    }

}  // namespace print

namespace factorial {

    // 递归计算阶乘的实现
    template <std::size_t N>
    struct Factorial {
        static constexpr std::size_t value = N * Factorial<N - 1>::value;
    };

    template <>
    struct Factorial<0> {
        static constexpr std::size_t value = 1;
    };

}  // namespace factorial

namespace fibonacci {

    // 递归计算斐波那契数列的实现
    template <std::size_t N>
    struct Fibonacci {
        static constexpr std::size_t value =
            Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
    };

    template <>
    struct Fibonacci<0> {
        static constexpr std::size_t value = 0;
    };

    template <>
    struct Fibonacci<1> {
        static constexpr std::size_t value = 1;
    };

    constexpr std::size_t fibonacci(std::size_t n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

}  // namespace fibonacci

namespace gcd {

    // 递归计算最大公约数的实现
    template <std::size_t A, std::size_t B>
    struct GCD {
        static constexpr std::size_t value = GCD<B, A % B>::value;
    };

    template <std::size_t A>
    struct GCD<A, 0> {
        static constexpr std::size_t value = A;
    };

}  // namespace gcd

int main() {
    // print::Print 测试
    auto t = std::make_tuple(3.14, 42, "hello world");
    print::Print(t);  // 输出: 3.14 42 hello world
    std::cout << std::endl;

    // factorial::Factorial 测试
    std::cout << "Factorial<5>::value: " << factorial::Factorial<5>::value
              << std::endl;  // 输出: 120

    // fibonacci::Fibonacci 测试
    std::cout << "Fibonacci<10>::value: " << fibonacci::Fibonacci<10>::value
              << std::endl;  // 输出: 55

    // gcd::GCD 测试
    std::cout << "GCD<48, 18>::value: " << gcd::GCD<48, 18>::value
              << std::endl;  // 输出: 6

    return 0;
}