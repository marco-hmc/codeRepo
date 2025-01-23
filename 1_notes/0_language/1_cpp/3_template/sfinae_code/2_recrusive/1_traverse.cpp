#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>

namespace PrintAll {
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

    void test() {
        auto t = std::make_tuple(3.14, 42, "hello world");
        Print(t);  // 输出: 3.14 42 hello world
        std::cout << std::endl;
    }
}  // namespace PrintAll

namespace TemplateCalcFactorial {
    template <std::size_t N>
    struct Factorial {
        static constexpr std::size_t value = N * Factorial<N - 1>::value;
    };

    template <>
    struct Factorial<0> {
        static constexpr std::size_t value = 1;
    };

    void test() {
        std::cout << "Factorial<5>::value: " << Factorial<5>::value
                  << std::endl;  // 输出: 120
    }
}  // namespace TemplateCalcFactorial

namespace TemplateCalcFibonacci {
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
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    void test() {
        std::cout << "Fibonacci<10>::value: " << Fibonacci<10>::value
                  << std::endl;  // 输出: 55
    }

}  // namespace TemplateCalcFibonacci

namespace TemplateCalcGCD {
    template <std::size_t A, std::size_t B>
    struct GCD {
        static constexpr std::size_t value = GCD<B, A % B>::value;
    };

    template <std::size_t A>
    struct GCD<A, 0> {
        static constexpr std::size_t value = A;
    };

    void test() {
        std::cout << "GCD<48, 18>::value: " << GCD<48, 18>::value
                  << std::endl;  // 输出: 6
    }

}  // namespace TemplateCalcGCD

namespace TemplateCalcMax {

    template <int N, int... Ns>
    struct max;

    template <int N>
    struct max<N> : std::integral_constant<int, N> {};

    template <int N1, int N2, int... Ns>
    struct max<N1, N2, Ns...>
        : std::integral_constant<int, (N1 < N2) ? max<N2, Ns...>::value
                                                : max<N1, Ns...>::value> {};

    template <int... Ns>
    inline constexpr auto max_v = max<Ns...>::value;

    void test() { static_assert(TemplateCalcMax::max_v<3, 2, 1, 5, 4> == 5); }

}  // namespace TemplateCalcMax

namespace TemplateCalcSqrt {

    template <int N, int L = 1, int R = N>
    struct sqrt {
        static constexpr auto M = L + (R - L) / 2;
        static constexpr auto T = N / M;
        static constexpr auto value =  // 避免递归实例化所有分支
            std::conditional_t<(T < M), sqrt<N, L, M>,
                               sqrt<N, M + 1, R>>::value;
    };

    template <int N, int M>
    struct sqrt<N, M, M> {
        static constexpr auto value = M - 1;
    };

    template <int N>
    inline constexpr auto sqrt_v = sqrt<N, 1, N>::value;

    void test() { static_assert(sqrt_v<10000> == 100); }
}  // namespace TemplateCalcSqrt

namespace TemplateCalcSqrt2 {

    template <int N>
    constexpr int sqrt() {
        if constexpr (N <= 1) {
            return N;
        }
        int l = 1;
        int r = N;
        while (l < r) {
            int m = l + (r - l) / 2;
            int t = N / m;
            if (m == t) {
                return m;
            }

            if (m > t) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l - 1;
    }

    void test() { static_assert(TemplateCalcSqrt2::sqrt<10000>() == 100); }

}  // namespace TemplateCalcSqrt2

int main() {
    PrintAll::test();
    TemplateCalcFactorial::test();
    TemplateCalcFibonacci::test();
    TemplateCalcGCD::test();

    TemplateCalcMax::test();
    TemplateCalcSqrt::test();
    TemplateCalcSqrt2::test();
    return 0;
}