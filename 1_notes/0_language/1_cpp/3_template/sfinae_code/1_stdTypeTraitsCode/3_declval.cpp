#include <iostream>
#include <type_traits>

/*
1. std::declval 怎么用？
    std::declval 是一个在编译时用于类型推断的工具，它可以用来获取一个类型的引用，而不需要实际构造该类型的对象。
    这在处理无法默认构造或不想构造对象的类型时特别有用。
*/

namespace declvalUsage {
    // 示例类
    class MyClass {
      public:
        int myFunction() const { return 42; }
    };

    // 用于在编译时推断成员函数的返回类型
    template <typename T>
    auto testFunctionReturnType() -> decltype(std::declval<T>().myFunction()) {
        // 注意：这里不会实际调用 T::myFunction，因此可以用于不可默认构造的类型
        return std::declval<T>().myFunction();
    }

    // 验证推断的类型是否为 int
    static_assert(
        std::is_same<decltype(testFunctionReturnType<MyClass>()), int>::value,
        "返回类型应为 int");

    void test() { std::cout << "推断的返回类型为 int" << std::endl; }
}  // namespace declvalUsage

////////////////////////////////////////////////////////////////////
namespace declvalImpl {
    // std::declval 的实现
    template <class T>
    std::add_rvalue_reference_t<T> declval() noexcept;  // 仅声明，无需定义

    // 示例类
    class MyClass {
      public:
        int myFunction() const { return 42; }
    };

    // 用于在编译时推断成员函数的返回类型
    template <typename T>
    auto testFunctionReturnType() -> decltype(declval<T>().myFunction()) {
        // 注意：这里不会实际调用 T::myFunction，因此可以用于不可默认构造的类型
        return declval<T>().myFunction();
    }

    // 验证推断的类型是否为 int
    static_assert(
        std::is_same<decltype(testFunctionReturnType<MyClass>()), int>::value,
        "返回类型应为 int");

    void test() { std::cout << "推断的返回类型为 int" << std::endl; }
}  // namespace declvalImpl

int main() {
    declvalUsage::test();
    declvalImpl::test();
    return 0;
}