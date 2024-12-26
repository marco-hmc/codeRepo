### 2. **ADL 忽略 `using` 声明**


## line---------------------------------------------


### 类模板中的注入类名

类模板的注入类名不仅可以作为类型名使用，还可以作为模板名使用。模板类的名字在模板定义中作为当前实例化的一部分，依赖于模板参数的类型。

```cpp
namespace jc {

template <template <typename> class>
struct A {};

template <typename T>
struct B {
  B* a;            // B 被当作类型名，等价于 B<T>
  B<void>* b;      // B 被当作模板名
  using c = A<B>;  // B 被当作模板名
  A<jc::B> d;      // jc::B 是模板名，不是注入类名
};

}  // namespace jc

int main() {}
```

在这个例子中：

- `B* a;` 表示 `B<T>` 类型。
- `B<void>* b;` 表示 `B<void>` 类型，`B` 在这里作为模板名。
- `A<jc::B> d;` 是一个模板类 `A`，传入 `jc::B` 作为模板参数。这里，`jc::B` 作为模板名，并不是注入类名。

## 非模板中的上下文相关性

C++ 是一种上下文相关语言，这意味着编译器在解析一个声明时会依赖于上下文信息。在上下文相关的语言中，解析一个声明时，编译器不仅要检查符号表，还需要依据扫描器和解析器的配合，来做出正确的决策。

### 符号表和扫描器

当编译器解析某个声明时，它会将该声明的信息添加到符号表中。如果扫描器遇到某个标识符，它会在符号表中查找对应的符号。如果找到的符号是一个类型，扫描器会对该标识符做出相应的注解。例如，在解析 `x*` 时，编译器会首先查找 `x` 是否是类型，如果是，则将其视为类型标识符，处理为指针声明。

如果 `x` 不是类型，编译器会认为这是一个乘法表达式，并处理为 `x *`。

### 示例：表达式解析

对于表达式 `A<1>(0)`，如果 `A` 是类模板，编译器会将 `0` 转换为 `A<1>` 类型。如果 `A` 不是类模板，编译器会将 `<` 看作小于号并执行比较。

```cpp
namespace jc {

template <bool B>
struct A {
  static const bool value = B;
};

static_assert(A<(1 > 0)>::value);  // 必须使用小括号
}  // namespace jc

int main() {}
```

在这个例子中：

- `A<(1 > 0)>::value` 会通过 `A<1>` 来访问静态成员 `value`。
- 必须使用小括号 `()` 来确保表达式 `1 > 0` 被正确解析为模板参数。

## 依赖名称（Dependent Name）

**依赖名称** 是指在模板定义中，依赖于模板参数的名称。C++ 编译器对依赖名称（dependent name）和非依赖名称（non-dependent name）有不同的查找规则。`Dependent name` 包括当前实例化和未知特化，而 **未知特化** 是指依赖于模板参数但不属于当前实例化的名称。

### 示例：当前实例化与未知特化

```cpp
namespace jc {

template <typename T>
struct A {
  using type = T;

  A* a;        // A 是当前实例化
  A<type>* b;  // A<type> 是当前实例化
  A<T*>* c;    // A<T*> 是未知特化

  struct B {
    A* a;        // A 是当前实例化
    A<type>* b;  // A<type> 是当前实例化
    B* c;        // B 是当前实例化
  };

  struct C {
    A* a;        // A 是当前实例化
    A<type>* b;  // A<type> 是当前实例化
    B* c;        // B 是未知特化
    C* d;        // C 是当前实例化
  };
};

template <>
struct A<int>::B {
  int i;
};

}  // namespace jc

int main() {
  jc::A<double>::C{}.c->a;  // 使用当前实例化的 A<double>::C
  jc::A<int>::C{}.c->i;     // 使用特化的 A<int>::B
}
```

在这个例子中：

- `A* a` 和 `A<type>* b` 是当前实例化的依赖名称。
- `A<T*>* c` 是未知特化，因为 `T` 可能会是 `int*` 等不同的类型。

### `typename` 消歧义符

当访问类模板的依赖名称时，必须使用 `typename` 消歧义符来明确告诉编译器该名称是一个类型。如果不加 `typename`，编译器可能会误将其当作非类型标识符。

