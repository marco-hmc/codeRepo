#include <cstddef>
#include <iostream>
#include <tuple>

namespace jc {

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

}  // namespace jc

int main() {
  auto t = std::make_tuple(3.14, 42, "hello world");
  jc::Print(t);  // 3.14 42 hello world
}