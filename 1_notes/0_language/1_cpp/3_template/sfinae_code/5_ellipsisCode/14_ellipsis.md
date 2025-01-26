## c++ 中的省略号

### 1. c++ 中的省略号怎么用？
在C++中，省略号（...）只有一种本质用途，接受不定长或者说变长的输入。根据输入，又可以进一步分为是，函数参数和模板参数。

1. 可变函数参数（Var-args）：
    在C风格的函数中，省略号用于表示一个可变数量的参数。在这个例子中，`...`表示函数`print`可以接受任意数量的参数，这些参数的类型和数量在编译时期是未知的。`va_start`、`va_arg`和`va_end`是处理这些参数的宏。
    ```cpp
    #include <cstdarg>
    void print(const char* format, ...) {
        // 注意，使用可变参数列表需要谨慎，因为它们不提供类型安全。在可能的情况下，应优先使用可变参数模板。
        va_list args;
        va_start(args, format);
        // ...
        va_end(args);
    }
    ```

1. 可变模板参数（Variadic Templates）：
    在模板编程中，省略号用于表示一个参数包（Parameter Pack），可以包含零个或多个参数。在这个例子中，`Args... args`表示一个参数包，可以接受任意数量和类型的参数。
    ```cpp
    template <typename... Args>
    void print(Args... args) {
        // ...
    }
    ```



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

----
----


模板一直是 C++ 所独有的**黑魔法**(一起念:**Dark Magic**)之一.
允许任意个数/任意类别的模板参数,同时也不需要在定义时将参数的个数固定.

```cpp
template<typename... Ts> class Magic;
```

```cpp
class Magic<int,
            std::vector<int>,
            std::map<std::string,
            std::vector<int>>> darkMagic;
```

既然是任意形式,所以个数为 `0` 的模板参数也是可以的:`class Magic<> nothing;`.

如果不希望产生的模板参数个数为 `0`,可以手动的定义至少一个模板参数:

```cpp
template<typename Require, typename... Args> class Magic;
```

变长参数模板也能被直接调整到到模板函数上.传统 C 中的 `printf` 函数,
虽然也能达成不定个数的形参的调用,但其并非类别安全.
而 C++11 除了能定义类别安全的变长参数函数外,
还可以使类似 `printf` 的函数能自然地处理非自带类别的对象.
除了在模板参数中能使用 `...` 表示不定长模板参数外,
函数参数也使用同样的表示法代表不定长参数,
这也就为我们简单编写变长参数函数提供了便捷的手段,例如:

```cpp
template<typename... Args> void printf(const std::string &str, Args... args);
```

那么我们定义了变长的模板参数,如何对参数进行解包呢?

首先,我们可以使用 `sizeof...` 来计算参数的个数,:

```cpp
template<typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}
```

我们可以传递任意个参数给 `magic` 函数:

```cpp
magic(); // 输出0
magic(1); // 输出1
magic(1, ""); // 输出2
```

其次,对参数进行解包,到目前为止还没有一种简单的方法能够处理参数包,但有两种经典的处理手法:

**1. 递归模板函数**

递归是非常容易想到的一种手段,也是最经典的处理方法.这种方法不断递归地向函数传递模板参数,进而达到递归遍历所有模板参数的目的:

```cpp
#include <iostream>
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}
int main() {
    printf1(1, 2, "123", 1.1);
    return 0;
}
```

**2. 变参模板展开**

你应该感受到了这很繁琐,在 C++17 中增加了变参模板展开的支持,于是你可以在一个函数中完成 `printf` 的编写:

```cpp
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}
```

> 事实上,有时候我们虽然使用了变参模板,却不一定需要对参数做逐个遍历,我们可以利用 `std::bind` 及完美转发等特性实现对函数和参数的绑定,从而达到成功调用的目的.

**3. 初始化列表展开**

递归模板函数是一种标准的做法,但缺点显而易见的在于必须定义一个终止递归的函数.

这里介绍一种使用初始化列表展开的黑魔法:

```cpp
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{
        ([&args] {std::cout << args << std::endl;}(), value)...
    };
}
```

在这个代码中,额外使用了 C++11 中提供的初始化列表以及 Lambda 表达式的特性(下一节中将提到).

通过初始化列表,`(lambda 表达式, value)...` 将会被展开.由于逗号表达式的出现,首先会执行前面的 lambda 表达式,完成参数的输出.
为了避免编译器警告,我们可以将 `std::initializer_list` 显式的转为 `void`.



## 变参模板（Variadic Template）

