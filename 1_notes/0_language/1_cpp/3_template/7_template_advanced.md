### 7. **C++11/14/17/20 中的模板新特性**

C++11、C++14、C++17 和 C++20 引入了许多新的模板特性，使得模板编程更加灵活和强大。以下是这些新特性的逐条解释：

### 7.1 C++11 中的模板新特性

#### 7.1.1 变参模板（Variadic Templates）

变参模板允许模板接受任意数量的模板参数。这使得编写泛型代码更加灵活，特别是在处理不定数量的参数时。

```cpp
#include <iostream>

// 递归终止条件
void print() {
    std::cout << "End of recursion" << std::endl;
}

// 变参模板函数
template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << std::endl;
    print(args...); // 递归调用
}

int main() {
    print(1, 2.5, "Hello", 'c'); // 输出 1, 2.5, Hello, c
    return 0;
}
```

#### 7.1.2 类型别名模板（Alias Templates）

类型别名模板允许为模板定义别名，使得代码更加简洁和易读。类型别名模板使用 `using` 关键字定义。

```cpp
#include <iostream>
#include <vector>

// 定义类型别名模板
template <typename T>
using Vec = std::vector<T>;

int main() {
    Vec<int> v = {1, 2, 3, 4, 5}; // 使用类型别名模板
    for (int n : v) {
        std::cout << n << std::endl;
    }
    return 0;
}
```

### 7.2 C++14 中的模板新特性

#### 7.2.1 变量模板（Variable Templates）

变量模板允许为模板定义变量，使得编写泛型常量更加方便。变量模板使用 `template` 关键字定义。

```cpp
#include <iostream>

// 定义变量模板
template <typename T>
constexpr T pi = T(3.1415926535897932385);

int main() {
    std::cout << pi<double> << std::endl; // 输出 3.14159...
    std::cout << pi<float> << std::endl;  // 输出 3.14159...
    return 0;
}
```

### 7.3 C++17 中的模板新特性

#### 7.3.1 折叠表达式（Fold Expressions）

折叠表达式是 C++17 引入的一种语法，用于简化变参模板中的递归操作。折叠表达式可以对参数包进行折叠，生成一个单一的表达式。

```cpp
#include <iostream>

// 使用折叠表达式计算参数包的和
template <typename... Args>
auto sum(Args... args) {
    return (args + ...); // 折叠表达式
}

int main() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl; // 输出 15
    return 0;
}
```

### 7.4 C++20 中的模板新特性

#### 7.4.1 概念（Concepts）

概念是 C++20 引入的一种新特性，用于对模板参数进行约束。概念可以定义模板参数必须满足的条件，从而提高模板代码的可读性和可维护性。

C++20 引入了 Concepts，为模板提供了类型约束的机制。Concepts 允许我们在模板参数上直接指定要求的特性，从而简化模板编程，提升代码的可读性和可维护性。

概念（Concept）是 C++20 引入的一个重要特性，旨在简化模板编程中的类型约束，使得模板参数的需求更加直观和易懂。它通过简洁的语法替代了传统的 SFINAE 技巧，使得模板代码更加易读，同时也改进了编译时错误提示，提升了开发体验。

尽管概念并不能解决 C++ 类型系统本身的复杂性问题，但它极大地改善了模板编程的可用性和开发效率。在复杂类型的模板约束中，概念提供了比 SFINAE 更清晰的错误信息，使得开发者能够更快速地发现问题并加以解决。

```cpp
#include <iostream>
#include <concepts>

// 定义一个概念，要求类型 T 必须是可加的
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// 使用概念约束模板参数
template <Addable T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << std::endl; // 输出 3
    // std::cout << add("Hello", "World") << std::endl; // 编译错误，字符串不满足 Addable 概念
    return 0;
}
```

##### 7.4.1.1 概念的应用：直接描述类型需求

概念不仅能用于函数模板的约束，还能直接用于类模板和其他类型的模板。通过概念，我们可以明确告知编译器，某个类型参数必须满足特定的要求。

例如，假设我们希望约束一个类型 `T` 必须支持自增操作（即 `++T`），可以定义一个概念 `Incrementable`：

