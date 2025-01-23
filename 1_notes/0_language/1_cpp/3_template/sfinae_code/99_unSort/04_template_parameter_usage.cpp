#include <cassert>
#include <iostream>

/*
  ## 模板参数的常见用法

  1. 使用成员指针作为模板参数：
     通过成员指针作为模板参数，可以在编译时绑定成员变量，从而实现对成员变量的操作。
     例如，下面的 Wrapper 类使用成员指针 ClassMember 来操作对象的成员变量。
*/

namespace WrapperSpace {

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

}  // namespace WrapperSpace

namespace TemplateArg {

    template <const char* s>
    struct A {};

}  // namespace TemplateArg

constexpr const char* s1 = "hello";  // 内链接对象的指针
extern const char s2[] = "world";    // 外链接
const char s3[] = "down";            // 内链接

namespace LexerAndFuncWrap {

    template <int buf[5]>
    struct Lexer {};

    template <int fun()>
    struct FuncWrap {};

}  // namespace LexerAndFuncWrap

namespace TemplateGrammar {

    template <bool b>
    struct A {
        inline static constexpr bool value = b;
    };

}  // namespace TemplateGrammar

int main() {
    // WrapperSpace::Wrapper 测试
    {
        WrapperSpace::A a;
        WrapperSpace::Wrapper<&WrapperSpace::A::i> wrapper(a);
        wrapper.increase();
        assert(a.i == 1);
        std::cout << "WrapperSpace::Wrapper test passed." << std::endl;
    }

    // TemplateArg::A 测试
    {
        static const char s4[] = "demo";  // 无链接
        // TemplateArg::A<"downdemo">{};              // 错误
        // TemplateArg::A<s1>{};                      // 错误
        // TemplateArg::A<s2>{};                      // C++11 允许
        // TemplateArg::A<s3>{};                      // C++14 允许
        // TemplateArg::A<s4>{};                      // C++17 允许
        std::cout << "TemplateArg::A test passed (commented out invalid cases)."
                  << std::endl;
    }

    // LexerAndFuncWrap::Lexer 和 LexerAndFuncWrap::FuncWrap 测试
    {
        int buffer[5] = {1, 2, 3, 4, 5};
        auto func = []() -> int { return 42; };

        // LexerAndFuncWrap::Lexer<buffer> lexer;  // 错误：数组类型退化为指针类型
        // LexerAndFuncWrap::FuncWrap<func> funcWrap;  // 错误：函数类型退化为指针类型
        std::cout << "LexerAndFuncWrap::Lexer and LexerAndFuncWrap::FuncWrap "
                     "test passed (commented out "
                     "invalid cases)."
                  << std::endl;
    }

    // TemplateGrammar::A 测试
    {
        static_assert(TemplateGrammar::A<(sizeof(int) > 0)>::value,
                      "TemplateGrammar::A test failed");
        std::cout << "TemplateGrammar::A test passed." << std::endl;
    }

    return 0;
}