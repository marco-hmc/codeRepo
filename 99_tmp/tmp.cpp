#include <iostream>

template <bool B, class T = void> struct enable_if {};

template <class T> struct enable_if<true, T> {
  typedef T type;
};

template <bool B, class T> using enable_if_t = typename enable_if<B, T>::type;

template <class T> struct is_integral {};

template <> struct is_integral<int> {
  const static bool value = true;
};

template <class T> struct is_floating_point {};

template <> struct is_floating_point<float> {
  const static bool value = true;
};

struct T {
  enum { INT, FLOAT } type;

  template <typename Integer,
            enable_if_t<is_integral<Integer>::value, bool> = true>
  T(Integer) : type(INT) {}

  template <typename Floating,
            enable_if_t<is_floating_point<Floating>::value, bool> = true>
  T(Floating) : type(FLOAT) {}
};

int main() {
  boost::coroutines2::coroutine<int>::pull_type apull(
      [](boost::coroutines2::coroutine<int>::push_type &apush) {
        for (int i = 0; i < 10; i++) {
          std::cout << "---------------------"
                    << "coroutine 1" << '\n';
          apush(1);
        }
      });

  boost::coroutines2::coroutine<int>::pull_type apull2(
      [](boost::coroutines2::coroutine<int>::push_type &apush) {
        for (int i = 0; i < 10; i++) {
          std::cout << "---------------------"
                    << "coroutine 2" << '\n';
          apush(2);
        }
      });

  for (int i = 0; i < 10; ++i) {
    std::cout << apull.get() << '\n';
    apull();
    std::cout << apull2.get() << '\n';
    apull2();
  }
  std::cout << "continue>>>" << '\n';

  return 0;
}