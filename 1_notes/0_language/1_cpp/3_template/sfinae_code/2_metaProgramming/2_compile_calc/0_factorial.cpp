#include <iostream>

template <int N>
struct factorial {
    static constexpr int value = N * factorial<N - 1>::value;
};

template <>
struct factorial<0> {
    static constexpr int value = 1;
};

int main() {
    std::cout << "Factorial of 5: " << factorial<5>::value << std::endl;
    std::cout << "Factorial of 0: " << factorial<0>::value << std::endl;
    return 0;
}