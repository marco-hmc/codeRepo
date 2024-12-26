#include <iostream>
#include <type_traits>

/*
1. std::integral_constant 怎么用？
    std::integral_constant 是一个模板，用于表示一个编译时常量值。
    它可以用于模板元编程中，作为类型和值的桥梁。
*/

namespace integralConstantUsage {
    // 定义一个模板别名 true_type 和 false_type
    using true_type = std::integral_constant<bool, true>;
    using false_type = std::integral_constant<bool, false>;

    // 使用 std::integral_constant 定义常量
    constexpr int value1 = std::integral_constant<int, 42>::value;
    constexpr bool value2 = std::integral_constant<bool, true>::value;

    // 静态断言测试
    static_assert(value1 == 42, "value1 应该是 42");
    static_assert(value2 == true, "value2 应该是 true");

    void test() {
        std::cout << "value1: " << value1 << std::endl;
        std::cout << "value2: " << std::boolalpha << value2 << std::endl;
    }
}  // namespace integralConstantUsage

////////////////////////////////////////////////////////////////////
namespace integralConstantImpl {
    // std::integral_constant 的实现
    template <class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant;  // 使用 typedef 以便于访问
        constexpr operator value_type() const noexcept { return value; }
    };

    // 定义一个模板别名 true_type 和 false_type
    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    // 使用自定义的 integral_constant 定义常量
    constexpr int value1 = integral_constant<int, 42>::value;
    constexpr bool value2 = integral_constant<bool, true>::value;

    // 静态断言测试
    static_assert(value1 == 42, "value1 应该是 42");
    static_assert(value2 == true, "value2 应该是 true");

    void test() {
        std::cout << "value1: " << value1 << std::endl;
        std::cout << "value2: " << std::boolalpha << value2 << std::endl;
    }
}  // namespace integralConstantImpl

int main() {
    integralConstantUsage::test();
    integralConstantImpl::test();
    return 0;
}