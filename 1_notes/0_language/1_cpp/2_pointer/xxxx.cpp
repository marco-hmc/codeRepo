#include <iostream>

struct Foo {
    int a;
    int b;
};

// 这两种的区别是什么？
Foo *(*bar_1) = nullptr;
Foo **bar_2 = nullptr;

int main() {
    // 创建一个 Foo 实例
    Foo foo_instance = {1, 2};
    Foo *foo_ptr = &foo_instance;

    // 使用 bar_1
    bar_1 = &foo_ptr;  // bar_1 是一个指向 Foo* 类型指针的指针
    std::cout << "bar_1 points to: " << (*bar_1)->a << ", " << (*bar_1)->b
              << std::endl;

    // 使用 bar_2
    bar_2 = &foo_ptr;  // bar_2 是一个指向 Foo* 类型指针的指针
    std::cout << "bar_2 points to: " << (*bar_2)->a << ", " << (*bar_2)->b
              << std::endl;

    return 0;
}