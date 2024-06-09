## c++ 中的省略号

### 1. c++ 中的省略号怎么用？
在C++中，省略号（...）有两种主要的用途：

1. 可变参数模板（Variadic Templates）：在模板编程中，省略号用于表示一个参数包（Parameter Pack），可以包含零个或多个参数。例如：

```cpp
template <typename... Args>
void print(Args... args) {
    // ...
}
```

在这个例子中，`Args... args`表示一个参数包，可以接受任意数量和类型的参数。

2. 可变参数列表（Varargs）：在C风格的函数中，省略号用于表示一个可变数量的参数。例如：

```cpp
#include <cstdarg>

void print(const char* format, ...) {
    va_list args;
    va_start(args, format);
    // ...
    va_end(args);
}
```

在这个例子中，`...`表示函数`print`可以接受任意数量的参数，这些参数的类型和数量在编译时期是未知的。`va_start`、`va_arg`和`va_end`是处理这些参数的宏。

注意，使用可变参数列表需要谨慎，因为它们不提供类型安全。在可能的情况下，应优先使用可变参数模板。

### 2. 汇编语言不是不理解变长参数吗？那这个...语法特性是怎么实现的？
C++的可变参数模板（Variadic Templates）和C语言的可变参数列表（Varargs）都是通过编译器在编译时期进行处理的，而不是在运行时期。因此，它们并不依赖于汇编语言的支持。

#### 2.1 具体是怎么处理...的
```c++
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}
```

编译器处理C++的可变参数模板（Variadic Templates）时，会将`...`视为一个参数包（Parameter Pack）。参数包可以包含零个或多个参数。

在你的代码中，`Args... args`就是一个参数包。`Args...`表示参数的类型可以有多个，`args...`表示参数的值可以有多个。

当编译器遇到`...`时，它会对参数包进行展开（Unpack）。在你的代码中，`(args + ...)`就是一个折叠表达式（Fold Expression）。编译器会将其展开为`arg1 + arg2 + arg3 + ...`。

例如，如果你调用`sum(1, 2, 3)`，那么编译器会将`(args + ...)`展开为`1 + 2 + 3`。

这就是编译器如何处理`...`的。它将`...`视为一个参数包，并在需要的时候对其进行展开。


### 3. 具体代码

#### 3.0 implementation0
```c++
void printNumbers(int count, ...)
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        printf("%d ", num);
    }

    va_end(args);
}
```
下面三个都是和va_list搭配使用的宏
* `va_start`:
    * 该宏用于初始化`va_list`类型的变量,以便访问不定长参数列表参数.
    * 它接受两个参数,第一个参数是一个`va_list`类型的变量,第二个是最后一个已知的固定参数.这个宏必须在访问不定长参数之前调用.
* `va_arg`: 该宏用于从不定长参数列表中获取下一个参数的值.
    * 它接受两个参数,第一个参数是一个`va_list`类型的变量,第二个参数是要获取的参数的类型.这个宏可以多次调用,每次调用都会返回下一个参数的
 * `va_end`: 该宏用于清理`va_list`类型的变量.
    * 它接受一个参数,即要清理的`va_list`类型的变量.这个宏必须在长参数处理完毕后调用.

这是传统C语言处理不定长的方式，`printf()`也是通过这种方式实现的。

#### 3.1 implementation1
```c++
// --1. fold expression c17-standard
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

// --2. variadic template c11-standard
int sum2() {
    return 0;
}
template<typename T, typename... Args>
T sum2(T first, Args... args) {
    return first + sum(args...);
}
```
##### 3.1.1 折叠表达式
(args + ...)是C++17标准引入的一种新特性，叫做折叠表达式（Fold Expressions）。

折叠表达式可以将一个参数包（Parameter Pack）中的所有元素用某种运算符连接起来。在你的代码中，(args + ...)就是一个折叠表达式，它将参数包args中的所有元素用加号（+）连接起来。

例如，如果你调用sum(1, 2, 3)，那么(args + ...)就会被展开为1 + 2 + 3。

折叠表达式可以使用所有的二元运算符，包括+、-、*、/、%、&&、||等等。此外，还可以使用一些特殊的运算符，如<<、>>、==、!=等等。

折叠表达式的工作原理是在编译时期将参数包展开，生成一个包含所有元素的表达式。这是在编译时期完成的，因此不会引入运行时开销。

##### 3.1.2 递归终止条件
这里的`int sum2()`函数是一个递归终止条件。在递归函数中，我们需要一个或多个基本情况（base case）来停止递归。

