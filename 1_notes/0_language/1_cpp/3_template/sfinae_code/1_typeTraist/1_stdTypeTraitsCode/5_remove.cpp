#include <iostream>
#include <type_traits>

/*
1. std::remove_reference 怎么用？
    std::remove_reference 是一个模板元编程工具，用于移除类型的引用修饰符。
    如果给定的类型是引用类型，则返回去掉引用后的类型；否则返回原类型。

2. std::remove_const 怎么用？
    std::remove_const 是一个模板元编程工具，用于移除类型的 const 修饰符。
    如果给定的类型是 const 类型，则返回去掉 const 后的类型；否则返回原类型。
*/

namespace removeReferenceUsage {

    template <typename T>
    using remove_reference_t = typename std::remove_reference<T>::type;

    static_assert(std::is_same<remove_reference_t<int>, int>::value,
                  "int 应该是 int");
    static_assert(std::is_same<remove_reference_t<int&>, int>::value,
                  "int& 应该是 int");
    static_assert(std::is_same<remove_reference_t<int&&>, int>::value,
                  "int&& 应该是 int");

    void test() {
        std::cout << "remove_reference_t<int>: "
                  << typeid(remove_reference_t<int>).name() << std::endl;
        std::cout << "remove_reference_t<int&>: "
                  << typeid(remove_reference_t<int&>).name() << std::endl;
        std::cout << "remove_reference_t<int&&>: "
                  << typeid(remove_reference_t<int&&>).name() << std::endl;
    }
}  // namespace removeReferenceUsage

namespace removeConstUsage {

    template <typename T>
    using remove_const_t = typename std::remove_const<T>::type;

    static_assert(std::is_same<remove_const_t<int>, int>::value,
                  "int 应该是 int");
    static_assert(std::is_same<remove_const_t<const int>, int>::value,
                  "const int 应该是 int");
    static_assert(std::is_same<remove_const_t<const int&>, const int&>::value,
                  "const int& 应该是 const int&");

    void test() {
        std::cout << "remove_const_t<int>: "
                  << typeid(remove_const_t<int>).name() << std::endl;
        std::cout << "remove_const_t<const int>: "
                  << typeid(remove_const_t<const int>).name() << std::endl;
        std::cout << "remove_const_t<const int&>: "
                  << typeid(remove_const_t<const int&>).name() << std::endl;
    }
}  // namespace removeConstUsage

namespace removeReferenceImpl {

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    static_assert(std::is_same<remove_reference_t<int>, int>::value,
                  "int 应该是 int");
    static_assert(std::is_same<remove_reference_t<int&>, int>::value,
                  "int& 应该是 int");
    static_assert(std::is_same<remove_reference_t<int&&>, int>::value,
                  "int&& 应该是 int");

    void test() {
        std::cout << "remove_reference_t<int>: "
                  << typeid(remove_reference_t<int>).name() << std::endl;
        std::cout << "remove_reference_t<int&>: "
                  << typeid(remove_reference_t<int&>).name() << std::endl;
        std::cout << "remove_reference_t<int&&>: "
                  << typeid(remove_reference_t<int&&>).name() << std::endl;
    }
}  // namespace removeReferenceImpl

namespace removeConstImpl {

    template <typename T>
    struct remove_const {
        using type = T;
    };

    template <typename T>
    struct remove_const<const T> {
        using type = T;
    };

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

    static_assert(std::is_same<remove_const_t<int>, int>::value,
                  "int 应该是 int");
    static_assert(std::is_same<remove_const_t<const int>, int>::value,
                  "const int 应该是 int");
    static_assert(std::is_same<remove_const_t<const int&>, const int&>::value,
                  "const int& 应该是 const int&");

    void test() {
        std::cout << "remove_const_t<int>: "
                  << typeid(remove_const_t<int>).name() << std::endl;
        std::cout << "remove_const_t<const int>: "
                  << typeid(remove_const_t<const int>).name() << std::endl;
        std::cout << "remove_const_t<const int&>: "
                  << typeid(remove_const_t<const int&>).name() << std::endl;
    }
}  // namespace removeConstImpl

int main() {
    removeReferenceUsage::test();
    removeConstUsage::test();
    removeReferenceImpl::test();
    removeConstImpl::test();
    return 0;
}