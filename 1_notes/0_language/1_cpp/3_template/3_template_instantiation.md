## 3. 模板实例化

模板实例化是指将模板转换为具体类型的过程。在 C++ 中，模板实例化有两种主要方式：显式实例化和隐式实例化。模板实例化的时机也非常重要，因为它决定了模板代码何时被编译。

模板实例化是将模板代码转换为具体类型的代码的过程。显式实例化和隐式实例化是两种主要的模板实例化方式。显式实例化通过明确指定模板参数强制编译器生成特定类型的模板实例，而隐式实例化则由编译器在需要使用模板时自动生成模板实例。模板实例化的时机对编译速度和代码膨胀有重要影响。通过理解模板实例化的概念、显式实例化、隐式实例化和模板实例化的时机，可以更好地编写和优化模板代码。

### 3.1 模板实例化的概念

模板实例化是将模板代码转换为具体类型的代码的过程。模板实例化发生在编译时，编译器会根据模板参数生成具体的函数或类定义。模板实例化的结果是一个具体的函数或类，可以在程序中使用。

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int result1 = add(3, 4); // 这里发生了模板实例化，生成了 int 类型的 add 函数
    double result2 = add(3.5, 4.5); // 这里发生了模板实例化，生成了 double 类型的 add 函数
    return 0;
}
```

### 3.2 显式实例化

显式实例化是指在代码中明确指定模板参数，从而强制编译器生成特定类型的模板实例。显式实例化通常用于提高编译速度或减少代码膨胀。

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 显式实例化 add 函数模板
template int add<int>(int, int);
template double add<double>(double, double);

int main() {
    int result1 = add(3, 4); // 使用显式实例化的 int 类型的 add 函数
    double result2 = add(3.5, 4.5); // 使用显式实例化的 double 类型的 add 函数
    return 0;
}
```

### 3.3 隐式实例化

隐式实例化是指编译器在需要使用模板时自动生成模板实例。隐式实例化通常发生在模板被第一次使用时，编译器会根据模板参数自动生成具体的函数或类定义。

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int result1 = add(3, 4); // 这里发生了隐式实例化，生成了 int 类型的 add 函数
    double result2 = add(3.5, 4.5); // 这里发生了隐式实例化，生成了 double 类型的 add 函数
    return 0;
}
```

### 3.4 模板实例化的时机

模板实例化的时机是指模板代码何时被编译器转换为具体类型的代码。模板实例化通常发生在模板被第一次使用时，但也可以通过显式实例化提前进行。模板实例化的时机对编译速度和代码膨胀有重要影响。

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 显式实例化 add 函数模板
template int add<int>(int, int);

int main() {
    int result1 = add(3, 4); // 使用显式实例化的 int 类型的 add 函数
    double result2 = add(3.5, 4.5); // 这里发生了隐式实例化，生成了 double 类型的 add 函数
    return 0;
}
```


### 99. quiz

#### 1. 不同源文件都使用了`vector<int>`，这是实例化了几次？代码有几次？
在 C++ 中，模板实例化的行为取决于编译器和链接器的实现。通常情况下，如果多个源文件都使用了相同的模板实例（例如 vector<int>），编译器会在每个使用该模板实例的源文件中生成一份实例化代码。然而，链接器会负责消除重复的实例化代码，只保留一份最终的实例化代码。

也就是说不同源文件使用了相同的模板实例就会各自实例化，但是链接器会优化，合并重复实例代码。

```c++
// 在头文件 template_example.h 中
template<typename T>
class MyClass {
public:
    void doSomething();
};

// 在一个源文件 template_example.cpp 中
#include "template_example.h"

// 显式实例化定义（在这个翻译单元中生成实例化代码）
template class MyClass<int>;

// 在其他源文件中使用时
// 显式实例化声明（只声明实例化，避免重复定义）
extern template class MyClass<int>;

```