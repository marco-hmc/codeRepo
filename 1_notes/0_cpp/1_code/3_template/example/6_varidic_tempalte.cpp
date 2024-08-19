#include <iostream>
#include <string>
#include <tuple>
#include <utility>

namespace jc {

void print() {}  // 参数包展开到零参数时调用

template <typename T, typename... Args>
void print(const T& t, Args&&... args) {
  std::cout << t << ",";
  print(std::forward<Args>(args)...);
}

template <int... Index>
struct A {};

template <typename... List, int... Index>
void test1(const std::tuple<List...>& t, A<Index...>) {
  print(std::get<Index>(t)...);  // print(std::get<2>(t), std::get<3>(t));
}

template <typename... List, int... Index>
void test2(const std::tuple<List...>& t, A<Index...>) {
  print((std::get<Index>(t) + std::get<Index>(t))...);
}

}  // namespace jc

int main() {
  auto t = std::make_tuple(3.14, 42, std::string{"hello"}, "world");
  jc::test1(t, jc::A<2, 3>{});     // hello,world
  jc::test2(t, jc::A<0, 1, 2>{});  // 6.28,84,hellohello,
}