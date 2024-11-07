#include <cstdint>

#define WRONG_CODE_ENABLED 0

namespace _1_1 {

#if WRONG_CODE_ENABLED
const char *s = "abc";
template <char const *s> class S {};

void foo2() { S<"abc"> i; }
#endif
} // namespace _1_1

namespace _1_2 {

template <typename T> class ClassB {
  T *a;
};

template <typename T> class ClassC {
  T a;
};

struct StructA;    // Declared but not be defined
ClassB<StructA> d; // Right
#if WRONG_CODE_ENABLED
ClassC<StructA> e; // Wrong
#endif

} // namespace _1_2

/*
1. 字符串字面值不能直接作为模板参数：C++
标准不允许字符串字面值直接作为模板参数传递，因为它们的地址在编译时是未知的。

2.
未定义类型作为模板参数：模板类可以接受未定义的类型作为模板参数，但前提是模板类不需要知道该类型的定义。例如，指针类型可以接受未定义的类型，而对象类型则不能。
*/
