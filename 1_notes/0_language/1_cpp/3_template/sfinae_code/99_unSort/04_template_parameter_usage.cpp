#include <cassert>
#include <iostream>

/*
  ## 模板参数的常见用法

  1. 使用成员指针作为模板参数：
     通过成员指针作为模板参数，可以在编译时绑定成员变量，从而实现对成员变量的操作。
     例如，下面的 Wrapper 类使用成员指针 ClassMember 来操作对象的成员变量。
*/

namespace WrapperImpl {
    template <typename>
    struct get_class;

    template <typename ClassType, typename MemberType>
    struct get_class<MemberType ClassType::*> {
        using type = ClassType;
    };

    template <typename T>
    using get_class_t = typename get_class<T>::type;

    template <auto ClassMember>
    class Wrapper {
      public:
        Wrapper(get_class_t<decltype(ClassMember)>& obj) : obj_(obj) {}

        void increase() { ++(obj_.*ClassMember); }

      private:
        get_class_t<decltype(ClassMember)>& obj_;
    };

    struct A {
        int i = 0;
    };

    void run() {
        A a;
        Wrapper<&A::i> wrapper(a);
        wrapper.increase();
        assert(a.i == 1);
        std::cout << "Wrapper test passed." << std::endl;
    }
}  // namespace WrapperImpl

namespace LexerAndFuncWrap {

    template <int buf[5]>
    struct Lexer {};

    template <int fun()>
    struct FuncWrap {};

    void run() {
        int buffer[5] = {1, 2, 3, 4, 5};
        auto func = []() -> int { return 42; };

        // LexerAndFuncWrap::Lexer<buffer> lexer;  // 错误：数组类型退化为指针类型
        // LexerAndFuncWrap::FuncWrap<func> funcWrap;  // 错误：函数类型退化为指针类型
    }
}  // namespace LexerAndFuncWrap

int main() {
    WrapperImpl::run();
    LexerAndFuncWrap::run();

    return 0;
}
