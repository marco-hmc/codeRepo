#include <iostream>

/*
  ## 注入类名（Injected Class Name）

  注入类名是指类作用域中的类名称，它是该类类型的公有别名。该别名使得在类的成员函数中可以使用类名作为类型，进行便捷的类型声明。在类作用域内，类名不仅代表该类型的名称，还可以作为类型的标识符使用。

  示例：注入类名
*/

namespace jc {
    int A;

    struct A {
        void f() {
            A* p;  // OK：A 是注入类名
            ::A* q;  // 错误：查找到全局变量 A，隐藏了 struct A 的名称
        }
    };

}  // namespace jc

int main() {
    jc::A a;
    a.f();
    return 0;
}

/*
  在这个示例中：

  - `A* p;` 使用 `A` 作为类名来声明指针，`A` 是类 `A` 的注入类名。
  - `::A* q;` 会错误地查找到全局变量 `A`，而不是 `struct A`，因为全局作用域中的 `A` 隐藏了类名。
*/