// if constexpr 条件编译（C++ 17）
// C++ 17 引入了 if constexpr 语句，它允许在编译期根据条件选择不同的代码路径，类似于模板特化。if constexpr 在编译期根据条件来决定是否编译某个代码块，从而减少了不必要的代码生成和提高了性能。

#include <iostream>
#include <type_traits>

namespace if_constexpr_demo {
    template <typename T>
    void print_type(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Integer: " << value << std::endl;
        } else {
            std::cout << "Non-integer: " << value << std::endl;
        }
    }
}  // namespace if_constexpr_demo

int main() {
    if_constexpr_demo::print_type(42);    // 输出: Integer: 42
    if_constexpr_demo::print_type(3.14);  // 输出: Non-integer: 3.14
    return 0;
}