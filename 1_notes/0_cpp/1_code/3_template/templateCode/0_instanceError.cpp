#include <cstdint>

#define WRONG_CODE_ENABLED 0
namespace _1_1 {

#if WRONG_CODE_ENABLED
const char* s = "abc";
template <char const* s>
class S {};

void foo2() { S<"abc"> i; }
#endif
}  // namespace _1_1

namespace _1_2 {
template <typename T>
class ClassB {
    T* a;
};

template <typename T>
class ClassC {
    T a;
};

struct StructA;     // Declared but not be defined
ClassB<StructA> d;  // Right
#if WRONG_CODE_ENABLED
ClassC<StructA> e;  // Wrong
#endif

}  // namespace _1_2