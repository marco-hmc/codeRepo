## 4. 模板特化

模板特化（Template Specialization）是 C++ 模板编程中的一个重要概念，它允许你为特定的模板参数提供特殊的实现。模板特化分为部分特化和全特化。通过模板特化，你可以为特定类型或特定条件提供优化的实现，从而提高代码的灵活性和性能。

### 4.1 部分特化

部分特化（Partial Specialization）是指为模板的某些特定参数提供特殊的实现，而不是为所有参数提供特殊的实现。部分特化通常用于类模板，因为函数模板不支持部分特化。

```cpp
#include <iostream>

// 通用类模板
template <typename T, typename U>
class MyClass {
public:
    void print() {
        std::cout << "Primary template" << std::endl;
    }
};

// 部分特化，当第二个模板参数为 int 时
template <typename T>
class MyClass<T, int> {
public:
    void print() {
        std::cout << "Partial specialization: second parameter is int" << std::endl;
    }
};

int main() {
    MyClass<double, double> obj1;
    obj1.print(); // 输出 "Primary template"

    MyClass<double, int> obj2;
    obj2.print(); // 输出 "Partial specialization: second parameter is int"

    return 0;
}
```

### 4.2 全特化

全特化（Full Specialization）是指为模板的所有参数提供特殊的实现。全特化可以用于类模板和函数模板。通过全特化，你可以为特定的模板参数组合提供完全不同的实现。

```cpp
#include <iostream>

// 通用类模板
template <typename T>
class MyClass {
public:
    void print() {
        std::cout << "Primary template" << std::endl;
    }
};

// 全特化，当模板参数为 int 时
template <>
class MyClass<int> {
public:
    void print() {
        std::cout << "Full specialization for int" << std::endl;
    }
};

int main() {
    MyClass<double> obj1;
    obj1.print(); // 输出 "Primary template"

    MyClass<int> obj2;
    obj2.print(); // 输出 "Full specialization for int"

    return 0;
}
```

### 4.3 特化的应用场景

模板特化在以下场景中非常有用：

1. **优化特定类型**：为特定类型提供优化的实现。例如，为 `int` 类型提供特殊的实现，以提高性能。
2. **处理特殊情况**：处理特定类型或条件下的特殊情况。例如，为指针类型提供特殊的实现，以处理指针的解引用和内存管理。
3. **实现类型特征**：实现类型特征（type traits），用于在编译时检查类型属性。例如，检查类型是否为指针类型、是否为整数类型等。

模板特化是 C++ 模板编程中的一个重要概念，它允许你为特定的模板参数提供特殊的实现。模板特化分为部分特化和全特化。部分特化用于为模板的某些特定参数提供特殊的实现，而全特化用于为模板的所有参数提供特殊的实现。通过模板特化，你可以为特定类型或特定条件提供优化的实现，从而提高代码的灵活性和性能。模板特化在优化特定类型、处理特殊情况和实现类型特征等场景中非常有用。