```cpp
namespace jc {

struct Base {
  int i;
};

template <typename T>
struct A {
  using type = T;
};

template <typename T>
struct Derived : A<T>::type {  // 基类列表中不能加 typename 消歧义符
  Derived()
      : A<T>::type  // 初始化列表中不能加 typename 消歧义符
        (typename A<T>::type{0})  // 必须加 typename 消歧义符
  {}

  A<T> f() {
    typename A<T>::type* p;  // 必须加 typename 消歧义符
    return {};
  }

  A<int>::type* s;  // non-dependent name，typename 消歧义符可有可无
};

}  // namespace jc

int main() { jc::Derived<jc::Base>{}.f(); }
```

在这个例子中：

- `A<T>::type` 必须加上 `typename` 消歧义符，来指明 `type` 是一个类型。
- `A<int>::type` 是一个非依赖名称，`typename` 消歧义符可以选择性地加上。

### `template` 消歧义符

当访问模板的依赖名称时，必须使用 `template` 消歧义符来指明该名称是一个模板，否则 `<` 会被误解析为小于号。

```cpp
namespace jc {

template <typename T>
struct A {
  template <typename U>
  struct Impl {
    template <typename Y>
    static void f() {}
  };

  template <typename U>
  static void f() {}
};

}  // namespace jc

template <typename T>
void test() {
  T::template Impl<T>::template f<T>();  // 需要加上 template 消歧义符
  T::template f<T>();  // 需要加上 template 消歧义符
}

int main() { test<jc::A<int>>(); }
```

在这个例子中：

- 访问 `Impl<T>::template f<T>()` 和 `f<T>()` 时，必须加上 `template` 消歧义符，以明确告诉编译器这些名称是模板。

## Non-dependent Base（非依赖基类）

**Non-dependent base** 是不依赖于模板参数类型的基类。派生类中访问非依赖基类的成员时，编译器会首先查找非依赖基类，再查找模板参数列表。

### 示例：Non-dependent Base

```cpp
#include <type_traits>

namespace jc {

template <typename>
struct Base {
  using T = char;
};

template <typename T>
struct Derived1 : Base<void> {  // 非依赖基类
  using type = T;               // T 是 Base<void>::T
};

template <typename T>
struct Derived2 : Base<T> {  // 依赖基类
  using type = T;            // T 是模板参数
};

static_assert(std::is_same_v<Derived1<int>::

type, char>);
static_assert(std::is_same_v<Derived2<int>::type, int>);

}  // namespace jc

int main() {}
```

在这个例子中：

- `Derived1` 使用了非依赖基类 `Base<void>`，因此 `T` 被解析为 `Base<void>::T`。
- `Derived2` 使用了依赖基类 `Base<T>`，因此 `T` 被解析为模板参数 `T`。

## line -------------------------------------------------------------------

## Dependent Base（依赖基类）

在 C++ 中，当派生类继承一个模板基类时，这个基类会被称为 **dependent base**（依赖基类）。对派生类来说，基类的类型依赖于模板参数，因此编译器在查找基类成员时必须特别注意。

### 1. 对于非依赖名称的查找

对于 **non-dependent name**（非依赖名称），编译器不会在 **dependent base** 中查找。非依赖名称是指那些在模板参数之外独立的名称。为了确保基类成员能被正确查找，通常需要使用 `this->` 或者作用域运算符来使其变为依赖名称。

#### 示例：错误的查找

```cpp
namespace jc {

template <typename>
struct Base {
  static constexpr int value = 1;
};

template <typename T>
struct Derived : Base<T> {  // dependent base
  constexpr int get_value() const {
    return value;  // 错误：不会在 dependent base 中查找 non-dependent name
  }
};

}  // namespace jc

int main() {}
```

在这个例子中，`value` 是一个非依赖名称，它应该在基类 `Base<T>` 中查找，但因为它是一个非依赖名称，编译器不会在 `Base<T>` 中查找它，导致编译错误。

### 2. 使用 `this->` 或作用域运算符进行查找

为了确保可以在 **dependent base** 中查找非依赖名称，可以使用 `this->` 或作用域运算符来将该名称变为 **dependent name**。

#### 示例：使用 `this->` 来查找

```cpp
namespace jc {

template <typename>
struct Base {
  static constexpr int value = 1;
};

template <typename T>
struct Derived : Base<T> {  // dependent base
  constexpr int get_value() const {
    return this->value;  // dependent name，会在 dependent base 中查找
  }
};

template <>
struct Base<bool> {
  static constexpr int value = 2;
};

}  // namespace jc

int main() {
  static_assert(jc::Derived<int>{}.get_value() == 1);  // 输出 1
  static_assert(jc::Derived<bool>{}.get_value() == 2); // 输出 2
}
```

在这个示例中：

