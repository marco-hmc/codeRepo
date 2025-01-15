## 空基类优化（EBCO，Empty Base Class Optimization）

### 为了保证给类动态分配内存时有不同的地址，C++ 规定空类大小必须大于 0

```cpp
namespace jc {

struct A {};
struct B {};

static_assert(sizeof(A) > 0);
static_assert(sizeof(B) > 0);

}  // namespace jc

int main() {
  jc::A a;
  jc::B b;
  static_assert((void*)&a != (void*)&b);
}
```

### 一般编译器将空类大小设为 1 字节，对于空类存在继承关系的情况，如果支持 EBCO，可以优化派生类的空间占用大小

```cpp
/* 不支持 EBCO 的内存布局：
 * [    ] } A } B } C
 * [    ]     }   }
 * [    ]         }
 *
 * 支持 EBCO 的内存布局：
 * [    ] } A } B } C
 */

namespace jc {

struct A {
  using Int = int;
};

struct B : A {};
struct C : B {};

static_assert(sizeof(A) == 1);
static_assert(sizeof(A) == sizeof(B));
static_assert(sizeof(A) == sizeof(C));

}  // namespace jc

int main() {}
```

### 模板参数可能是空类

```cpp
namespace jc {

struct A {};
struct B {};

template <typename T, typename U>
struct C {
  T a;
  U b;
};

static_assert(sizeof(C<A, B>) == 2);

}  // namespace jc

int main() {}
```

### 为了利用 EBCO 压缩内存空间，可以将模板参数设为基类

```cpp
namespace jc {

struct A {};
struct B {};

template <typename T, typename U>
struct C : T, U {};

static_assert(sizeof(C<A, B>) == 1);

}  // namespace jc

int main() {}
```

### 但模板参数可能是相同类型，或者不一定是类，此时将其设为基类在实例化时会报错。如果已知一个模板参数类型为空类，把可能为空的类型参数与一个不为空的成员利用 EBCO 合并起来，即可把空类占用的空间优化掉

```cpp
namespace jc {

template <typename Base, typename Member>
class Pair : private Base {
 public:
  Pair(const Base& b, const Member& m) : Base(b), member_(m) {}

  const Base& first() const { return (const Base&)*this; }

  Base& first() { return (Base&)*this; }

  const Member& second() const { return this->member_; }

  Member& second() { return this->member_; }

 private:
  Member member_;
};

template <typename T>
struct Unoptimizable {
  T info;
  void* storage;
};

template <typename T>
struct Optimizable {
  Pair<T, void*> info_and_storage;
};

}  // namespace jc

struct A {};

static_assert(sizeof(jc::Unoptimizable<A>) == 2 * sizeof(void*));
static_assert(sizeof(jc::Optimizable<A>) == sizeof(void*));

int main() {}
```

## 指定模板参数

### 模板常常带有一长串类型参数，不过通常都设有默认值

```cpp
struct A {};
struct B {};
struct C {};

template <typename T1 = A, typename T2 = B, typename T3 = C>
struct MyClass {};
```

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
