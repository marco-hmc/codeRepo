#include <iostream>

/*
  ## ADL 忽略 `using` 声明

  ADL（Argument-Dependent Lookup，实参依赖查找）不会考虑作用域中的 `using` 声明或 `using namespace` 语句。因此，即使在某个命名空间内通过 `using` 引入了其他命名空间的函数，也不会影响 ADL 的查找过程。

  示例：ADL 忽略 `using` 声明

  ADL 会查找与实参类型关联的命名空间或类，具体的关联规则如下：
  - **内置类型**：没有关联的命名空间或类，ADL 不会发生。
  - **指针和数组类型**：查找所引用类型的关联命名空间和类。
  - **枚举类型**：查找与枚举类型声明所在的命名空间。
  - **类成员**：查找该成员所在的类。
  - **类类型**：查找与该类相关的所有命名空间和类，包括该类本身、直接和间接的基类。
  - **函数类型**：查找函数参数类型和返回类型相关的命名空间和类。
  - **类成员指针类型**：查找类成员所在的类和命名空间。

*/

namespace jc {
    template <typename T>
    constexpr int f(T) {
        return 1;
    }
}  // namespace jc

namespace jd {

    using namespace jc;  // 忽略 using 声明，不会调用 jc::f

    enum Color { red };
    constexpr int f(Color) { return 2; }

}  // namespace jd

constexpr int f(int) { return 3; }

static_assert(::f(jd::red) == 3);  // 受限的函数名称，不使用 ADL
static_assert(f(jd::red) == 2);    // 使用 ADL 找到 jd::f()

int main() {
    std::cout << "::f(jd::red) = " << ::f(jd::red) << std::endl;  // 输出 3
    std::cout << "f(jd::red) = " << f(jd::red) << std::endl;      // 输出 2
    return 0;
}

/*
  在这个例子中：

  - 在 `jd` 命名空间内，`using namespace jc;` 不会影响 ADL。调用 `::f(jd::red)` 会查找全局作用域中的 `f(int)`。
  - `f(jd::red)` 会通过 ADL 查找 `jd::f()`，因为 `jd::f()` 是 `jd::red` 的逻辑组成部分。
*/