#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

struct RangeValue {
  enum RangeInfinity {
    kPositiveInfinite,
    kNegativeInfinite,
  };
  static const RangeValue PositiveInfinity;
  static const RangeValue NegativeInfinite;

  double value;
  bool bounded;
  RangeInfinity infinity;
};

const RangeValue RangeValue::PositiveInfinity{0, false,
                                              RangeValue::kPositiveInfinite};

class Foo {
public:
  Foo(int a, int b) : a(a), b(b) {}

  int a;
  int b;
};

class Bar {
public:
  Bar(Foo left, Foo right) : left(left), right(right) {}

public:
  Foo left;
  Foo right;
};

class Utils {
public:
  template <typename T1, typename T2> static Bar createBar(T1 &&a, T2 &&b) {
    return Bar(std::forward<T1>(a), std::forward<T2>(b));
  }
  static void printHello() { cout << "hello" << endl; }
};

int main() {
  double a = 1.;
  double b = 2.;
  if (a == b) {
    cout << "a == b" << endl;
  }
  auto tmp = Utils::createBar(Foo{1, 2}, Foo{3, 4});
}
