#include <iostream>

// 递归终止条件
int sum() {
    return 0;
}

// 求和函数,递归计算参数的总和
template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

int main() {
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
    return 0;
}
