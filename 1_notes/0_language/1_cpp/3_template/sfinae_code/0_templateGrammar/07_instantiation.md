## 隐式实例化（Implicit Instantiation）

### 1. 隐式实例化的基本概念

当编译器遇到模板特化时，它会根据所提供的模板实参来替换模板参数，从而生成对应的特化代码。通常情况下，如果我们声明一个类模板的指针或引用类型，不需要看到类模板的完整定义。但是，如果我们要访问类模板特化的成员，或想知道模板特化的大小，就必须能够访问到模板定义。

#### 示例：隐式实例化与成员访问

```cpp
namespace jc {

template <typename T>
struct A;

A<int>* p = 0;  // OK：只需类模板声明，不需要定义

template <typename T>
struct A {
  void f();
};

void g(A<int>& a) {  // 只使用类模板声明
  a.f();             // 需要类模板定义，才能调用 A::f()
}

template <typename T>
void A<T>::f() {}

}  // namespace jc

int main() {}
```

在上面的示例中，声明 `A<int>* p` 时，编译器不需要类模板的完整定义。然而，当我们调用 `a.f()` 时，编译器就需要访问 `A<int>` 的完整定义，以确保 `f()` 函数存在并能被正确调用。

### 2. 函数重载与模板实例化

当函数重载时，如果候选函数的参数是类类型，则该类的完整定义必须可见。如果重载函数的参数是类模板，为了检查重载匹配，编译器会实例化类模板。这可能会导致额外的实例化和编译负担。

#### 示例：函数重载和模板实例化

```cpp
namespace jc {

template <typename T>
struct A {
  A(int);  // 类模板的构造函数
};

void f(A<double>) {}
void f(int) {}

}  // namespace jc

int main() {
  jc::f(42);  // 调用 f(int)，但会实例化 A<double>，即使没被使用
}
```

在这个例子中，虽然 `jc::f(42)` 只调用了 `f(int)`，但编译器仍然会实例化 `A<double>`，因为 `f(A<double>)` 作为候选函数之一必须被检查。

## 延迟实例化（Lazy Instantiation）

### 1. 延迟实例化的概念

延迟实例化是指模板的实例化不会在模板声明时发生，而是等到模板被实际使用时才进行实例化。编译器只会实例化模板的成员声明，而不会立即实例化成员定义。特殊情况包括匿名 `union` 和虚函数，匿名 `union` 的成员会被实例化，而虚函数是否实例化则取决于具体实现。

#### 示例：延迟实例化与错误检查

```cpp
namespace jc {

template <int N>
struct A {
  int a[N];  // 编译器假设 N 是正整数，如果 N <= 0 将导致错误
};

template <typename T, int N>
struct B {
  void f() {
    A<N> a;  // 如果 N <= 0，调用时会出错
  }

  struct Nested {
    A<N> a;  // N <= 0 时也会出错
  };

  // union 成员会被生成，即使不调用也会导致实例化
  union {
    A<N> a;  // N <= 0 会导致错误
  };
};

}  // namespace jc

int main() {
  jc::B<int, -1> b;
  //   b.f();  // 调用时出错
  //   jc::B<int, -1>::Nested{};  // 错误
}
```

在上面的代码中，模板 `B<int, -1>` 中的 `A<N>` 会在调用时才被实例化。如果 `N <= 0`，就会出现编译错误。即使某些成员（如 `error()` 函数）没有被调用，编译器仍然会在实例化时检查 `A<N>` 是否能正确生成。如果 `A<N>` 的实例化失败（如 `N` 为负数），编译器会报告错误。

### 2. 特殊情况：虚函数与匿名 `union`

- **虚函数**：虚函数只有在实际调用时才会实例化。如果虚函数没有定义，调用时会导致链接错误。
- **匿名 `union`**：即使匿名 `union` 中的成员没有被使用，编译器也会实例化它们。

## 两阶段查找（Two-Phase Lookup）

### 1. 两阶段查找的概念

C++ 编译器解析模板时，存在两阶段查找的过程。由于模板参数类型的依赖关系，编译器无法在模板解析阶段完全解析所有名称，尤其是**依赖名称**（dependent name）。因此，编译器会在模板实例化时再次查找这些依赖名称。两阶段查找的过程如下：

