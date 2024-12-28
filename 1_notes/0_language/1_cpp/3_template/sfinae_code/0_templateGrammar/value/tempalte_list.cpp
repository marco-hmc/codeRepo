// 类型列表（Type List）
// 一个类型列表是由多个类型组成的一个结构，通常通过递归模板实现。可以通过类型列表来执行编译期计算，或定义一个对多个类型操作的算法。

#include <iostream>

namespace tl {
    template <typename... Types>
    struct type_list {};

    template <typename List>
    struct length;

    template <typename... Types>
    struct length<type_list<Types...>> {
        static constexpr size_t value = sizeof...(Types);
    };
}  // namespace tl

int main() {
    std::cout << "Length of type list: "
              << tl::length<tl::type_list<int, double, char>>::value
              << std::endl;
    return 0;
}