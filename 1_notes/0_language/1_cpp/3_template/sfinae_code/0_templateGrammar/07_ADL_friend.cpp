#include <iostream>

/*
  ## ADL 与友元函数

  如果一个类的友元函数所在类是 ADL 的关联类集合的一部分，那么该友元函数可以在外围作用域找到并调用。否则，若该类未实例化，则该友元函数不可见。

  示例：ADL 与友元函数
*/

namespace jc {

    template <typename T>
    class A {
        friend void f() { std::cout << "friend void f()" << std::endl; }
        friend void f(A<T>) { std::cout << "friend void f(A<T>)" << std::endl; }
    };

    void g(const A<int>& a) {
        // f();   // f() 无参数，不能使用 ADL，不可见
        f(a);  // f(A<int>) 关联类 A<int> 所以可见，若类 A<int> 未实例化则调用时实例化
    }

}  // namespace jc

int main() {
    jc::A<int> a;
    jc::g(a);
    return 0;
}

/*
  在这个示例中：

  - `f()` 是 `A<T>` 的友元函数，但由于 `f()` 不带参数，它不能通过 ADL 查找。
  - `f(a)` 使用了 `A<int>` 类型作为参数，因此可以通过 ADL 查找到 `f(A<int>)`，且如果 `A<int>` 类未实例化，调用时会触发类实例化。
*/