```cpp
template <typename T>
concept Incrementable = requires(T t) {
    ++t;  // 要求T支持自增操作
};

template <Incrementable T>
void inc_counter(T& counter) {
    ++counter;  // 使用自增操作
}
```

这段代码明确要求 `T` 类型必须支持 `++` 操作。如果我们尝试将一个不支持自增的类型传递给 `inc_counter`，编译器会报错。

##### 7.4.1.2 语法与约束的组合

尽管概念使得模板参数约束变得更加清晰，但我们仍然需要遵循一些规则。例如，概念的约束不能直接写为如下形式：

```cpp
template <typename T> requires (T t) { ++t; }
void inc_counter(T& cnt);
```

这是不合法的，原因在于 `requires` 关键字在不同的上下文中有不同的含义：

- 在函数模板或类模板声明中，`requires` 后面必须跟着一个**概念表达式**，即类型约束的具体内容；
- 在定义概念时，`requires` 是一个保留字，用于定义一个“要求”的表达式。

因此，为了表达一个模板参数必须满足某种行为（例如 `++` 操作），我们需要使用更复杂的写法，例如：

```cpp
template <typename T> requires (requires(T t) { ++t; })
void inc_counter(T& cnt);
```

在这段代码中，`requires (requires(T t) { ++t; })` 实际上定义了一个匿名的概念，表示类型 `T` 必须支持 `++` 操作。

##### 7.4.1.3 概念带来的错误信息改进

概念不仅简化了模板的写法，也改善了模板编译时的错误提示。在没有概念的情况下，SFINAE 可能会导致模糊且难以理解的错误提示：

```cpp
// 使用 SFINAE 的错误提示
<source>:23:5: error: no matching function for call to 'Inc'
    Inc(y);
    ^~~
<source>:5:6: note: candidate template ignored: substitution failure [with T = X]: cannot increment value of type 'X'
void Inc(T& v, std::decay_t<decltype(++v)>* = nullptr)
     ^                               ~~
```

而使用概念后，错误提示更加清晰，直接指明了模板参数未能满足约束条件：

```cpp
// 使用 Concept 的错误提示
<source>:25:5: error: no matching function for call to 'Inc_Concept'
    Inc_Concept(y);
    ^~~~~~~~~~~
<source>:13:6: note: candidate template ignored: constraints not satisfied [with T = X]
void Inc_Concept(T& v)
     ^
<source>:12:11: note: because 'X' does not satisfy 'Incrementable'
template <Incrementable T>
          ^
<source>:10:41: note: because '++t' would be invalid: cannot increment value of type 'X'
concept Incrementable = requires(T t) { ++t; };
```

通过概念带来的错误信息，编译器明确指出了 `X` 类型不满足 `Incrementable` 概念，无法进行自增操作。这种错误提示更具可读性，帮助开发者更快地定位问题。

#### 7.4.2 约束（Constraints）

约束是 C++20 引入的一种新特性，用于对模板参数进行更细粒度的控制。约束可以与概念结合使用，定义模板参数必须满足的条件。

```cpp
#include <iostream>
#include <concepts>

// 定义一个概念，要求类型 T 必须是整数类型
template <typename T>
concept Integral = std::is_integral_v<T>;

// 使用约束和概念约束模板参数
template <Integral T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    std::cout << multiply(3, 4) << std::endl; // 输出 12
    // std::cout << multiply(3.5, 4.5) << std::endl; // 编译错误，double 类型不满足 Integral 概念
    return 0;
}
```


示例：通过 Concepts 限制模板参数为整数类型：

```cpp
template<std::integral T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int result = add(1, 2);   // 编译通过
    // double result2 = add(1.1, 2.2); // 编译错误，因为 double 不是整数类型
}
```

```cpp
namespace SFINAE_METHODS{
    template <typename ArgT>
    void foo(ArgT&& a, typename std::enable_if<std::is_same<std::decay_t<ArgT>, float>::value>::type* = nullptr);
}

namespace CONCEPT_METHODS{
    template <typename ArgT>
    requires std::same_as<std::remove_cvref_t<ArgT>, float>
    void foo(ArgT&& a);
}
```

