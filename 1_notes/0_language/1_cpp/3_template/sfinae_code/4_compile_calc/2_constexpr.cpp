
#include <iostream>
#include <type_traits>

/*

    1. constexpr 函数和常量表达式
        constexpr 是 C++11 引入的一个关键字，用来标识那些能够在编译期求值的函数或变量。
        它允许我们在编译期进行一些简单的数学计算、字符串处理、条件判断等。

    2. if constexpr 条件编译（C++ 17）
        C++ 17 引入了 if constexpr 语句，它允许在编译期根据条件选择不同的代码路径，类似于模板特化。
        if constexpr 在编译期根据条件来决定是否编译某个代码块，从而减少了不必要的代码生成和提高了性能。

*/

namespace Constexpr_Usage {
    constexpr int factorial(int n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }
    constexpr int value = Constexpr_Usage::factorial(5);  // 编译期计算 5!

}  // namespace Constexpr_Usage

namespace If_Constexpr_Usage {
    template <typename T>
    void print_type(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Integer: " << value << std::endl;
        } else {
            std::cout << "Non-integer: " << value << std::endl;
        }
    }
}  // namespace If_Constexpr_Usage

int main() {
    std::cout << Constexpr_Usage::value << std::endl;  // 输出: 120
    If_Constexpr_Usage::print_type(42);                // 输出: Integer: 42
    If_Constexpr_Usage::print_type(3.14);  // 输出: Non-integer: 3.14
    return 0;
}
