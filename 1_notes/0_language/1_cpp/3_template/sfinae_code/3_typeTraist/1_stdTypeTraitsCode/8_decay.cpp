#include <iostream>
#include <type_traits>

/*
1. std::decay 怎么用？
    std::decay 是一个模板，用于将类型转换为它的“衰减”类型，模拟通过值传递参数时的类型转换。
    具体来说，它会移除引用、移除 cv 限定符，并将数组或函数类型转换为指针类型。
*/

namespace decayUsage {

    template <typename T>
    using decay_t = typename std::decay<T>::type;

    static_assert(std::is_same<decay_t<int>, int>::value, "int 应该是 int");
    static_assert(std::is_same<decay_t<int&>, int>::value, "int& 应该是 int");
    static_assert(std::is_same<decay_t<const int>, int>::value,
                  "const int 应该是 int");
    static_assert(std::is_same<decay_t<int[3]>, int*>::value,
                  "int[3] 应该是 int*");
    static_assert(std::is_same<decay_t<void(int)>, void (*)(int)>::value,
                  "void(int) 应该是 void(*)(int)");

    void test() {
        std::cout << "decay_t<int>: " << typeid(decay_t<int>).name()
                  << std::endl;
        std::cout << "decay_t<int&>: " << typeid(decay_t<int&>).name()
                  << std::endl;
        std::cout << "decay_t<const int>: " << typeid(decay_t<const int>).name()
                  << std::endl;
        std::cout << "decay_t<int[3]>: " << typeid(decay_t<int[3]>).name()
                  << std::endl;
        std::cout << "decay_t<void(int)>: " << typeid(decay_t<void(int)>).name()
                  << std::endl;
    }
}  // namespace decayUsage

namespace decayImpl {

    template <typename T>
    struct decay {
        using U = typename std::remove_reference<T>::type;
        using type = typename std::conditional<
            std::is_array<U>::value, typename std::remove_extent<U>::type*,
            typename std::conditional<
                std::is_function<U>::value, typename std::add_pointer<U>::type,
                typename std::remove_cv<U>::type>::type>::type;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;

    static_assert(std::is_same<decay_t<int>, int>::value, "int 应该是 int");
    static_assert(std::is_same<decay_t<int&>, int>::value, "int& 应该是 int");
    static_assert(std::is_same<decay_t<const int>, int>::value,
                  "const int 应该是 int");
    static_assert(std::is_same<decay_t<int[3]>, int*>::value,
                  "int[3] 应该是 int*");
    static_assert(std::is_same<decay_t<void(int)>, void (*)(int)>::value,
                  "void(int) 应该是 void(*)(int)");

    void test() {
        std::cout << "decay_t<int>: " << typeid(decay_t<int>).name()
                  << std::endl;
        std::cout << "decay_t<int&>: " << typeid(decay_t<int&>).name()
                  << std::endl;
        std::cout << "decay_t<const int>: " << typeid(decay_t<const int>).name()
                  << std::endl;
        std::cout << "decay_t<int[3]>: " << typeid(decay_t<int[3]>).name()
                  << std::endl;
        std::cout << "decay_t<void(int)>: " << typeid(decay_t<void(int)>).name()
                  << std::endl;
    }
}  // namespace decayImpl

int main() {
    decayUsage::test();
    decayImpl::test();
    return 0;
}