- **第一阶段**：模板解析阶段，编译器会查找所有的**non-dependent name**（非依赖名称）和部分**dependent name**（受依赖名称）。对于某些名称，编译器无法在模板解析时完全解析，必须等到实例化时再进行查找。
  
- **第二阶段**：模板实例化阶段，称为**实例化点（POI，Point of Instantiation）**。在这一阶段，编译器会查找所有的**dependent name**（受依赖名称），并再次进行**非依赖名称**的查找。

#### 示例：两阶段查找

```cpp
namespace jc {

template <typename T>
struct A {
  void f() {
    // 在实例化时查找 T::value
    T::value;  // 受依赖名称
  }
};

template <typename T>
struct B {
  void g() {
    A<T> a;
    a.f();  // 调用 f() 时，T::value 会在实例化时查找
  }
};

}  // namespace jc

int main() {
  jc::B<int> b;
  b.g();  // 在实例化时查找 T::value
}
```

在这个例子中，`A<T>::f()` 中的 `T::value` 是一个受依赖名称。编译器在模板解析阶段无法完全确定 `T::value` 是否存在，直到模板实例化时，编译器才会查找 `T::value` 是否有效。

### 2. 查找过程的细节

- **Unqualified Name Lookup**：对于非依赖名称，编译器在模板解析阶段会进行**非限定名称查找**（unqualified name lookup）。这意味着编译器会尝试查找该名称是否在当前作用域中定义。
  
- **ADL（Argument-Dependent Lookup）**：当进行函数查找时，编译器会使用**参数依赖查找**（ADL）来决定是否匹配函数模板。

### 总结

- **隐式实例化**：模板的实例化通常在首次使用时发生，但对于某些成员和操作，编译器需要完整的模板定义。
  
- **延迟实例化**：模板成员的定义通常在模板实例化时才会进行。某些特殊情况（如匿名 `union` 和虚函数）会在模板声明时就进行实例化。
  
- **两阶段查找**：编译器在模板解析阶段和实例化阶段分别进行查找，以处理受依赖名称和非依赖名称的查找问题。


## line ----------------------------------------------------

## POI（Points of Instantiation）

### 1. POI 的基本概念

**POI（Points of Instantiation）** 是指编译器在模板实例化过程中，访问模板的声明或定义的某个位置。这时，编译器会在代码中插入相应的模板实例。POI 是编译器实例化模板时的“触发点”，即模板实例化发生的位置。

#### 示例：POI 与二阶段查找

```cpp
namespace jc {

struct A {
  A(int i) : i(i) {}
  int i;
};

A operator-(const A& a) { return A{-a.i}; }

bool operator<(const A& lhs, const A& rhs) { return lhs.i < rhs.i; }

using Int = A;  // 若使用 int 而不使用 A，则无法使用 ADL 找到 g

template <typename T>
void f(T i) {
  if (i < 0) {
    g(-i);  // POI: 二阶段查找，T 为 A 时可以使用 ADL，T 为 int 时找不到 g
  }
}

void g(Int) {  // 这里的 g 是 POI
  f<Int>(42);  // 调用点
}

}  // namespace jc

int main() {}
```

在上述代码中，当调用 `f<Int>(42)` 时，编译器会在 `f` 的调用位置实例化 `f<Int>`，这时编译器会查找 `g()`。如果 `T` 是 `A`，则通过 **ADL（Argument-Dependent Lookup）** 找到 `g()`，否则无法找到。

### 2. POI 的位置限制

类模板实例的 POI 位置只能在包含该实例声明或定义之前的最近作用域内。

#### 示例：POI 的位置限制

```cpp
namespace jc {

template <typename T>
struct A {
  T x;
};

// POI 位置
int f() {
  // 不能作为 POI，因为 A<int> 的定义不能出现在函数作用域内
  return sizeof(A<int>);
  // 不能作为 POI，因为 sizeof(A<int>) 在函数作用域内无法解析
}

}  // namespace jc

int main() {}
```

