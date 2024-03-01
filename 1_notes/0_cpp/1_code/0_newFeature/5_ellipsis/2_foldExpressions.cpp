#include <iostream>

// 使用折叠表达式计算参数包中所有参数的和
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

int main() {
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
    return 0;
}
