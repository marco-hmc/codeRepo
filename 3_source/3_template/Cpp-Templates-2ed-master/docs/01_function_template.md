## 两阶段编译（Two-Phase Translation）

## [模板实参推断（Template Argument Deduction）](https://en.cppreference.com/w/cpp/language/template_argument_deduction)

## [type traits](https://en.cppreference.com/w/cpp/header/type_traits)

## 重载

* 注意不能返回 C-style 字符串的引用
// QUES_1

```cpp
namespace jc {

template <typename T>
const T& f(const char* s) {
  return s;
}

}  // namespace jc

int main() {
  const char* s = "downdemo";
  jc::f<const char*>(s);  // 错误：返回临时对象的引用
}
```

## 用于原始数组与字符串字面值（string literal）的模板

* 字符串字面值传引用会推断为字符数组，为此需要为原始数组和字符串字面值提供特定处理的模板

```cpp
#include <cassert>
#include <cstddef>

namespace jc {

template <typename T, typename U>
constexpr bool less(const T& a, const U& b) {
  return a < b;
}

template <typename T, std::size_t M, std::size_t N>
constexpr bool less(T (&a)[M], T (&b)[N]) {
  for (std::size_t i = 0; i < M && i < N; ++i) {
    if (a[i] < b[i]) {
      return true;
    }
    if (b[i] < a[i]) {
      return false;
    }
  }
  return M < N;
}

}  // namespace jc

static_assert(jc::less(0, 42));
static_assert(!jc::less("down", "demo"));
static_assert(jc::less("demo", "down"));

int main() {}
```

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

## 零初始化（Zero Initialization）

* 使用模板时常希望模板类型的变量已经用默认值初始化，但内置类型无法满足要求。解决方法是显式调用内置类型的默认构造函数

```cpp
namespace jc {

template <typename T>
constexpr T default_value() {
  T x{};
  return x;
}

template <typename T>
struct DefaultValue {
  constexpr DefaultValue() : value() {}
  T value;
};

template <typename T>
struct DefaultValue2 {
  T value{};
};

static_assert(default_value<bool>() == false);
static_assert(default_value<char>() == 0);
static_assert(default_value<int>() == 0);
static_assert(default_value<double>() == 0);

static_assert(DefaultValue<bool>{}.value == false);
static_assert(DefaultValue<char>{}.value == 0);
static_assert(DefaultValue<int>{}.value == 0);
static_assert(DefaultValue<double>{}.value == 0);

static_assert(DefaultValue2<bool>{}.value == false);
static_assert(DefaultValue2<char>{}.value == 0);
static_assert(DefaultValue2<int>{}.value == 0);
static_assert(DefaultValue2<double>{}.value == 0);

}  // namespace jc

int main() {}
```
