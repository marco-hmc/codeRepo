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

3. std::is_same 怎么用？
    std::is_same 用于检查两个类型是否相同。
    如果类型 T 和 U 相同，则 std::is_same<T, U>::value 为 true；
    否则为 false。
*/

namespace is_base_ofUsage {
    struct Base {};
    struct Derived : Base {};
    struct Unrelated {};

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
    struct A {};
    struct B : A {};
    struct C {};

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

namespace is_sameUsage {

    static_assert(std::is_same<int, int>::value, "int 应该与 int 相同");
    static_assert(!std::is_same<int, double>::value,
                  "int 不应该与 double 相同");

    void test() {
        std::cout << "std::is_same<int, int>::value: "
                  << std::is_same<int, int>::value << std::endl;
        std::cout << "std::is_same<int, double>::value: "
                  << std::is_same<int, double>::value << std::endl;
    }
}  // namespace is_sameUsage

namespace is_base_ofImpl {

    template <typename Base, typename Derived>
    struct is_base_of {
        static constexpr bool value = std::is_base_of<Base, Derived>::value;
    };
}  // namespace is_base_ofImpl

namespace is_convertibleImpl {

    template <typename From, typename To>
    struct is_convertible {
        static constexpr bool value = std::is_convertible<From, To>::value;
    };
}  // namespace is_convertibleImpl

namespace is_sameImpl {

    template <typename T, typename U>
    struct is_same {
        static constexpr bool value = std::is_same<T, U>::value;
    };
}  // namespace is_sameImpl

int main() {
    is_base_ofUsage::test();
    is_convertibleUsage::test();
    is_sameUsage::test();
    return 0;
}