#include <iostream>
#include <type_traits>

/*
2. has_const_x_getter 怎么用？
    has_const_x_getter 是一个模板元编程工具，用于在编译时检查类型是否具有一个 const 成员函数 x。
    它常用于 SFINAE（Substitution Failure Is Not An Error）技术中，根据条件选择合适的模板实例化。
*/

namespace hasConstXGetterUsage {
    // has_const_x_getter 的实现
    template <typename T>
    struct has_const_x_getter {
      private:
        static int detect(...);

        template <typename V>
        static auto detect(const V& v) -> decltype((int)(v.x()), void()) {}

      public:
        static constexpr bool value =
            std::is_void_v<decltype(detect(std::declval<T>()))>;
    };

    template <typename T>
    constexpr bool has_const_x_getter_v = has_const_x_getter<T>::value;

    // 示例类型
    struct A {
        int x() const;
    };
    struct B {
        int x();
    };
    struct C {
        void x() const;
    };
    struct D {
        int y() const;
    };
    struct E {};
    struct F {
        const int& x() const;
    };

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_const_x_getter_v<A>: "
                  << has_const_x_getter_v<A> << std::endl;  // 输出 true
        std::cout << "has_const_x_getter_v<B>: "
                  << has_const_x_getter_v<B> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<C>: "
                  << has_const_x_getter_v<C> << std::endl;  // 输出 true
        std::cout << "has_const_x_getter_v<D>: "
                  << has_const_x_getter_v<D> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<E>: "
                  << has_const_x_getter_v<E> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<F>: "
                  << has_const_x_getter_v<F> << std::endl;  // 输出 true
    }
}  // namespace hasConstXGetterUsage

////////////////////////////////////////////////////////////////////
namespace hasConstXGetterImpl {
    // has_const_x_getter 的实现
    template <typename T>
    struct has_const_x_getter {
      private:
        static int detect(...);

        template <typename V>
        static auto detect(const V& v) -> decltype((int)(v.x()), void()) {}

      public:
        static constexpr bool value =
            std::is_void_v<decltype(detect(std::declval<T>()))>;
    };

    template <typename T>
    constexpr bool has_const_x_getter_v = has_const_x_getter<T>::value;

    // 示例类型
    struct A {
        int x() const;
    };
    struct B {
        int x();
    };
    struct C {
        void x() const;
    };
    struct D {
        int y() const;
    };
    struct E {};
    struct F {
        const int& x() const;
    };

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_const_x_getter_v<A>: "
                  << has_const_x_getter_v<A> << std::endl;  // 输出 true
        std::cout << "has_const_x_getter_v<B>: "
                  << has_const_x_getter_v<B> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<C>: "
                  << has_const_x_getter_v<C> << std::endl;  // 输出 true
        std::cout << "has_const_x_getter_v<D>: "
                  << has_const_x_getter_v<D> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<E>: "
                  << has_const_x_getter_v<E> << std::endl;  // 输出 false
        std::cout << "has_const_x_getter_v<F>: "
                  << has_const_x_getter_v<F> << std::endl;  // 输出 true
    }
}  // namespace hasConstXGetterImpl

int main() {
    hasConstXGetterUsage::test();
    hasConstXGetterImpl::test();
    return 0;
}