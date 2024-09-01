#include <functional>
#include <iostream>

namespace identifier1 {
template <typename F> struct Y {
  F f;
  template <typename... Args> auto operator()(Args &&...args) const {
    return f(*this, std::forward<Args>(args)...);
  }
};

template <typename F> Y<F> make_y_combinator(F &&f) {
  return {std::forward<F>(f)};
}

void test_y_combinator() {
  auto factorial = make_y_combinator([](auto self, int n) -> int {
    if (n <= 1) {
      return 1;
    }
    return n * self(n - 1);
  });
  std::cout << "Factorial of 5: " << factorial(5) << '\n';
}
} // namespace identifier1

// Factorial function using Y combinator
////////////////////////////////////////////////////////////////////////////////////////

namespace identifier2 {
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
} // namespace identifier2

int main() {
  identifier1::test_y_combinator();
  identifier2::test_y_combinator();
  return 0;
}

/*
1. **什么是Y combinator?**
    Y-combinator是一个高阶函数，用于实现递归。它允许你在没有显式命名函数的情况下定义递归函数。

2. **为什么需要Y combinator?**
   在某些编程环境中，函数不能直接引用自身。Y-combinator提供了一种方法，使得即使在这种限制下，也可以定义递归函数。

3. **为什么Y combinator可以递归调用自己?**
   Y-combinator利用了函数的自应用，通过将一个函数应用于自身，能够在没有显式命名的情况下实现递归。通过传递一个函数作为参数，
   Y-combinator可以递归地调用自身。

*/