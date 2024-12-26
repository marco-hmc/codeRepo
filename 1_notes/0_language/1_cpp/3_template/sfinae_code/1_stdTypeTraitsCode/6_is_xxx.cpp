#include <iostream>
#include <type_traits>

/*
1. std::is_base_of 怎么用？
    std::is_base_of 用于检查一个类型是否是另一个类型的基类。
    如果 Base 是 Derived 的基类或相同类型，则 std::is_base_of<Base, Derived>::value 为 true；
    否则为 false。

2. std::is_convertible 怎么用？
    std::is_convertible 用于检查一个类型是否可以转换为另一个类型。
    如果类型 From 可以隐式转换为类型 To，则 std::is_convertible<From, To>::value 为 true；
    否则为 false。
*/

namespace is_base_ofUsage {
    // 示例类
    struct Base {};
    struct Derived : Base {};
    struct Unrelated {};

    // 使用 std::is_base_of 检查基类关系
    static_assert(std::is_base_of<Base, Derived>::value,
                  "Base 应该是 Derived 的基类");
    static_assert(!std::is_base_of<Derived, Base>::value,
                  "Derived 不应该是 Base 的基类");
    static_assert(!std::is_base_of<Base, Unrelated>::value,
                  "Base 不应该是 Unrelated 的基类");

    void test() {
        std::cout << "std::is_base_of<Base, Derived>::value: "
                  << std::is_base_of<Base, Derived>::value << std::endl;
        std::cout << "std::is_base_of<Derived, Base>::value: "
                  << std::is_base_of<Derived, Base>::value << std::endl;
        std::cout << "std::is_base_of<Base, Unrelated>::value: "
                  << std::is_base_of<Base, Unrelated>::value << std::endl;
    }
}  // namespace is_base_ofUsage

namespace is_convertibleUsage {
    // 示例类
    struct A {};
    struct B : A {};
    struct C {};

    // 使用 std::is_convertible 检查类型转换
    static_assert(std::is_convertible<B, A>::value, "B 应该可以转换为 A");
    static_assert(!std::is_convertible<A, B>::value, "A 不应该可以转换为 B");
    static_assert(!std::is_convertible<C, A>::value, "C 不应该可以转换为 A");

    void test() {
        std::cout << "std::is_convertible<B, A>::value: "
                  << std::is_convertible<B, A>::value << std::endl;
        std::cout << "std::is_convertible<A, B>::value: "
                  << std::is_convertible<A, B>::value << std::endl;
        std::cout << "std::is_convertible<C, A>::value: "
                  << std::is_convertible<C, A>::value << std::endl;
    }
}  // namespace is_convertibleUsage

////////////////////////////////////////////////////////////////////
namespace is_base_ofImpl {
    // std::is_base_of 的实现
    template <typename Base, typename Derived>
    struct is_base_of {
        static constexpr bool value = std::is_base_of<Base, Derived>::value;
    };
}  // namespace is_base_ofImpl

namespace is_convertibleImpl {
    // std::is_convertible 的实现
    template <typename From, typename To>
    struct is_convertible {
        static constexpr bool value = std::is_convertible<From, To>::value;
    };
}  // namespace is_convertibleImpl

int main() {
    is_base_ofUsage::test();
    is_convertibleUsage::test();
    return 0;
}