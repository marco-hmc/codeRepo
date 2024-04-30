# include<iostream>

template<typename T>
struct has_type {
    template<typename C>
    static char test(typename C::type*);

    template<typename C>
    static int test(...);

    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

struct A { typedef int type; };
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << has_type<A>::value << std::endl; // 输出true
    std::cout << has_type<B>::value << std::endl; // 输出false
    return 0;
}

// template<typename T>
// struct has_function {
//     template<typename C>
//     static char test(decltype(&C::function));

//     template<typename C>
//     static int test(...);

//     static const bool value = sizeof(test<T>(0)) == sizeof(char);
// };

// struct C { void function() {} };
// struct D { };

// int main() {
//     std::cout << std::boolalpha;
//     std::cout << has_function<C>::value << std::endl; // 输出true
//     std::cout << has_function<D>::value << std::endl; // 输出false
//     return 0;
// }
