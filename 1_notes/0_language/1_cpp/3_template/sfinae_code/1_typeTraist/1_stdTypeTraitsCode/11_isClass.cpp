#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

/*
2. is_class 怎么用？
    is_class 是一个模板，用于检查一个类型是否是类类型。
    它可以用于模板元编程中，作为类型特性的检查工具。
*/

namespace isClassUsage {
    // is_class 的实现
    template <typename T, typename = std::void_t<>>
    struct is_class : std::false_type {};

    template <typename T>
    struct is_class<T, std::void_t<int T::*>> : std::true_type {};

    template <typename T>
    constexpr bool is_class_v = is_class<T>::value;

    // 静态断言测试
    static_assert(is_class_v<std::string>, "std::string 应该是类类型");
    static_assert(is_class_v<std::vector<int>>,
                  "std::vector<int> 应该是类类型");
    static_assert(!is_class_v<int>, "int 不应该是类类型");

    struct A {};
    union B {};

    static_assert(is_class_v<A>, "A 应该是类类型");
    static_assert(!is_class_v<B>, "B 不应该是类类型");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "is_class_v<std::string>: "
                  << is_class_v<std::string> << std::endl;
        std::cout << "is_class_v<std::vector<int>>: "
                  << is_class_v<std::vector<int>> << std::endl;
        std::cout << "is_class_v<int>: " << is_class_v<int> << std::endl;
        std::cout << "is_class_v<A>: " << is_class_v<A> << std::endl;
        std::cout << "is_class_v<B>: " << is_class_v<B> << std::endl;
    }
}  // namespace isClassUsage

////////////////////////////////////////////////////////////////////
namespace isClassImpl {
    // is_class 的实现
    template <typename T, typename = std::void_t<>>
    struct is_class : std::false_type {};

    template <typename T>
    struct is_class<T, std::void_t<int T::*>> : std::true_type {};

    template <typename T>
    constexpr bool is_class_v = is_class<T>::value;

    // 静态断言测试
    static_assert(is_class_v<std::string>, "std::string 应该是类类型");
    static_assert(is_class_v<std::vector<int>>,
                  "std::vector<int> 应该是类类型");
    static_assert(!is_class_v<int>, "int 不应该是类类型");

    struct A {};
    union B {};

    static_assert(is_class_v<A>, "A 应该是类类型");
    static_assert(!is_class_v<B>, "B 不应该是类类型");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "is_class_v<std::string>: "
                  << is_class_v<std::string> << std::endl;
        std::cout << "is_class_v<std::vector<int>>: "
                  << is_class_v<std::vector<int>> << std::endl;
        std::cout << "is_class_v<int>: " << is_class_v<int> << std::endl;
        std::cout << "is_class_v<A>: " << is_class_v<A> << std::endl;
        std::cout << "is_class_v<B>: " << is_class_v<B> << std::endl;
    }
}  // namespace isClassImpl

int main() {
    isClassUsage::test();
    isClassImpl::test();
    return 0;
}