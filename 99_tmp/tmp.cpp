#include <iostream>

struct Foo {
    int a;
    int b;
};

int main() {
    // 创建一个 Foo 对象
    {
        Foo fooInstance;
        fooInstance.a = 10;
        fooInstance.b = 20;

        // 创建一个指向 Foo 对象的指针
        Foo *fooPtr = &fooInstance;
        Foo **bar = &fooPtr;

        // 通过二级指针访问 Foo 对象的成员
        std::cout << "a: " << (*bar)->a << std::endl;
        std::cout << "b: " << (*bar)->b << std::endl;
    }

    { Foo *(*bar) = nullptr; }
    return 0;
}