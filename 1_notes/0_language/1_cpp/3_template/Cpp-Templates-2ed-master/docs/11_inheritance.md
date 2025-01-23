
## 指定模板参数

### 现在想指定某个实参，而其他参数依然使用默认实参

```cpp
namespace jc {

struct A {};
struct B {};
struct C {
  static constexpr int f() { return 1; }
};

struct Alias {
  using P1 = A;
  using P2 = B;
  using P3 = C;
};

template <typename T>
struct SetT1 : virtual Alias {
  using P1 = T;
};

template <typename T>
struct SetT2 : virtual Alias {
  using P2 = T;
};

template <typename T>
struct SetT3 : virtual Alias {
  using P3 = T;
};

// 由于不能从多个相同类直接继承，需要一个中间层用于区分
template <typename T, int N>
struct Mid : T {};

template <typename T1, typename T2, typename T3>
struct SetBase : Mid<T1, 1>, Mid<T2, 2>, Mid<T3, 3> {};

/* Alias 要被用作默认实参
 * 但 SetBase 会将其多次指定为 Mid 的基类
 * 为了防止多次继承产生二义性
 * 虚派生一个新类替代 Alias 作为默认实参
 */
struct Args : virtual Alias {};  // Args 即包含了别名 P1、P2、P3

template <typename T1 = Args, typename T2 = Args, typename T3 = Args>
struct MyClass {
  using Policies = SetBase<T1, T2, T3>;

  constexpr int f() { return Policies::P3::f(); }
};

struct D {
  static constexpr int f() { return 2; }
};

static_assert(MyClass{}.f() == 1);
static_assert(MyClass<SetT3<D>>{}.f() == 2);

}  // namespace jc

int main() {}
```
