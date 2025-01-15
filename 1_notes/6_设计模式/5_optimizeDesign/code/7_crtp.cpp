/*
## 奇异递归模板模式（CRTP，The Curiously Recurring Template Pattern）

### CRTP 的实现手法是将派生类作为基类的模板参数

```cpp
#include <cassert>

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

template <typename T>
class Derived : public Base<Derived<T>> {};

}  // namespace jc

int main() {
  jc::Derived<int> a, b;
  jc::Derived<char> c;
  assert(jc::Derived<int>::count() == 2);
  assert(jc::Derived<char>::count() == 1);
}
```

### 通常大量运算符重载会一起出现，但通常这些运算符只需要一个定义，其他运算符可以提取到基类中基于这一个来实现

```cpp
#include <cassert>

namespace jc {

template <typename T>
class Base {
  friend bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
};

class Derived : public Base<Derived> {
  friend bool operator==(const Derived& lhs, const Derived& rhs) {
    return lhs.i_ == rhs.i_;
  }

 public:
  Derived(int i) : i_(i) {}

 private:
  int i_ = 0;
};

}  // namespace jc

int main() {
  jc::Derived a{1};
  jc::Derived b{2};
  assert(a != b);
}
```

### CRTP 基类可以基于 CRTP 派生类暴露的小得多的接口定义大部分接口，这个模式称为 facade 模式

```cpp
#include <cassert>
#include <iterator>
#include <type_traits>
#include <vector>

namespace jc {

template <typename Derived, typename Value, typename Category>
class IteratorFacade {
 public:
  using value_type = std::remove_const_t<Value>;
  using reference = Value&;
  using pointer = Value*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = Category;

 public:
  reference operator*() const { return as_derived().dereference(); }

  Derived& operator++() {
    as_derived().increment();
    return as_derived();
  }

  Derived operator++(int) {
    Derived tmp(as_derived());
    as_derived().increment();
    return tmp;
  }

  friend bool operator==(const IteratorFacade& lhs, const IteratorFacade& rhs) {
    return lhs.as_derived().equals(rhs.as_derived());
  }

  friend bool operator!=(const IteratorFacade& lhs, const IteratorFacade& rhs) {
    return !operator==(lhs, rhs);
  }

 private:
  Derived& as_derived() { return *static_cast<Derived*>(this); }

  const Derived& as_derived() const {
    return *static_cast<const Derived*>(this);
  }
};

template <typename T>
struct ListNode {
  ListNode(T x) : value(x) {}

  T value;
  ListNode<T>* next = nullptr;
};

template <typename T>
class ListNodeIterator
    : public IteratorFacade<ListNodeIterator<T>, T, std::forward_iterator_tag> {
 public:
  ListNodeIterator(ListNode<T>* t = nullptr) : t_(t) {}
  T& dereference() const { return t_->value; }
  void increment() { t_ = t_->next; }
  bool equals(const ListNodeIterator& rhs) const { return t_ == rhs.t_; }

 private:
  ListNode<T>* t_ = nullptr;
};

}  // namespace jc

int main() {
  auto a = new jc::ListNode<int>{1};
  auto b = new jc::ListNode<int>{2};
  auto c = new jc::ListNode<int>{3};
  a->next = b;
  b->next = c;

  auto first = jc::ListNodeIterator{a};
  auto last = ++jc::ListNodeIterator{c};

  std::vector<int> v;
  for (auto it = first; it != last; ++it) {
    v.emplace_back(*it);
  }
  assert((v == std::vector<int>{1, 2, 3}));

  delete c;
  delete b;
  delete a;
}
```

*/