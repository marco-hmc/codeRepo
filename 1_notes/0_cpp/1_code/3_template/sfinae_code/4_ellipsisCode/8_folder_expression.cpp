#include <iostream>
#include <tuple>
#include <utility>

namespace jc {

template <typename... Args> auto sum(Args &&...args) {
  auto a = (... + std::forward<Args>(args));     // (((1 + 2) + 3) + 4)
  auto b = (std::forward<Args>(args) + ...);     // (1 + (2 + (3 + 4)))
  auto c = (5 + ... + std::forward<Args>(args)); // ((((5 + 1) + 2) + 3) + 4)
  auto d = (std::forward<Args>(args) + ... + 5); // (1 + (2 + (3 + (4 + 5))))
  return std::make_tuple(a, b, c, d);
}

auto print1 = [](auto &&...args) {
  // operator<< 左折叠，std::cout 是初始值
  (std::cout << ... << std::forward<decltype(args)>(args));
};

auto print2 = [](auto &&...args) {
  // operator, 左折叠
  ((std::cout << std::forward<decltype(args)>(args) << ","), ...);
};

} // namespace jc

int main() {
  auto [a, b, c, d] = jc::sum(1, 2, 3, 4);
  jc::print1(a, b, c, d); // 10101515
  jc::print2(a, b, c, d); // 10,10,15,15,
}