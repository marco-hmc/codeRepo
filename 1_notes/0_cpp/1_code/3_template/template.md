## template

所以模板替换不是错误，是指模板实例化的时候如果和当前的模板函数匹配错误，不算失败，会继续尝试和其他模板匹配并完成实例化，但是如果没有任何一个模板函数能够完成模板实例化，还是会出现编译错误，对吗？
### 1. SFINAE
* 什么是重载决议？

* 实参的推断要求一致，其本身不会为了编译通过自动做类型转换
* 只有在函数调用前声明的重载才会被匹配，即使后续有更优先的匹配，由于不可见也会被忽略

### 变长参数模板

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
