#include <cassert>
#include <utility>

class MyClass {
public:
  MyClass(int val = 0) : member(val) {}

  MyClass &operator=(MyClass other) {
    swap(*this, other);
    return *this;
  }

    friend void swap(MyClass& first, MyClass& second) {
        // Swap the members of 'first' and 'second'
        std::swap(first.member, second.member);
    }

    int getMember() const { return member; }

  private:
    int member;
};

int main() {
  MyClass a(5);
  MyClass b(10);
  a = b;
  assert(a.getMember() == 10);

  swap(a, b);
  assert(a.getMember() == 5);
  assert(b.getMember() == 10);

  return 0;
}