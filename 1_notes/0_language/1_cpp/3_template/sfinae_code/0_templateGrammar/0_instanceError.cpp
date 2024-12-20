/*
  教学示例：模板参数中的常见错误

  1. 字符串字面值不能直接作为模板参数：
     C++ 标准不允许字符串字面值直接作为模板参数传递，因为它们的地址在编译时是未知的。
     解决方法是使用指向常量字符数组的指针。

  2. 未定义类型作为模板参数：
     模板类可以接受未定义的类型作为模板参数，但前提是模板类不需要知道该类型的定义。
     例如，指针类型可以接受未定义的类型，而对象类型则不能。
*/

#include <iostream>

namespace _1_1 {

    const char str[] = "abc";
    template <const char *s>
    class S {
      public:
        void print() { std::cout << s << std::endl; }
    };

    void foo2() {
        // 错误示例：字符串字面值不能直接作为模板参数
        // S<"abc"> i;  // 错误：字符串字面值不能直接作为模板参数

        S<str> i;
        i.print();
    }
}  // namespace _1_1

namespace _1_2 {

    // 模板类 ClassB 接受未定义的类型作为指针
    template <typename T>
    class ClassB {
        T *a;  // 指针类型可以接受未定义的类型
    };

    // 模板类 ClassC 需要知道类型的定义
    template <typename T>
    class ClassC {
        T a;  // 对象类型不能接受未定义的类型
    };

    struct StructA;  // 声明 StructA

    void foo() {
        // 正确示例：指针类型可以接受未定义的类型
        ClassB<StructA> d;

        // 错误示例：对象类型不能接受未定义的类型
        // ClassC<StructA> e;  // 错误：StructA 未定义

        // 正确示例：定义 StructA 后使用对象类型
        struct StructA {};  // 定义 StructA
        ClassC<StructA> e;  // 正确：StructA 已定义
    }

}  // namespace _1_2

int main() {
    _1_1::foo2();
    _1_2::foo();
    return 0;
}