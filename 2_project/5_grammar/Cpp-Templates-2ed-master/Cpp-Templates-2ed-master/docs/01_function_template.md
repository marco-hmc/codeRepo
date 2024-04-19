
* 各种类型的数组参数对应的偏特化

```cpp
#include <cstddef>

namespace jc {

template <typename T>
struct A;

template <typename T, std::size_t N>
struct A<T[N]> {
  static constexpr int value = 1;
};

template <typename T, std::size_t N>
struct A<T (&)[N]> {
  static constexpr int value = 2;
};

template <typename T>
struct A<T[]> {
  static constexpr int value = 3;
};

template <typename T>
struct A<T (&)[]> {
  static constexpr int value = 4;
};

template <typename T>
struct A<T*> {
  static constexpr int value = 5;
};

template <typename T1, typename T2, typename T3>
constexpr void test(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1,
                    T2& x2, T3&& x3) {
  static_assert(A<decltype(a1)>::value == 5);  // A<T*>
  static_assert(A<decltype(a2)>::value == 5);  // A<T*>
  static_assert(A<decltype(a3)>::value == 2);  // A<T(&)[N]>
  static_assert(A<decltype(x0)>::value == 4);  // A<T(&)[]>
  static_assert(A<decltype(x1)>::value == 5);  // A<T*>
  static_assert(A<decltype(x2)>::value == 4);  // A<T(&)[]>
  static_assert(A<decltype(x3)>::value == 4);  // A<T(&)[]>
}

}  // namespace jc

int main() {
  int a[42];
  static_assert(jc::A<decltype(a)>::value == 1);
  extern int x[];  // 传引用时将变为 int(&)[]
  static_assert(jc::A<decltype(x)>::value == 3);  // A<T[]>
  jc::test(a, a, a, x, x, x, x);
}

int x[] = {1, 2, 3};  // 定义前置声明的数组
```
