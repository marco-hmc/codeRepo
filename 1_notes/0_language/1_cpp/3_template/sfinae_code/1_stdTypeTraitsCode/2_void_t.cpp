#include <iostream>
#include <type_traits>

/*
1. std::void_t 怎么用？
    std::void_t 是一个用于 SFINAE（Substitution Failure Is Not An Error）的工具。
    它常用于编译时检查一个类型是否具有某个特定的成员类型、成员函数或属性。
    如果替换失败，编译器不会报错，而是选择其他重载或模板特化。
*/

namespace void_tUsage {
    // 定义一个模板结构体 has_type，用于检查类型 T 是否具有名为 type 的成员类型
    template <typename, typename = std::void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

    // 辅助变量模板，用于简化使用
    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;

    // 示例结构体
    struct A {
        using type = int;
    };

    struct B {};

    // 静态断言测试
    static_assert(has_type_v<A>, "A has a member named type");
    static_assert(!has_type_v<B>, "B does not have a member named type");

    // 运行时输出结果
    void test() {
        std::cout << "A has type: " << has_type_v<A> << std::endl;
        std::cout << "B has type: " << has_type_v<B> << std::endl;
    }
}  // namespace void_tUsage

////////////////////////////////////////////////////////////////////
namespace void_tImpl {
    // std::void_t 的实现
    template <typename... Ts>
    using void_t = void;

    // 定义一个模板结构体 has_type，用于检查类型 T 是否具有名为 type 的成员类型
    template <typename, typename = void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, void_t<typename T::type>> : std::true_type {};

    // 辅助变量模板，用于简化使用
    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;

    // 示例结构体
    struct A {
        using type = int;
    };

    struct B {};

    // 静态断言测试
    static_assert(has_type_v<A>, "A has a member named type");
    static_assert(!has_type_v<B>, "B does not have a member named type");

    // 运行时输出结果
    void test() {
        std::cout << "A has type: " << has_type_v<A> << std::endl;
        std::cout << "B has type: " << has_type_v<B> << std::endl;
    }
}  // namespace void_tImpl

int main() {
    void_tUsage::test();
    void_tImpl::test();
    return 0;
}