在这个例子中，`sum2(T first, Args... args)`函数是一个可变参数模板，它会递归地调用自己，每次调用时都去掉一个参数，直到没有参数为止。当没有参数时，就会调用`int sum2()`函数，返回0，作为递归的终止条件。

如果没有这个`int sum2()`函数，那么当参数列表为空时，编译器会找不到匹配的函数调用，导致编译错误。

#### 3.2 implementation2
```c++
template <typename First, typename... Args>
auto sum3(const First first, const Args... args) -> decltype(first) {
  const auto values = {first, args...};
  return std::accumulate(values.begin(), values.end(), First{0});
}
```
这段代码是一个使用C++可变参数模板（Variadic Templates）的函数模板，用于求和一系列数。

函数模板的参数有两部分：`First`和`Args...`。`First`是第一个参数的类型，`Args...`是剩余参数的类型。这样设计的目的是为了能够处理至少一个参数的情况。

函数的返回类型是`decltype(first)`，这表示返回类型与第一个参数`first`的类型相同。这是因为在加法运算中，结果的类型通常与操作数的类型相同。

在函数体中，首先将所有参数（包括`first`和`args...`）放入一个初始化列表`values`中，然后使用`std::accumulate`函数对`values`中的所有元素进行求和。`std::accumulate`函数的第三个参数是初始值，这里使用了`First{0}`，表示类型为`First`的零值。

总的来说，这段代码的目的是使用C++的可变参数模板和初始化列表，以及STL的`std::accumulate`函数，来实现对一系列数的求和。

简单来说和`sum2()`相比，这个也是c11标准支持，但是通过`std::initializer_list`和支持容器操作的算法如`std::accumulate`来取到最后一个元素，避免`sum2()`的终止递归条件判断。

##### 3.2.1 为什么用声明first?
那么你需要找到一种方式来确定函数的返回类型，以及std::accumulate的初始值的类型。这是因为在C++中，函数的返回类型和std::accumulate的初始值的类型都需要在编译时期确定。

如果你的函数只接受一个类型的参数，那么你可以直接使用这个类型作为返回类型和初始值的类型。例如：
```c++
template <typename... Args>
double sum3(const Args... args) {
  const auto values = {args...};
  return std::accumulate(values.begin(), values.end(), 0.0);
}
```
在这个例子中，函数的返回类型和初始值的类型都是double。

##### 3.2.2 不可以用decltype(args)吗
在C++中，`decltype`关键字用于查询表达式的类型。然而，`args`是一个参数包（Parameter Pack），它可以包含多个参数，每个参数的类型可能都不同。因此，`decltype(args)`并没有明确的意义，编译器无法确定它应该返回哪种类型。

而`args`是一个参数包，它可能包含多种类型的参数，因此不能使用`decltype(args)`。

如果你想要处理多种类型的参数，并且希望函数的返回类型能够根据所有参数的类型自动推导，那么你可能需要使用更复杂的类型推导逻辑，例如使用`std::common_type`。这是c14标准例如：

```cpp
template <typename... Args>
auto sum3(const Args... args) -> std::common_type_t<Args...> {
  const auto values = {args...};
  return std::accumulate(values.begin(), values.end(), std::common_type_t<Args...>{0});
}
```

#### 3.3 总结
使用`...`的时候有以下三个技巧
* 折叠表达式-c17标准
* 递归+递归结束条件-c11标准
* 使用`std::initializer_list`表示结束-c11/c14标准


### 99. 习题
```c++
// 1. recursive parameter unpack
template <typename T0> void printf1(T0 value) {
  std::cout << value << std::endl;
}
template <typename T, typename... Ts> void printf1(T value, Ts... args) {
  std::cout << value << std::endl;
  printf1(args...);
}

// 2. variadic template parameter unfold
template <typename T0, typename... T> void printf2(T0 t0, T... t) {
  std::cout << t0 << std::endl;
  if constexpr (sizeof...(t) > 0)
    printf2(t...);
}

// 3. parameter unpack using initializer_list
template <typename T, typename... Ts> auto printf3(T value, Ts... args) {
  std::cout << value << std::endl;
  (void)std::initializer_list<T>{
      ([&args] { std::cout << args << std::endl; }(), value)...};
}
```
p.s. : 第三种写法是用了lambda函数接`()`表示调用, 后面用一个`,value`是作为逗号表达式用的。