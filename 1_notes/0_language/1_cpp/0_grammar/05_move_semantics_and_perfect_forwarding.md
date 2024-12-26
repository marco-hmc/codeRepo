## 移动语义（Move Semantics）

### 1. **C++11 引入的值类别**

在 C++11 中，**值类别**（value category）是一个重要的概念，它区分了不同类型的值，包括：

- **左值（lvalue）**：表示持久存储的对象，可以取地址。
- **纯右值（prvalue）**：通常是临时对象，如字面值和返回值。
- **亡值（xvalue）**：表示某些资源即将被销毁的对象，通常是通过移动操作产生的。
  
**左值和亡值**组成了泛左值（glvalue），**纯右值和亡值**组成了右值（rvalue）。

为了使编译器能够识别接受右值参数的构造函数，我们引入了**右值引用**（rvalue reference），其通过 `&&` 语法表示，从而区分**移动构造函数**与**拷贝构造函数**。

#### 示例：右值引用与移动语义

```cpp
#include <cassert>
#include <string>
#include <utility>
#include <vector>

namespace jc {

struct A {
  A() : data(new std::string) {}  // 默认构造函数
  A(const A& rhs) : data(new std::string{*rhs.data}) {}  // 拷贝构造函数
  A(A&& rhs) noexcept : data(rhs.data) {  // 移动构造函数
    rhs.data = nullptr;  // 将源对象的指针置空
  }
  ~A() { delete data; }  // 析构函数

  std::string* data = nullptr;  // 管理的数据
};

}  // namespace jc

int main() {
  std::vector<jc::A> v;

  // 调用默认构造函数、移动构造函数、析构函数
  v.emplace_back(jc::A{});  

  jc::A a;
  // 调用拷贝构造函数
  v.emplace_back(a);  
  assert(a.data);  // a 的数据未被修改

  // 调用移动构造函数
  v.emplace_back(std::move(a));  
  assert(!a.data);  // a 的数据已被移动
}
```

在这个例子中：
- `v.emplace_back(jc::A{})` 调用了 **默认构造函数**、**移动构造函数** 和 **析构函数**。
- `v.emplace_back(a)` 调用了 **拷贝构造函数**。
- `v.emplace_back(std::move(a))` 调用了 **移动构造函数**，同时原对象 `a` 的数据被置为空。

### 2. **右值引用与 `std::move`**

右值引用（`&&`）只能绑定到右值。右值包括字面值（pure rvalue）和临时变量（xvalue）。如果将左值传递给右值引用参数，编译器将产生错误。为了在这种情况下进行类型转换，我们使用 `std::move`。

`std::move` 是一个标准库函数，实际上并不执行移动操作，而是将其参数转换为右值引用，通常用于启用移动语义。

#### 示例：`std::move` 和强制类型转换

```cpp
#include <cassert>
#include <string>
#include <type_traits>
#include <utility>

namespace jc {

// 定义自定义的 move 函数，效果与 std::move 相同
template <typename T>
constexpr std::remove_reference_t<T>&& move(T&& x) noexcept {
  return static_cast<std::remove_reference_t<T>&&>(x);
}

constexpr int f(const std::string&) { return 1; }  // 接受左值引用
constexpr int f(std::string&&) { return 2; }  // 接受右值引用

}  // namespace jc

int main() {
  std::string s;

  // 调用左值版本的 f
  static_assert(jc::f(s) == 1);  
  // 调用右值版本的 f
  assert(jc::f(std::string{}) == 2);  

  // 强制类型转换为右值引用，调用右值版本
  static_assert(jc::f(static_cast<std::string&&>(s)) == 2);  
  // 使用 std::move 进行转换
  static_assert(jc::f(jc::move(s)) == 2);  
  static_assert(jc::f(std::move(s)) == 2);  // 与 std::move 等效
}
```

在这个例子中：
- `jc::f(s)` 调用了左值版本的 `f`。
- `jc::f(std::string{})` 调用了右值版本的 `f`，因为 `std::string{}` 是一个临时对象。
- `jc::f(static_cast<std::string&&>(s))` 强制将 `s` 转换为右值引用，从而调用右值版本的 `f`。
- `jc::f(jc::move(s))` 和 `jc::f(std::move(s))` 调用了右值版本的 `f`，因为 `std::move(s)` 实际上是将 `s` 转换为右值引用。

### 3. **总结**

