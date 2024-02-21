#include <utility> // Include the <utility> header for std::forward

class Foo {
public:
  Foo(int a, int b);

  int a;
  int b;
};

class Bar {
public:
  template <typename T1, typename T2>
  Bar(T1 &&left, T2 &&right)
      : left(std::forward<T1>(left)), right(std::forward<T2>(right)) {}

public:
  Foo left;
  Foo right;
};

// class Utils {
// public:
//   template <typename T1, typename T2> static Bar createBar(T1 &&a, T2 &&b) {
//     return Bar(std::forward<T1>(a), std::forward<T2>(b));
//   }
//   template <typename T1, typename T2> static Bar createBar2(T1 &&a, T2 &&b);
//   static void printHello();
// };

// template <typename T1, typename T2> Bar Utils::createBar2(T1 &&a, T2 &&b) {
//   return Bar(std::forward<T1>(a), std::forward<T2>(b));
// }