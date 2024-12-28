#include <iostream>
#include <string>

/*
  ## ADL（Argument-Dependent Lookup，实参依赖查找）

  ADL 是 C++ 中的一种查找函数的机制。当函数调用时，编译器不仅查找局部作用域中的函数，还会根据函数的参数类型查找与其关联的命名空间或类。ADL 使得某些函数可以“隐式地”找到，而不需要显式指定命名空间或类名。

  ## ADL 的基本原理

  当你调用一个函数并传递一个类类型的参数时，编译器会通过 ADL 查找该函数。ADL 查找的范围包括：
  - 函数所在的局部作用域。
  - 与参数类型相关联的命名空间或类。

  示例：ADL 查找函数
*/

namespace jc {

    struct A {};

    void f(const A&) {
        std::cout << "jc::f(const A&)" << std::endl;
    }  // f() 是 A 的逻辑组成部分

}  // namespace jc

int main() {
    jc::A a;
    f(a);  // 通过 ADL 找到 jc::f()，如果没有 ADL，需要写成 jc::f(a)

    std::string s;
    std::cout << s;  // std::operator<<() 是 std::string 的逻辑组成部分
    // 如果没有 ADL，需要写成 std::operator<<(std::cout, s)

    return 0;
}

/*
  在上面的例子中：
  - `f(a)` 通过 ADL 找到 `jc::f()`，而无需显式地写成 `jc::f(a)`。
  - 对于 `std::cout << s;`，通过 ADL 查找到 `std::operator<<()`，无需显式写出 `std::operator<<(std::cout, s)`。

  注意：ADL 不会考虑作用域中的 `using` 声明或 `using namespace` 语句。因此，即使在某个命名空间内通过 `using` 引入了其他命名空间的函数，也不会影响 ADL 的查找过程。
*/