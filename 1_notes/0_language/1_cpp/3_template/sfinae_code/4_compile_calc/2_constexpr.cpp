// constexpr 函数和常量表达式
// constexpr 是 C++11 引入的一个关键字，用来标识那些能够在编译期求值的函数或变量。它允许我们在编译期进行一些简单的数学计算、字符串处理、条件判断等。

#include <iostream>

namespace constexpr_demo {
    constexpr int factorial(int n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }
}  // namespace constexpr_demo

int main() {
    constexpr int value = constexpr_demo::factorial(5);  // 编译期计算 5!
    std::cout << value << std::endl;                     // 输出: 120
    return 0;
}