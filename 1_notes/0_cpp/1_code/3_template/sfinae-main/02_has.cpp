#include <iostream>

namespace Method1 {
template <typename T> struct has_type {
  template <typename C> static char test(typename C::type *);

  template <typename C> static int test(...);

  static const bool value = sizeof(test<T>(nullptr)) == sizeof(char);
};

struct A {
  typedef int type;
};
struct B {};

void test_has_type() {
  std::cout << std::boolalpha;
  std::cout << has_type<A>::value << '\n'; // 输出true
  std::cout << has_type<B>::value << '\n'; // 输出false
}
} // namespace Method1

namespace Method2 {
#include <type_traits>

template <typename, typename = std::void_t<>>
struct has_type : std::false_type {};

template <typename T>
struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

struct A {
  typedef int type;
};
struct B {};

void test_has_type() {
  std::cout << std::boolalpha;
  std::cout << has_type<A>::value << std::endl; // 输出true
  std::cout << has_type<B>::value << std::endl; // 输出false
}
} // namespace Method2

//////////////////////////////////////////////////////
namespace Method1 {
template <typename T> struct has_function {
  template <typename C> static char test(decltype(&C::function));

  template <typename C> static int test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

struct C {
  void function() {}
};
struct D {};

void test_has_function() {
  std::cout << std::boolalpha;
  std::cout << has_function<C>::value << '\n'; // 输出true
  std::cout << has_function<D>::value << '\n'; // 输出false
}
} // namespace Method1

namespace Method2 {

template <typename, typename = std::void_t<>>
struct has_function : std::false_type {};

template <typename T>
struct has_function<T, std::void_t<decltype(&T::function)>> : std::true_type {};

// 测试代码
struct C {
  void function() {}
};

struct D {};

void test_has_function() {
  std::cout << std::boolalpha;
  std::cout << has_function<C>::value << std::endl; // 输出true
  std::cout << has_function<D>::value << std::endl; // 输出false
}
} // namespace Method2
/////////////////////////////////////////////////////

int main() {
  Method1::test_has_type();
  Method2::test_has_type();
  Method1::test_has_function();
  Method2::test_has_function();
  return 0;
}