在上面的代码中，`sizeof(A<int>)` 无法在 `f()` 函数中成为 POI，因为类模板 `A<int>` 的定义必须在该位置之前才能正确实例化。

### 3. 模板实例化的连锁效应

实例化一个模板时，可能会触发其他模板的实例化。这种“连锁”效应会导致多个 POI。

#### 示例：模板实例化引发的连锁 POI

```cpp
namespace jc {

template <typename T>
struct A {
  using type = int;
};

template <typename T>
void f() {
  A<char>::type a = 0;  // A<char> 的 POI
  typename A<T>::type b = 0;  // A<T> 的 POI
}

}  // namespace jc

int main() {
  jc::f<double>();  // f<double> 的 POI
  // A<double> 的 POI
  // f<double> 的 POI
}
```

在这个例子中，调用 `jc::f<double>()` 会导致 `A<double>` 和 `A<char>` 的实例化。因此，`f<double>` 和 `A<double>` 的 POI 会在不同的点产生。

### 4. POI 的重复性与优化

一个编译单元通常会包含一个模板实例的多个 POI。然而，对于类模板实例化，通常每个编译单元只会保留首个 POI，其他 POI 会被忽略。对于函数模板和变量模板的实例化，所有 POI 都会被保留。

## 模板的链接（Linkage of Templates）

### 1. 类模板的名称冲突

类模板的名称不能与其他实例的名称冲突。

#### 示例：名称冲突

```cpp
namespace jc {

int A;

class A;  // OK：两者名称在不同的作用域内

int B;

template <typename T>
struct B;  // 错误：模板名称与非模板名称冲突

struct C;

template <typename T>
struct C;  // 错误：模板名称与非模板名称冲突

}  // namespace jc

int main() {}
```

在上面的代码中，`struct A` 和 `int A` 的名称冲突会导致编译错误。同样，模板名称 `B` 和 `C` 与非模板类型冲突也会导致错误。

### 2. 模板不能具有 C 链接

模板不能与 C 语言的链接规范（C linkage）一起使用。

#### 示例：C 链接错误

```cpp
namespace jc {

extern "C++" template <typename T>
void normal();  // 正确：默认 C++ 链接规范

extern "C" template <typename T>
void invalid();  // 错误：不能使用 C 链接

extern "Java" template <typename T>
void java_link();  // 非标准链接，某些编译器可能支持

}  // namespace jc

int main() {}
```

模板不能使用 C 链接规范（`extern "C"`）。如果使用 `extern "C++"`，则为默认的 C++ 链接规范。

### 3. 模板的外链接与静态链接

模板通常具有外链接（**external linkage**）。然而，**静态模板函数**（即加上 `static` 关键字的模板函数）会具有内部链接（**internal linkage**），这使得它在当前翻译单元内可见，但在其他翻译单元中不可见。

#### 示例：静态与外部链接

```cpp
template <typename T>  // 外部链接
void external();

template <typename T>  // 内部链接
static void internal();

namespace {
template <typename>  // 内部链接
void other_internal();
}

struct {
  template <typename T>  // 无链接：不能被重复声明
  void f(T) {}
} x;

int main() {}
```

### 4. 链接错误

与普通函数不同，如果模板的声明和实现分离，通常会出现链接错误，因为编译器在函数调用处没有看到模板实例化的定义，只会假设在其他地方提供了定义，链接器依赖该引用进行解决。

#### 示例：模板声明与实现分离导致链接错误

```cpp
// a.hpp
#pragma once

namespace jc {

template <typename T>
class A {
 public:
  void f();
};

}  // namespace jc

// a.cpp
#include "a.hpp"

namespace jc {

template <typename T>
void A<T>::f() {}

}  // namespace jc

// main.cpp
#include "a.hpp"

int main() {
  jc::A<int>{}.f();  // 链接错误
}
```

上面的代码会导致链接错误，因为 `A<int>::f()` 的实现只出现在 `a.cpp` 中，但在 `main.cpp` 中调用时，编译器无法找到该定义。

### 5. 推荐的做法：在头文件中实现模板

为了避免链接错误，通常建议在头文件中直接实现模板。