- **右值引用（`&&`）** 是 C++11 引入的一个重要特性，它允许编译器识别右值并进行高效的资源转移，通常与 **移动构造函数** 和 **移动赋值运算符** 配合使用。
- `std::move` 不是一个执行移动操作的函数，它只是将一个对象转化为右值引用，以便允许其资源的移动。
- **移动语义** 可以极大地提升性能，尤其是在涉及大量临时对象和容器的场景中，通过避免不必要的深拷贝。


## 完美转发（Perfect Forwarding）

在 C++ 中，当我们需要将函数参数传递给另一个函数时，**完美转发**是一种确保原始值类别（lvalue 或 rvalue）不丢失的技术。为此，C++ 提供了**万能引用**（也称为转发引用）和 `std::forward` 函数，允许我们根据传入参数的类型（左值或右值）选择合适的转发方式。

### 1. **右值引用的问题**

右值引用（`&&`）能够接受右值，但如果将右值引用传递给另一个函数，值类别会丢失（即被转化为左值）。这会导致一些问题，尤其是当我们希望将参数转发到其他函数时。

#### 示例：值类别丢失

```cpp
#include <cassert>
#include <string>
#include <utility>

namespace jc {

constexpr int f(const std::string&) { return 1; }
constexpr int f(std::string&&) { return 2; }

constexpr int g(std::string&& s) { return f(s); }

void test() {
  std::string s;
  assert(f(std::string{}) == 2);  // 临时对象，调用右值版本
  assert(g(std::string{}) == 1);  // 传递右值引用，调用左值版本
  static_assert(f(std::move(s)) == 2);  // std::move 后调用右值版本
  static_assert(g(std::move(s)) == 1);  // std::move 后调用左值版本
}

}  // namespace jc

int main() { jc::test(); }
```

在上面的例子中，`g(std::string&& s)` 接受右值引用参数，但当将右值传递给 `f(s)` 时，`s` 被当作左值处理。为了保持值类别不丢失，需要一种方法来确保正确地转发参数。

### 2. **手动重载解决方案**

为了在转发时保持原始值类别，通常需要手动为不同的值类别重载多个函数。

#### 示例：手动重载以保持值类别

```cpp
#include <cassert>
#include <string>
#include <utility>

namespace jc {

constexpr int f(std::string&) { return 1; }
constexpr int f(const std::string&) { return 2; }
constexpr int f(std::string&&) { return 3; }

constexpr int g(std::string& s) { return f(s); }
constexpr int g(const std::string& s) { return f(s); }
constexpr int g(std::string&& s) { return f(std::move(s)); }

void test() {
  std::string s;
  const std::string& s2 = s;
  static_assert(g(s) == 1);             // 调用左值版本
  assert(g(s2) == 2);                   // 调用 const 左值版本
  static_assert(g(std::move(s)) == 3);  // 调用右值版本
  assert(g(std::string{}) == 3);        // 调用右值版本
}

}  // namespace jc

int main() { jc::test(); }
```

在这个例子中，我们为每种值类别（左值、右值、const 左值）分别编写了不同的重载版本，确保在转发时保持正确的值类别。

### 3. **万能引用与完美转发**

**万能引用**（或称转发引用）是一个能够根据传入的实参类型推导出正确引用类型的引用，它是通过 `T&&` 在模板参数中声明的。当我们传递左值时，它会被推导为左值引用 `T&`，当传递右值时，它会被推导为右值引用 `T&&`。

为了完美转发参数，我们需要结合 `std::forward`（或自定义的 `forward`）来保持值类别。`std::forward` 根据类型推导，确保左值和右值分别被正确地转发。

#### 示例：万能引用与 `std::forward`

```cpp
#include <cassert>
#include <string>
#include <type_traits>

namespace jc {

template <typename T>
constexpr T&& forward(std::remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

constexpr int f(std::string&) { return 1; }
constexpr int f(const std::string&) { return 2; }
constexpr int f(std::string&&) { return 3; }

template <typename T>
constexpr int g(T&& s) {
  return f(jc::forward<T>(s));  // 使用 std::forward 实现完美转发
}

void test() {
  std::string s;
  const std::string& s2 = s;
  static_assert(g(s) == 1);             // T = std::string&, 调用左值版本
  assert(g(s2) == 2);                   // T = const std::string&, 调用 const 左值版本
  static_assert(g(std::move(s)) == 3);  // T = std::string, 调用右值版本
  assert(g(std::string{}) == 3);        // T = std::string, 调用右值版本
  assert(g("downdemo") == 3);           // T = const char(&)[9], 调用右值版本
}

}  // namespace jc

int main() { jc::test(); }
```

在这个例子中，`g` 函数接受一个万能引用参数，并通过 `std::forward<T>(s)` 完美地转发该参数到 `f` 函数。`std::forward` 根据传入的实参类型来决定是否以左值或右值形式传递。