* C++11 引入了 [sizeof...](https://en.cppreference.com/w/cpp/language/sizeof...) 在编译期计算参数包中的元素数，C++17 引入了 if constexpr 判断编译期值，编译期结果为 true 才会实例化代码

```cpp
#include <iostream>
#include <string>
#include <utility>

namespace jc {

template <typename T, typename... Args>
void print(const T& t, Args&&... args) {
  std::cout << t << std::endl;
  if constexpr (sizeof...(args) > 0) {  // 不能用 if，因为零长包也会实例化代码
    print(std::forward<Args>(args)...);  // 当条件满足时才实例化
  }
}

}  // namespace jc

int main() { jc::print(3.14, 42, std::string{"hello"}, "world"); }
```


## [折叠表达式（Fold Expression）](https://en.cppreference.com/w/cpp/language/fold)

* 对于空扩展需要决定类型和值，空的一元折叠表达式通常会产生错误，除了三种例外情况
  * 一个 `&&` 的一元折叠的空扩展产生值 true
  * 一个 `||` 的一元折叠的空扩展产生值 false
  * 一个 `,` 的一元折叠空扩展产生一个 void 表达式

|折叠表达式|计算结果|
|:-:|:-:|
|(... op pack)|(((pack1 op pack2) op pack3) ... op PackN)|
|(pack op ...)|(pack1 op (... (packN-1 op packN)))|
|(init op ... op pack)|(((init op pack1) op pack2) ... op PackN)|
|(pack op ... op init)|(pack1 op (... (packN op init)))|

* 折叠表达式借鉴的是 [Haskell](https://www.haskell.org/) 的 fold

```hs
import Data.List (foldl')

foldlList :: [Char]
foldlList = foldl' (\x y -> concat ["(", x, "+", y, ")"]) "0" (map show [1 .. 4])

foldrList :: [Char]
foldrList = foldr ((\x y -> concat ["(", x, "+", y, ")"]) . show) "0" [1 .. 4]

main :: IO ()
main = do
  putStrLn foldlList -- ((((0+1)+2)+3)+4)
  putStrLn foldrList -- (1+(2+(3+(4+0))))
```

* 实现与 Haskell 类似的左折叠和右折叠

```cpp
#include <iostream>
#include <string>
#include <type_traits>

namespace jc {

template <typename F, typename T, typename... Args>
void foldlList(F&& f, T&& zero, Args&&... x) {
  ((std::invoke(std::forward<F>(f), (std::string(sizeof...(Args), '('))),
    std::invoke(std::forward<F>(f), (std::forward<T>(zero)))),
   ...,
   (std::invoke(std::forward<F>(f), ('+')),
    std::invoke(std::forward<F>(f), (std::forward<Args>(x))),
    std::invoke(std::forward<F>(f), (')'))));
}

template <typename F, typename T, typename... Args>
void foldrList(F&& f, T&& zero, Args&&... x) {
  ((std::invoke(std::forward<F>(f), ('(')),
    std::invoke(std::forward<F>(f), (std::forward<Args>(x))),
    std::invoke(std::forward<F>(f), ('+'))),
   ...,
   (std::invoke(std::forward<F>(f), (std::forward<T>(zero))),
    std::invoke(std::forward<F>(f), (std::string(sizeof...(Args), ')')))));
}

}  // namespace jc

int main() {
  auto print = [](const auto& x) { std::cout << x; };
  jc::foldlList(print, 0, 1, 2, 3, 4);  // ((((0+1)+2)+3)+4)
  jc::foldrList(print, 0, 1, 2, 3, 4);  // (1+(2+(3+(4+0))))
}
```

* 折叠表达式几乎可以使用所有二元运算符

```cpp
#include <cassert>

namespace jc {

struct Node {
  Node(int i) : val(i) {}

  int val = 0;
  Node* left = nullptr;
  Node* right = nullptr;
};

// 使用 operator->* 的折叠表达式，用于遍历指定的二叉树路径
template <typename T, typename... Args>
Node* traverse(T root, Args... paths) {
  return (root->*...->*paths);  // root ->* paths1 ->* paths2 ...
}

void test() {
  Node* root = new Node{0};
  root->left = new Node{1};
  root->left->right = new Node{2};
  root->left->right->left = new Node{3};

  auto left = &Node::left;
  auto right = &Node::right;
  Node* node1 = traverse(root, left);
  assert(node1->val == 1);
  Node* node2 = traverse(root, left, right);
  assert(node2->val == 2);
  Node* node3 = traverse(node2, left);
  assert(node3->val == 3);
}

}  // namespace jc

int main() { jc::test(); }
```

* 包扩展可以用于编译期表达式

```cpp
#include <type_traits>

namespace jc {

template <typename T, typename... Args>
constexpr bool is_homogeneous(T, Args...) {
  return (std::is_same_v<T, Args> && ...);  // operator&& 的折叠表达式
}

}  // namespace jc

static_assert(!jc::is_homogeneous(3.14, 42, "hello", "world"));
static_assert(jc::is_homogeneous("hello", "", "world"));

int main() {}
```

## 变参模板的应用

* 无需指定类型，自动获取 [std::variant](https://en.cppreference.com/w/cpp/utility/variant) 值

```cpp
#include <array>
#include <cassert>
#include <functional>
#include <string>
#include <type_traits>
#include <variant>

namespace jc {

template <typename F, std::size_t... N>
constexpr auto make_array_impl(F f, std::index_sequence<N...>)
    -> std::array<std::invoke_result_t<F, std::size_t>, sizeof...(N)> {
  return {std::invoke(f, std::integral_constant<decltype(N), N>{})...};
}

template <std::size_t N, typename F>
constexpr auto make_array(F f)
    -> std::array<std::invoke_result_t<F, std::size_t>, N> {
  return make_array_impl(f, std::make_index_sequence<N>{});
}

template <typename T, typename Dst, typename... List>
bool get_value_impl(const std::variant<List...>& v, Dst& dst) {
  if (std::holds_alternative<T>(v)) {
    if constexpr (std::is_convertible_v<T, Dst>) {
      dst = static_cast<Dst>(std::get<T>(v));
      return true;
    }
  }
  return false;
}

template <typename Dst, typename... List>
bool get_value(const std::variant<List...>& v, Dst& dst) {
  using Variant = std::variant<List...>;
  using F = std::function<bool(const Variant&, Dst&)>;
  static auto _list = make_array<sizeof...(List)>([](auto i) -> F {
    return &get_value_impl<std::variant_alternative_t<i, Variant>, Dst,
                           List...>;
  });
  return std::invoke(_list[v.index()], v, dst);
}

}  // namespace jc

int main() {
  std::variant<int, std::string> v = std::string{"test"};
  std::string s;
  assert(jc::get_value(v, s));
  assert(s == "test");
  v = 42;
  int i;
  assert(jc::get_value(v, i));
  assert(i == 42);
}
```

* 字节序转换

```cpp
// https://en.cppreference.com/w/cpp/language/fold

#include <cstdint>
#include <type_traits>
#include <utility>

namespace jc {

template <typename T, size_t... N>
constexpr T bswap_impl(T t, std::index_sequence<N...>) {
  return (((t >> N * 8 & 0xFF) << (sizeof(T) - 1 - N) * 8) | ...);
}

template <typename T, typename U = std::make_unsigned_t<T>>
constexpr U bswap(T t) {
  return bswap_impl<U>(t, std::make_index_sequence<sizeof(T)>{});
}

}  // namespace jc

static_assert(jc::bswap<std::uint32_t>(0x12345678u) == 0x78563412u);
static_assert((0x12345678u >> 0) == 0x12345678u);
static_assert((0x12345678u >> 8) == 0x00123456u);
static_assert((0x12345678u >> 16) == 0x00001234u);
static_assert((0x12345678u >> 24) == 0x00000012u);
static_assert(jc::bswap<std::uint16_t>(0x1234u) == 0x3412u);

int main() {}
```

* [自定义字面值（User-defined literals）](https://en.cppreference.com/w/cpp/language/user_literal)

```cpp
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

namespace jc {

template <char... args>
std::string operator"" _dbg() {
  std::array<char, sizeof...(args)> v{args...};
  std::stringstream os;
  for (const auto& x : v) {
    os << x;
  };
#ifndef NDEBUG
  std::cout << os.str() << std::endl;
#endif
  return os.str();
}

std::string operator"" _encrypt(const char* c, size_t) {
  std::string s{c};
  std::string p{R"(passwd: ")"};
  auto it = std::search(s.begin(), s.end(),
                        std::boyer_moore_horspool_searcher{p.begin(), p.end()});
  if (it != s.end()) {
    it += p.size();
    while (it != s.end() && *it != '\"') {
      *it++ = '*';
    }
  }
#if !defined(NDEBUG)
  std::cout << s << std::endl;
#endif
  return s;
}

}  // namespace jc

int main() {
  using namespace jc;

  assert(12.34_dbg == "12.34");

  std::string s = R"JSON({
  data_dir: "C:\Users\downdemo\.data\*.txt",
  user: "downdemo(accelerate rapidly)",
  passwd: "123456"
})JSON"_encrypt;

  std::string s2 = R"JSON({
  data_dir: "C:\Users\downdemo\.data\*.txt",
  user: "downdemo(accelerate rapidly)",
  passwd: "******"
})JSON";

  assert(s == s2);
}
```

* 变参基类

```cpp
#include <string>
#include <unordered_set>

namespace jc {

struct A {
  std::string s;
};

struct A_EQ {
  bool operator()(const A& lhs, const A& rhs) const { return lhs.s == rhs.s; }
};

struct A_Hash {
  std::size_t operator()(const A& a) const {
    return std::hash<std::string>{}(a.s);
  }
};

// 定义一个组合所有基类的 operator() 的派生类
template <typename... Bases>
struct Overloader : Bases... {
  using Bases::operator()...;  // C++17
};

using A_OP = Overloader<A_Hash, A_EQ>;

}  // namespace jc

int main() {
  // 将 A_EQ 和 A_Hash 组合到一个类型中

  /* unordered_set 的声明
  template<
  class Key,
      class Hash = std::hash<Key>,
      class KeyEqual = std::equal_to<Key>,
      class Allocator = std::allocator<Key>
  > class unordered_set;
  */

  std::unordered_set<jc::A, jc::A_Hash, jc::A_EQ> s1;
  std::unordered_set<jc::A, jc::A_OP, jc::A_OP> s2;
}
```

* C++14 使用 [std::integer_sequence](https://en.cppreference.com/w/cpp/utility/integer_sequence) 遍历 [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple)

```cpp
#include <cstddef>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

namespace jc {

template <typename F, typename... List, std::size_t... Index>
void apply_impl(F&& f, const std::tuple<List...>& t,
                std::index_sequence<Index...>) {
  std::invoke(std::forward<F>(f), std::get<Index>(t)...);
}

template <typename F, typename... List>
void apply(F&& f, const std::tuple<List...>& t) {
  apply_impl(std::forward<F>(f), t, std::index_sequence_for<List...>{});
}

}  // namespace jc

struct Print {
  template <typename... Args>
  void operator()(const Args&... args) {
    auto no_used = {(std::cout << args << " ", 0)...};
  }
};

int main() {
  auto t = std::make_tuple(3.14, 42, "hello world");
  jc::apply(Print{}, t);  // 3.14 42 hello world
}
```

* C++11 未提供 [std::integer_sequence](https://en.cppreference.com/w/cpp/utility/integer_sequence)，手动实现一个即可

```cpp
#include <cstddef>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

namespace jc {

template <std::size_t... Index>
struct index_sequence {
  using type = index_sequence<Index...>;
};

template <typename List1, typename List2>
struct concat;

template <std::size_t... List1, std::size_t... List2>
struct concat<index_sequence<List1...>, index_sequence<List2...>>
    : index_sequence<List1..., (sizeof...(List1) + List2)...> {};

template <typename List1, typename List2>
using concat_t = typename concat<List1, List2>::type;

template <std::size_t N>
struct make_index_sequence_impl
    : concat_t<typename make_index_sequence_impl<N / 2>::type,
               typename make_index_sequence_impl<N - N / 2>::type> {};

template <>
struct make_index_sequence_impl<0> : index_sequence<> {};

template <>
struct make_index_sequence_impl<1> : index_sequence<0> {};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_impl<N>::type;

template <typename... Types>
using index_sequence_for = make_index_sequence<sizeof...(Types)>;

static_assert(std::is_same_v<make_index_sequence<3>, index_sequence<0, 1, 2>>);

template <typename F, typename... List, std::size_t... Index>
void apply_impl(F&& f, const std::tuple<List...>& t, index_sequence<Index...>) {
  std::invoke(std::forward<F>(f), std::get<Index>(t)...);
}

template <typename F, typename... List>
void apply(F&& f, const std::tuple<List...>& t) {
  apply_impl(std::forward<F>(f), t, index_sequence_for<List...>{});
}

}  // namespace jc

struct Print {
  template <typename... Args>
  void operator()(const Args&... args) {
    auto no_used = {(std::cout << args << " ", 0)...};
  }
};

int main() {
  auto t = std::make_tuple(3.14, 42, "hello world");
  jc::apply(Print{}, t);  // 3.14 42 hello world
}
```

### 99. quiz
#### 1. 变长参数实现的原理是什么？
首先，汇编语言是不支持变长参数的。C++的可变参数模板（Variadic Templates）和C语言的可变参数列表（Varargs）都是通过编译器在编译时期进行处理的，而不是在运行时期。
因此，它们并不依赖于汇编语言的支持。
而进一步地，汇编语言可以通过把变长的参数压在某一个栈中，pop直至栈为空，来获取args；也可以在编译器推导出参数个数，传入函数实现。
具体实现需要考虑性能，

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
