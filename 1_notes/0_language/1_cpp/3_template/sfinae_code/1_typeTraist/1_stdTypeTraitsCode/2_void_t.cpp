#include <iostream>
#include <type_traits>

/*
1. std::void_t 怎么用？
    std::void_t 是一个用于 SFINAE（Substitution Failure Is Not An Error）的工具。
    它常用于编译时检查一个类型是否具有某个特定的成员类型、成员函数或属性。
    如果替换失败，编译器不会报错，而是选择其他重载或模板特化。
*/

namespace void_tUsage {
    template <typename, typename = std::void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;

    struct A {
        using type = int;
    };

    struct B {};

    static_assert(has_type_v<A>, "A has a member named type");
    static_assert(!has_type_v<B>, "B does not have a member named type");

    void test() {
        std::cout << "A has type: " << has_type_v<A> << std::endl;
        std::cout << "B has type: " << has_type_v<B> << std::endl;
    }
}  // namespace void_tUsage

////////////////////////////////////////////////////////////////////
namespace void_tImpl {
    template <typename... Ts>
    using void_t = void;

    template <typename, typename = void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, void_t<typename T::type>> : std::true_type {};

    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;

    struct A {
        using type = int;
    };

    struct B {};

    static_assert(has_type_v<A>, "A has a member named type");
    static_assert(!has_type_v<B>, "B does not have a member named type");

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