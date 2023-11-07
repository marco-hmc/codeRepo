// ### 折叠表达式

// C++ 17 中将变长参数这种特性进一步带给了表达式,考虑下面这个例子:

#include <iostream>
template<typename ... T>
auto sum(T ... t) {
    return (t + ...);
}

template <auto value>
void foo() {
    std::cout << value << std::endl;
    return;
}

int main() {
    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    foo<10>();  // value 被推导为 int 类型
}

