#include <iostream>

// **注入类名** 是指类作用域中的类名称，它是该类类型的公有别名。该别名使得在类的成员函数中可以使用类名作为类型，进行便捷的类型声明。在类作用域内，类名不仅代表该类型的名称，还可以作为类型的标识符使用。

namespace jc {
    int A;

    struct A {
        void f() {
            A* p;  // OK：A 是注入类名
            // ::A* q;  // 错误：查找到全局变量 A，隐藏了 struct A 的名称
            std::cout << "Function f() called" << std::endl;
        }
    };

}  // namespace jc

int main() {
    // jc::A a;
    // a.f();
    return 0;
}