#include <iostream>
#include <type_traits>

/*
2. std::enable_if 怎么用？
    std::enable_if 是一个模板元编程工具，用于在编译时根据条件启用或禁用模板。
    它常用于 SFINAE（Substitution Failure Is Not An Error）技术中，根据条件选择合适的模板实例化。
*/

namespace enableIfUsage {

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    conditionalFunction(T value) {
        return value * 2;
    }

    template <typename T>
    typename std::enable_if<!std::is_integral<T>::value, T>::type
    conditionalFunction(T value) {
        return value + 0.5;
    }

    void test() {
        std::cout << "conditionalFunction(10): " << conditionalFunction(10)
                  << std::endl;
        std::cout << "conditionalFunction(10.5): " << conditionalFunction(10.5)
                  << std::endl;
    }
}  // namespace enableIfUsage

namespace enableIfImpl {

    template <bool B, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <typename T>
    typename enableIfImpl::enable_if<std::is_integral<T>::value, T>::type
    conditionalFunction(T value) {
        return value * 2;
    }

    template <typename T>
    typename enableIfImpl::enable_if<!std::is_integral<T>::value, T>::type
    conditionalFunction(T value) {
        return value + 0.5;
    }

    void test() {
        std::cout << "conditionalFunction(10): " << conditionalFunction(10)
                  << std::endl;
        std::cout << "conditionalFunction(10.5): " << conditionalFunction(10.5)
                  << std::endl;
    }
}  // namespace enableIfImpl

int main() {
    enableIfUsage::test();
    enableIfImpl::test();
    return 0;
}