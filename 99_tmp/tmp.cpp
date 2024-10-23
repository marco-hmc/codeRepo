#include <cstdint>

#define WRONG_CODE_ENABLED 0

namespace _2_2_3 {
template <typename T>
class TypeToID {
   public:
    static int const ID = -1;
};

class B {};

template <>
class TypeToID<void()>;  // 函数的TypeID
template <>
class TypeToID<int[3]>;  // 数组的TypeID
template <>
class TypeToID<int(int[3])>;  // 这是以数组为参数的函数的TypeID
template <>
class TypeToID<int (B::*[3])(
    void*, float[2])>;  // 我也不知道这是什么了，自己看着办吧。

template <>
class TypeToID<int const* volatile* const volatile>;
}  // namespace _2_2_3