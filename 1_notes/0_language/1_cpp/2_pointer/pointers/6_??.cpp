#include <iostream>
class Foo {
  public:
    void print() { std::cout << "Hello from Foo" << std::endl; }
};

int main() {
    Foo *ptr = new Foo();
    Foo *(*bar_1) = nullptr;
    Foo **bar_2 = nullptr;

    bar_1 = &ptr;
    bar_2 = &ptr;

    // 使用 bar_1 来调用 Foo 的成员函数
    // (*bar_1)->print();
    (**bar_1).print();

    // 使用 bar_2 来调用 Foo 的成员函数
    (*bar_2)->print();
    (**bar_2).print();

    delete ptr;
    return 0;
}