- `this->value` 将 `value` 转换为 **dependent name**，使得编译器能够在依赖基类 `Base<T>` 中查找 `value`。
- `jc::Derived<int>` 和 `jc::Derived<bool>` 根据不同的模板参数，调用了基类 `Base<int>` 和 `Base<bool>` 中的 `value`。

#### 示例：使用 `using` 声明

另一种方式是使用 `using` 声明，这样只需要一次声明就能让派生类中的成员引用基类的成员。

```cpp
namespace jc {

template <typename>
struct Base {
  static constexpr int value = 1;
};

template <typename T>
struct Derived : Base<T> {  // dependent base
  using Base<T>::value;  // 引入 value

  constexpr int get_value() const {
    return value;  // dependent name，会在 dependent base 中查找
  }
};

template <>
struct Base<bool> {
  static constexpr int value = 2;
};

}  // namespace jc

int main() {
  static_assert(jc::Derived<int>{}.get_value() == 1);  // 输出 1
  static_assert(jc::Derived<bool>{}.get_value() == 2); // 输出 2
}
```

在这个示例中：

- `using Base<T>::value;` 引入了 `Base<T>` 中的 `value` 成员，这使得 `get_value()` 可以直接使用它。
- 使用 `using` 声明可以避免重复写 `this->`，简化代码。

### 3. 使用作用域运算符时不会访问虚函数

当你使用作用域运算符访问基类的成员时，编译器不会进行虚函数的查找。作用域运算符只是直接访问基类的成员，因此虚函数不会被调用。

#### 示例：作用域运算符不访问虚函数

```cpp
#include <cassert>

namespace jc {

template <typename>
struct Base {
  virtual int f() const { return 1; }
};

template <typename T>
struct Derived : Base<T> {  // dependent base
  virtual int f() const { return 2; }
  int get_value() const { return Base<T>::f(); }  // 使用作用域运算符访问
};

template <>
struct Base<bool> {
  virtual int f() const { return 3; }
};

}  // namespace jc

int main() {
  assert(jc::Derived<int>{}.get_value() == 1);   // 输出 1
  assert(jc::Derived<bool>{}.get_value() == 3);  // 输出 3
}
```

在这个示例中，`Base<T>::f()` 通过作用域运算符访问基类的 `f()` 函数，但不会进行虚函数机制的查找，因此对于 `Derived<int>`，它调用了 `Base<int>` 中的 `f()`，而对于 `Derived<bool>`，它调用了 `Base<bool>` 中的 `f()`，没有调用 `Derived` 中重写的虚函数。

### 4. 使用 `this->` 或 `using` 声明访问虚函数

如果你需要访问虚函数，并希望遵循多态的规则（即基于对象的动态类型调用正确的函数），你必须使用 `this->` 或 `using` 声明，而不是作用域运算符。

#### 示例：使用 `this->` 或 `using` 声明访问虚函数

```cpp
#include <cassert>

namespace jc {

template <typename>
struct Base {
  virtual int f() const { return 1; }
};

template <typename T>
struct Derived1 : Base<T> {  // dependent base
  virtual int f() const { return 2; }
  int get_value() const { return this->f(); }  // 使用 this-> 调用虚函数
};

template <typename T>
struct Derived2 : Base<T> {  // dependent base
  using Base<T>::f;  // 引入 Base<T>::f
  virtual int f() const { return 2; }
  int get_value() const { return f(); }  // 使用 f() 调用虚函数
};

template <>
struct Base<bool> {
  virtual int f() const { return 3; }
};

}  // namespace jc

int main() {
  assert(jc::Derived1<int>{}.get_value() == 2);  // 输出 2
  assert(jc::Derived1<bool>{}.get_value() == 2); // 输出 2
  assert(jc::Derived2<int>{}.get_value() == 2);  // 输出 2
  assert(jc::Derived2<bool>{}.get_value() == 2); // 输出 2
}
```

在这个示例中：

- `Derived1` 和 `Derived2` 都使用 `this->f()` 或 `using Base<T>::f` 来确保访问虚函数时遵循动态多态。
- 使用 `this->` 或 `using` 声明，使得编译器能够正确解析虚函数调用，并支持多态性。

### 总结

- **Non-dependent name**（非依赖名称）不会在 **dependent base**（依赖基类）中查找，若要使其作为依赖名称查找，必须使用 `this->` 或作用域运算符。
- 使用作用域运算符时，虚函数不会被访问。若要确保访问虚函数，需要使用 `this->` 或 `using` 声明。
- `this->` 和 `using` 声明使得派生类能够正确访问基类的成员，并支持多态性。