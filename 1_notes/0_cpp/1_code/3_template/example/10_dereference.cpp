#include <type_traits>

template <typename T>
class has_dereference {
 private:
  template <typename U>
  struct Identity;

  template <typename U>
  static std::true_type test(Identity<decltype(*std::declval<U>())>*);

  template <typename U>
  static std::false_type test(...);

 public:
  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
inline constexpr bool has_dereference_v = has_dereference<T>::value;

template <typename T>
void f(T& i) {
  static_assert(has_dereference_v<T>, "T is not dereferenceable");
  *i = 0;
}

int main() {
  int i = 42;
  f(i);  // static_assert 报错：T is not dereferenceable
}