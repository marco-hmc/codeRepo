#include <iostream>
#include <memory>

struct Foo {
  Foo() { std::cout << "Foo::Foo" << '\n'; }
  ~Foo() { std::cout << "Foo::~Foo" << '\n'; }
  void foo() { std::cout << "Foo::foo" << '\n'; }
};

void f(const Foo &) { std::cout << "f(const Foo&)" << '\n'; }

int main() {
  std::unique_ptr<Foo> p1(std::make_unique<Foo>());

  // p1 is not empty, prints
  if (p1)
    p1->foo();
  {
    std::unique_ptr<Foo> p2(std::move(p1));

    // p2 is not empty, prints
    f(*p2);

    // p2 is not empty, prints
    if (p2)
      p2->foo();

    // p1 is empty, no prints
    if (p1)
      p1->foo();

    p1 = std::move(p2);

    // p2 is empty, no prints
    if (p2)
      p2->foo();
    std::cout << "p2 was destroyed" << '\n';
  }
  // p1 is not empty, prints
  if (p1)
    p1->foo();

  // Foo instance will be destroyed when leaving the scope
}
