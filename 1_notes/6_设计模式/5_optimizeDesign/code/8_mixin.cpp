/*

## Mixins

### 使用 Mixins 手法可以更方便地引入额外信息

```cpp
#include <cassert>
#include <string>

namespace jc {

template <typename... Mixins>
struct Point : Mixins... {
  Point() : Mixins()..., x(0.0), y(0.0) {}
  Point(double x, double y) : Mixins()..., x(x), y(y) {}
  double x;
  double y;
};

struct Label {
  std::string label = "point";
};

struct Color {
  enum { red, green, blue };
};

using CustomPoint = Point<Label, Color>;

}  // namespace jc

int main() {
  jc::CustomPoint p;
  assert(p.label == "point");
  assert(p.red == jc::Color::red);
  assert(p.green == jc::Color::green);
  assert(p.blue == jc::Color::blue);
}
```

### CRTP-mixin

```cpp
#include <cassert>
#include <string>

namespace jc {

template <typename T>
class Base {
 public:
  static int count() { return i; }

 protected:
  Base() { ++i; }
  Base(const Base<T> &) { ++i; }
  Base(Base<T> &&) noexcept { ++i; }
  ~Base() { --i; }

 private:
  inline static int i = 0;
};

template <template <typename> class... Mixins>
struct Point : Mixins<Point<>>... {
  Point() : Mixins<Point<>>()..., x(0.0), y(0.0) {}
  Point(double x, double y) : Mixins<Point<>>()..., x(x), y(y) {}
  double x;
  double y;
};

template <typename T>
struct Label {
  std::string label = "point";
};

template <typename T>
struct Color {
  enum { red, green, blue };
};

using PointCount = Point<Base, Label, Color>;

}  // namespace jc

int main() {
  jc::PointCount a, b, c;
  assert(jc::PointCount::count() == 3);
  assert(a.label == "point");
  assert(a.red == jc::Color<void>::red);
  assert(a.green == jc::Color<void>::green);
  assert(a.blue == jc::Color<void>::blue);
}
```

### Mixins 参数化成员函数的虚拟性

```cpp
#include <cassert>

namespace jc {

template <typename... Mixins>
class Base : private Mixins... {
 public:
  int f() { return 1; }  // 是否为虚函数由 Mixins 中的声明决定
};

template <typename... Mixins>
class Derived : public Base<Mixins...> {
 public:
  int f() { return 2; }
};

}  // namespace jc

struct A {};

struct B {
  virtual int f() = 0;
};

int main() {
  jc::Base<A>* p = new jc::Derived<A>;
  assert(p->f() == 1);

  jc::Base<B>* q = new jc::Derived<B>;
  assert(q->f() == 2);
}
```


*/