#### 示例：头文件中实现模板

```cpp
// a.hpp
#pragma once

namespace jc {

template <typename T>
class A {
 public:
  void f();
};

template <typename T>
inline void A<T>::f() {}

}  // namespace jc

// main.cpp
#include "a.hpp"

int main() {
  jc::A<int>{}.f();
}
```

通过这种方式，模板的实现会在头文件中直接提供，避免了链接错误。

## 显式实例化（Explicit Instantiation）

显式实例化是手动指定模板实例化特定类型的机制。它允许将模板的定义与实例化分离，并控制哪些模板类型在编译期间被实例化。

### 1. 显式实例化的基本用法

在头文件中使用 `extern` 声明显式实例化，告知用户哪些类型的模板被实例化。

#### 示例：显式实例化

```cpp
// a.hpp
#pragma once

namespace jc {

template <typename T>
class A {
 public:
  void f();
};

extern template class A<int>;         // 声明 A<int> 的显式实例化
extern template void A<double>::f();  // 声明 A<double>::f() 的显式实例化

}  // namespace jc

// a.cpp
#include "a.hpp"

namespace jc {

template <typename T>
void A<T>::f() {}

template class A<int>;  // 实例化 A<int>
template void A<double>::f();  // 实例化 A<double>::f()

}  // namespace jc

// main.cpp
#include "a.hpp"

int main() {
  jc::A<int>{}.f();
  jc::A<double>{}.f();
}
```

### 2. 分离实例化实现

显式实例化可以将实例化过程提取到单独的源文件中，这有助于减小头文件的大小和提高编译效率。

#### 示例：分离显式实例化实现

```cpp
// a.hpp
#pragma once

namespace jc {

template <typename T>
class A {


 public:
  void f();
};

extern template class A<int>;
extern template void A<double>::f();

}  // namespace jc

// a.cpp
#include "a.hpp"

namespace jc {

template <typename T>
void A<T>::f() {}

template class A<int>;
template void A<double>::f();

}  // namespace jc

// a_init.cpp
#include "a.cpp"

namespace jc {

template class A<int>;
template void A<double>::f();

}  // namespace jc

// main.cpp
#include "a.hpp"

int main() {
  jc::A<int>{}.f();
  jc::A<double>{}.f();
}
```

### 3. 显式实例化不会影响类型推断

显式实例化只影响模板实例化，并不会影响类型推断规则。模板实例化和类型推断始终保持一致。

#### 示例：显式实例化与类型推断

```cpp
namespace jc {

template <typename T>
void f(T, T) {}

template void f<double>(double, double);

}  // namespace jc

int main() {
  jc::f<double>(1, 3.14);  // OK
  jc::f(1, 3.14);  // 错误：推断类型不一致，不存在普通函数 f(double, double)
}
```

### 4. 显式实例化与特化冲突

显式实例化后，不能为相同的类型定义特化。

#### 示例：显式实例化与特化冲突

```cpp
namespace jc {

template <typename T>
struct A {
  void f();
};

template <typename T>
void A<T>::f() {}

template struct A<int>;  // 显式实例化 A<int>

// 不允许为 A<int> 定义特化
// template <>
// struct A<int> {};  // 错误

}  // namespace jc

int main() {}
```

### 5. 显式实例化与友元函数

通过显式实例化，可以为已有的类添加友元函数。

#### 示例：显式实例化与友元函数

```cpp
#include <cassert>
#include <iostream>
#include <string>

namespace jc {

template <auto>
struct A;

template <typename T, typename Class, T Class::*Member>
struct A<Member> {
  friend T& get(Class& c) { return c.*Member; }
};

}  // namespace jc

class Data {
 public:
  std::string value() const { return value_; }

 private:
  std::string value_ = "downdemo";
};

template struct jc::A<&Data::value_>;
std::string& jc::get(Data&);

int main() {
  Data data;
  assert(data.value() == "downdemo");
  jc::get(data) = "june";
  assert(data.value() == "june");
}
```

通过显式实例化，`get` 成为 `Data` 类的友元函数，从而能够访问 `value_` 成员。