### 4. **结合变参模板实现完美转发**

结合变参模板，完美转发可以支持转发任意数量的实参。通过递归地调用 `std::forward`，我们能够转发任意数量的参数。

#### 示例：变参模板中的完美转发

```cpp
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace jc {

template <typename F, typename... Args>
constexpr void constexpr_for(F&& f, Args&&... args) {
  (std::invoke(std::forward<F>(f), std::forward<Args>(args)), ...);
}

template <typename... Args>
void print(Args&&... args) {
  constexpr_for([](const auto& x) { std::cout << x << std::endl; },
                std::forward<Args>(args)...);
}

}  // namespace jc

int main() {
  jc::print(3.14, 42, std::string{"hello"}, "world");
}
```

在这个例子中，`constexpr_for` 递归地调用了 `std::invoke` 来转发参数，从而实现了将任意数量的实参转发到打印函数 `print` 中。`std::forward<Args>(args)...` 保证了每个参数都保持其原始的值类别。

### 5. **Lambda 中的完美转发**

在 Lambda 函数中，使用完美转发时需要借助 `decltype` 来推导参数的类型，并使用 `std::forward` 转发。

#### 示例：Lambda 中的完美转发

```cpp
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace jc {

constexpr auto constexpr_for = [](auto&& f, auto&&... args) {
  (std::invoke(std::forward<decltype(f)>(f),
               std::forward<decltype(args)>(args)),
   ...);
};

auto print = [](auto&&... args) {
  constexpr_for([](const auto& x) { std::cout << x << std::endl; },
                std::forward<decltype(args)>(args)...);
};

}  // namespace jc

int main() {
  jc::print(3.14, 42, std::string{"hello"}, "world");
}
```

### 6. **C++20 Lambda 指定模板参数**

C++20 引入了 Lambda 表达式的模板参数，使得在 Lambda 函数中使用完美转发变得更加简洁。

#### 示例：C++20 Lambda 指定模板参数

```cpp
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace jc {

constexpr auto constexpr_for =
    []<typename F, typename... Args>(F&& f, Args&&... args) {
  (std::invoke(std::forward<F>(f), std::forward<Args>(args)), ...);
};

auto print = []<typename... Args>(Args&& ... args) {
  constexpr_for([](const auto& x) { std::cout << x << std::endl; },
                std::forward<Args>(args)...);
};

}  // namespace jc

int main() {
  jc::print(3.14, 42, std::string{"hello"}, "world");
}
```

### 7. **C++20 Lambda 捕获参数包**

C++20 还允许 Lambda 捕获参数包，使得在 Lambda 中更加灵活地操作转发的实参。

#### 示例：C++20 Lambda 捕获参数包

```cpp
#include <iostream>
#include <string>
#include <

type_traits>
#include <utility>

namespace jc {

template <typename... Args>
void print(Args&&... args) {
  [... args = std::forward<Args>(args)]<typename F>(F&& f) {
    (std::invoke(std::forward<F>(f), args), ...);
  }([](const auto& x) { std::cout << x << std::endl; });
}

}  // namespace jc

int main() {
  jc::print(3.14, 42, std::string{"hello"}, "world");
}
```

### 总结

- **完美转发** 是保持原始值类别（左值或右值）的技术，通常结合 **万能引用** 和 `std::forward` 来实现。
- **万能引用** 可以匹配几乎所有类型（左值或右值），使得我们能够根据实参的类型正确地转发。
- 通过 **变参模板**，我们能够转发任意数量的参数，实现更加灵活和高效的函数调用。
- 在 **C++20** 中，Lambda 表达式提供了更多便利，如指定模板参数和捕获参数包，使得完美转发更加简洁和易用。

## 构造函数模板（Constructor Templates）

C++ 中，**构造函数模板**允许我们为类提供一个泛型构造函数。它通过模板机制使得构造函数能够处理不同类型的参数。然而，构造函数模板与普通的构造函数略有不同，需要注意一些细节。

### 1. **构造函数模板的特点**

构造函数模板并不是一个常规的构造函数，它是由函数模板实例化而来的。因此，构造函数模板不会像普通构造函数那样与拷贝构造函数或移动构造函数发生重载。对于一个 `non-const` 对象的构造函数调用，**万能引用**（`T&&`）通常会优先匹配。

#### 示例：构造函数模板

