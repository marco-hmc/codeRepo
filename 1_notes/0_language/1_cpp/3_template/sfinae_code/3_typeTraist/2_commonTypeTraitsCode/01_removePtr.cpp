#include <iostream>
#include <type_traits>

/*
1. RemovePointer 怎么用？
    RemovePointer 是一个模板，用于递归地移除指针类型，直到不再是指针类型为止。
    它可以用于模板元编程中，处理嵌套指针类型。
*/

namespace removePointerUsage {
    // 定义 RemovePointer 模板
    template <typename T>
    struct RemovePointer {
        using Result = T;
    };

    template <typename T>
    struct RemovePointer<T*> {
        using Result = typename RemovePointer<T>::Result;
    };

    // 静态断言测试
    static_assert(std::is_same<RemovePointer<int>::Result, int>::value,
                  "RemovePointer<int>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int*>::Result, int>::value,
                  "RemovePointer<int*>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int**>::Result, int>::value,
                  "RemovePointer<int**>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int***>::Result, int>::value,
                  "RemovePointer<int***>::Result 应该是 int");

    void test() {
        std::cout << "RemovePointer<int>::Result: "
                  << typeid(RemovePointer<int>::Result).name() << std::endl;
        std::cout << "RemovePointer<int*>::Result: "
                  << typeid(RemovePointer<int*>::Result).name() << std::endl;
        std::cout << "RemovePointer<int**>::Result: "
                  << typeid(RemovePointer<int**>::Result).name() << std::endl;
        std::cout << "RemovePointer<int***>::Result: "
                  << typeid(RemovePointer<int***>::Result).name() << std::endl;
    }
}  // namespace removePointerUsage

////////////////////////////////////////////////////////////////////
namespace removePointerImpl {
    // RemovePointer 的实现
    template <typename T>
    struct RemovePointer {
        using Result = T;
    };

    template <typename T>
    struct RemovePointer<T*> {
        using Result = typename RemovePointer<T>::Result;
    };

    // 静态断言测试
    static_assert(std::is_same<RemovePointer<int>::Result, int>::value,
                  "RemovePointer<int>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int*>::Result, int>::value,
                  "RemovePointer<int*>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int**>::Result, int>::value,
                  "RemovePointer<int**>::Result 应该是 int");
    static_assert(std::is_same<RemovePointer<int***>::Result, int>::value,
                  "RemovePointer<int***>::Result 应该是 int");

    void test() {
        std::cout << "RemovePointer<int>::Result: "
                  << typeid(RemovePointer<int>::Result).name() << std::endl;
        std::cout << "RemovePointer<int*>::Result: "
                  << typeid(RemovePointer<int*>::Result).name() << std::endl;
        std::cout << "RemovePointer<int**>::Result: "
                  << typeid(RemovePointer<int**>::Result).name() << std::endl;
        std::cout << "RemovePointer<int***>::Result: "
                  << typeid(RemovePointer<int***>::Result).name() << std::endl;
    }
}  // namespace removePointerImpl

int main() {
    removePointerUsage::test();
    removePointerImpl::test();
    return 0;
}