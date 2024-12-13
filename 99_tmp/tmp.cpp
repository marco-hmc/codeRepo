#include <functional>
#include <iostream>

auto Y = [](auto f) {
    return [f](auto x) -> std::function<int(int)> {
        return f([x](auto v) { return x(x)(v); });
    }([f](auto x) -> std::function<int(int)> {
               return f([x](auto v) { return x(x)(v); });
           });
};

auto factorial = Y(
    [](auto f) { return [f](int n) { return (n == 0) ? 1 : n * f(n - 1); }; });

void test_y_combinator() {
    std::cout << "Factorial of 5: " << factorial(5) << '\n';
}

int main() {
    test_y_combinator();
    return 0;
}