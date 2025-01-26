#include <bitset>
#include <cassert>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

namespace ParamIsTemplate {

    template <typename T, template <typename...> class Container>
    void f(const Container<T>& /*unused*/) {}

    void test() { f(std::vector<int>{}); }

}  // namespace ParamIsTemplate

namespace ParamIsTemplate_complexVersion {

    // 模板类 Stack 的定义
    template <typename T,
              template <typename Elem, typename = std::allocator<Elem>>
              class Container = std::deque>
    class Stack {
      public:
        using reference = T&;
        using const_reference = const T&;

        // 友元声明
        template <typename, template <typename, typename> class>
        friend class Stack;

        // 赋值操作符
        template <typename U,
                  template <typename Elem2, typename = std::allocator<Elem2>>
                  class Container2>
        Stack<T, Container>& operator=(const Stack<U, Container2>& rhs);

        // 栈操作
        void push(const T& x);
        void pop();
        reference top();
        const_reference top() const;
        std::size_t size() const;
        bool empty() const;

      private:
        Container<T> container_;
    };

    // 赋值操作符的实现
    template <typename T, template <typename, typename> class Container>
    template <typename U, template <typename, typename> class Container2>
    inline Stack<T, Container>& Stack<T, Container>::operator=(
        const Stack<U, Container2>& rhs) {
        container_.assign(rhs.container_.begin(), rhs.container_.end());
        return *this;
    }

    // push 操作的实现
    template <typename T, template <typename, typename> class Container>
    inline void Stack<T, Container>::push(const T& x) {
        container_.emplace_back(x);
    }

    // pop 操作的实现
    template <typename T, template <typename, typename> class Container>
    inline void Stack<T, Container>::pop() {
        assert(!empty());
        container_.pop_back();
    }

    // top 操作的实现（非 const 版本）
    template <typename T, template <typename, typename> class Container>
    inline typename Stack<T, Container>::reference Stack<T, Container>::top() {
        assert(!empty());
        return container_.back();
    }

    // top 操作的实现（const 版本）
    template <typename T, template <typename, typename> class Container>
    inline typename Stack<T, Container>::const_reference
    Stack<T, Container>::top() const {
        assert(!empty());
        return container_.back();
    }

    // size 操作的实现
    template <typename T, template <typename, typename> class Container>
    inline std::size_t Stack<T, Container>::size() const {
        return container_.size();
    }

    // empty 操作的实现
    template <typename T, template <typename, typename> class Container>
    inline bool Stack<T, Container>::empty() const {
        return container_.empty();
    }

    void test() {
        Stack<std::string, std::deque> s;
        s.push("hello");
        s.push("world");
        assert(s.size() == 2);
        assert(s.top() == "world");
        s.pop();
        assert(s.size() == 1);
        assert(s.top() == "hello");
        s.pop();
        assert(s.empty());

        std::cout << "All tests passed!" << std::endl;
    }

}  // namespace ParamIsTemplate_complexVersion

namespace ParamIsNonType {

    template <bool IsSet = true, std::size_t N>
    std::size_t find_next(const std::bitset<N>& b, std::size_t cur) {
        for (std::size_t i = cur + 1; i < N; ++i) {
            if (!(b.test(i) ^ IsSet)) {
                return i;
            }
        }
        return N;
    }

    void test_find_next() {
        std::bitset<8> b{"10010111"};
        static constexpr int next_set[] = {1, 2, 4, 4, 7, 7, 7, 8, 8, 8};
        static constexpr int next_unset[] = {3, 3, 3, 5, 5, 6, 8, 8, 8, 8};

        for (std::size_t i = 0; i < std::size(next_set); ++i) {
            assert(ParamIsNonType::find_next<true>(b, i) == next_set[i]);
            assert(ParamIsNonType::find_next<false>(b, i) == next_unset[i]);
        }
    }
}  // namespace ParamIsNonType

namespace ParamFailExapmle {

    template <const char* s>
    class S {
      public:
        void print() { std::cout << s << std::endl; }
    };

    const char str[] = "abc";
    void syntax_literal_string_ok_example() {
        S<str> i;
        i.print();
    }

    void syntax_literal_string_fail_example() {
        // const char str[] = "abc";
        // S<str> i;
        // i.print();
    }
}  // namespace ParamFailExapmle

namespace ParamUndefinedType {
    template <typename T>
    class ClassB {
        T* a;
    };

    template <typename T>
    class ClassC {
        T a;
    };

    struct StructA;

    void syntax_undefined_type_fail_example() {
        // ClassC<StructA> e;  // 错误：StructA 未定义
    }

    void syntax_undefined_type_ok_example() {
        ClassB<StructA> d;
        struct StructA {};  // 定义 StructA
        ClassC<StructA> f;  // 正确：StructA 已定义
    }

}  // namespace ParamUndefinedType

namespace ParamOtherExample {

    constexpr const char* s1 = "hello";  // 内链接对象的指针
    extern const char s2[] = "world";    // 外链接
    const char s3[] = "down";            // 内链接

    template <const char* s>
    struct A {};

    // TemplateArg::A 测试
    void run() {
        static const char s4[] = "demo";  // 无链接
        // TemplateArg::A<"downdemo">{};              // 错误
        // TemplateArg::A<s1>{};                      // 错误
        // TemplateArg::A<s2>{};                      // C++11 允许
        // TemplateArg::A<s3>{};                      // C++14 允许
        // TemplateArg::A<s4>{};                      // C++17 允许
        std::cout << "TemplateArg::A test passed (commented out invalid cases)."
                  << std::endl;
    }
}  // namespace ParamOtherExample

namespace ParamIsPointerFailCase {
    template <int buf[5]>
    struct ArrPtr {};

    template <int fun()>
    struct FuncPtr {};

    void run() {
        int buffer[5] = {1, 2, 3, 4, 5};
        auto func = []() -> int { return 42; };

        // 错误：数组类型退化为指针类型
        // LexerAndFuncWrap::Lexer<buffer> lexer;
        // LexerAndFuncWrap::FuncWrap<func> funcWrap;
    }
}  // namespace ParamIsPointerFailCase

namespace ParamIsPointerOkCase {
    template <int* buf>
    struct ArrPtr {};

    template <int (*fun)()>
    struct FuncPtr {};

    void run() {
        static int buffer[5] = {1, 2, 3, 4, 5};
        // not ok
        // int buffer[5] = {1, 2, 3, 4, 5};
        auto func = []() -> int { return 42; };

        ParamIsPointerOkCase::ArrPtr<buffer> arrPtr;
        ParamIsPointerOkCase::FuncPtr<func> funcPtr;
    }
}  // namespace ParamIsPointerOkCase

int main() {
    ParamIsTemplate::test();
    ParamIsTemplate_complexVersion::test();
    ParamIsNonType::test_find_next();
    ParamFailExapmle::syntax_literal_string_ok_example();
    ParamFailExapmle::syntax_literal_string_fail_example();
    ParamUndefinedType::syntax_undefined_type_fail_example();
    ParamUndefinedType::syntax_undefined_type_ok_example();
    return 0;
}