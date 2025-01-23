#include <iostream>
#include <type_traits>

// 一个函数模板，仅当 T 是整数类型时启用
template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
void foo(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

template <typename T, std::enable_if_t<std::is_integral<T>::value, int>>
void foo2(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

template <typename T>
std::enable_if_t<std::is_integral<T>::value, int> foo2(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

int main() {
    foo(2);  // 调用浮点版本的 foo
    // foo2(3);  // 编译错误，无法匹配任何重载
    return 0;
}