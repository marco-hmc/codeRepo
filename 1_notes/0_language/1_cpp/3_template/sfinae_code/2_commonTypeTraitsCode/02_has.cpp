#include <iostream>
#include <type_traits>

/*
2. has_type 和 has_function 怎么用？
    has_type 和 has_function 是模板元编程工具，用于在编译时检查类型是否具有特定的成员类型或成员函数。
    它们常用于 SFINAE（Substitution Failure Is Not An Error）技术中，根据条件选择合适的模板实例化。
*/

namespace hasUsage {
    // has_type 的实现
    template <typename, typename = std::void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

    // has_function 的实现
    template <typename, typename = std::void_t<>>
    struct has_function : std::false_type {};

    template <typename T>
    struct has_function<T, std::void_t<decltype(&T::function)>>
        : std::true_type {};

    // 示例类型
    struct A {
        typedef int type;
    };

    struct B {};

    struct C {
        void function() {}
    };

    struct D {};

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_type<A>::value: " << has_type<A>::value
                  << std::endl;  // 输出 true
        std::cout << "has_type<B>::value: " << has_type<B>::value
                  << std::endl;  // 输出 false
        std::cout << "has_function<C>::value: " << has_function<C>::value
                  << std::endl;  // 输出 true
        std::cout << "has_function<D>::value: " << has_function<D>::value
                  << std::endl;  // 输出 false
    }
}  // namespace hasUsage

////////////////////////////////////////////////////////////////////
namespace hasImpl {
    // has_type 的实现
    template <typename, typename = std::void_t<>>
    struct has_type : std::false_type {};

    template <typename T>
    struct has_type<T, std::void_t<typename T::type>> : std::true_type {};

    // has_function 的实现
    template <typename, typename = std::void_t<>>
    struct has_function : std::false_type {};

    template <typename T>
    struct has_function<T, std::void_t<decltype(&T::function)>>
        : std::true_type {};

    // 示例类型
    struct A {
        typedef int type;
    };

    struct B {};

    struct C {
        void function() {}
    };

    struct D {};

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_type<A>::value: " << has_type<A>::value
                  << std::endl;  // 输出 true
        std::cout << "has_type<B>::value: " << has_type<B>::value
                  << std::endl;  // 输出 false
        std::cout << "has_function<C>::value: " << has_function<C>::value
                  << std::endl;  // 输出 true
        std::cout << "has_function<D>::value: " << has_function<D>::value
                  << std::endl;  // 输出 false
    }
}  // namespace hasImpl

int main() {
    hasUsage::test();
    hasImpl::test();
    return 0;
}