```cpp
#include <string>
#include <utility>

namespace jc {

struct A {
  // 构造函数模板，接受任何类型的参数
  template <typename T>
  explicit A(T&& t) : s(std::forward<T>(t)) {}

  // 拷贝构造函数
  A(const A& rhs) : s(rhs.s) {}

  // 移动构造函数
  A(A&& rhs) noexcept : s(std::move(rhs.s)) {}

  std::string s;
};

}  // namespace jc

int main() {
  const jc::A a{"downdemo"};
  jc::A b{a};  // OK，匹配拷贝构造函数
  // jc::A c{b};  // 错误，匹配构造函数模板
}
```

在这个示例中：

- `A(T&& t)` 是一个构造函数模板，它可以接受任何类型的参数并将其转发给成员变量 `s`。
- `A(const A& rhs)` 和 `A(A&& rhs)` 是常规的拷贝构造函数和移动构造函数。
- 对于 `jc::A b{a};`，会匹配到拷贝构造函数。
- 对于 `jc::A c{b};`，编译器会尝试匹配构造函数模板，但由于它要求参数可以转换为 `std::string`，会导致匹配失败。

### 2. **使用 `std::enable_if` 约束模板参数**

为了避免构造函数模板与普通的拷贝或移动构造函数冲突，我们可以使用 `std::enable_if` 来为模板添加约束，只在特定条件下启用模板构造函数。例如，可以要求模板参数能够转换为 `std::string`，这样只允许传入可以转换为 `std::string` 的类型。

#### 示例：使用 `std::enable_if` 约束模板

```cpp
#include <string>
#include <type_traits>
#include <utility>

namespace jc {

struct A {
  // 构造函数模板，要求 T 类型能转换为 std::string
  template <typename T,  // 要求 T 能转为 std::string
            typename = std::enable_if_t<std::is_convertible_v<T, std::string>>>
  explicit A(T&& t) : s(std::forward<T>(t)) {}

  // 拷贝构造函数
  A(const A& rhs) : s(rhs.s) {}

  // 移动构造函数
  A(A&& rhs) noexcept : s(std::move(rhs.s)) {}

  std::string s;
};

}  // namespace jc

int main() {
  const jc::A a{"downdemo"};
  jc::A b{a};  // OK，匹配拷贝构造函数
  jc::A c{b};  // OK，匹配拷贝构造函数
}
```

在此示例中，我们通过 `std::enable_if` 约束模板参数 `T`，要求 `T` 能够转换为 `std::string`。因此，模板构造函数只会在 `T` 可以转换为 `std::string` 时有效。

- `jc::A a{"downdemo"}` 调用 `A(const A&)` 构造函数。
- `jc::A c{b}` 调用拷贝构造函数，`b` 已经是 `A` 类型，因此匹配 `A(const A&)`。

### 3. **使用 C++20 Concepts 约束模板参数**

从 C++20 开始，我们可以使用 **概念**（Concepts）来更直观和简洁地约束模板参数。概念提供了比 `std::enable_if` 更清晰的语法，使得我们能够直接为模板函数指定条件。

#### 示例：使用 C++20 Concepts 约束模板

```cpp
#include <concepts>
#include <string>
#include <utility>

namespace jc {

struct A {
  // 使用 C++20 Concepts 来约束模板参数 T
  template <typename T>
    requires std::convertible_to<T, std::string>
  explicit A(T&& t) : s(std::forward<T>(t)) {}

  // 拷贝构造函数
  A(const A& rhs) : s(rhs.s) {}

  // 移动构造函数
  A(A&& rhs) noexcept : s(std::move(rhs.s)) {}

  std::string s;
};

}  // namespace jc

int main() {
  const jc::A a{"downdemo"};
  jc::A b{a};  // OK，匹配拷贝构造函数
  jc::A c{b};  // OK，匹配拷贝构造函数
}
```

在这个例子中，`std::convertible_to<T, std::string>` 是一个概念，要求 `T` 类型能够转换为 `std::string`。使用 `requires` 关键字将这个约束应用于构造函数模板。

- `jc::A a{"downdemo"}` 会调用 `A(const A&)` 构造函数。
- `jc::A c{b}` 会调用 `A(const A&)` 构造函数，因为 `b` 是 `A` 类型的对象。

### 总结

1. **构造函数模板** 是通过模板机制实现的，可以处理不同类型的参数，但它与拷贝构造函数或移动构造函数是不同的，它不会覆盖这些普通构造函数。
2. 为了避免构造函数模板与普通的拷贝或移动构造函数发生冲突，可以使用 `std::enable_if` 来对模板参数进行约束。
3. C++20 引入了 **概念**（Concepts），使得我们可以更直观地约束模板参数，避免了使用 `std::enable_if` 的复杂性。
