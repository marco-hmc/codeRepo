#### 1. std::void_t的实现和用法
```c++
namespace std {
    template<typename... Ts> using void_t = void;
}
```
常用于编译时检查一个类型是否具有某个特定的成员类型、成员函数或属性。
例如，你可以这样使用它：

```c++
struct A { using type = int; };
struct B {};

static_assert(has_type<A, std::void_t<A::type>>::value, "A has a member named type");
static_assert(!has_type<B, std::void_t<B::type>>::value, "B does not have a member named type");
```

#### 2. std::enable_if的实现和用法
```c++
namespace std {
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}
```

std::enable_if的第一个参数是一个编译时常量表达式，用于控制是否启用某个函数或类型。
如果表达式为true，std::enable_if将有一个名为type的成员类型，等同于它的第二个参数（如果提供）。

```c++
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T value) {
    std::cout << "处理整数: " << value << std::endl;
    return value;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
process(T value) {
    std::cout << "处理浮点数: " << value << std::endl;
    return value;
}
```

`std::enable_if_t`另一个常见的用法是用来开启模板

```c++
template <
  class Foo, 
  class Bar, 
  typename = std::enable_if_t<xxx>
>

```
typename =的用法定义了一个默认模板参数，这个参数的存在依赖于std::enable_if_t表达式的结果。如果xxx的结果为true，则这个模板重载被启用；否则，由于SFINAE，这个模板重载被编译器忽略，不会参与到重载解析中。这样，开发者可以根据类型特征在编译时控制模板的选择和使用。

#### 3. std::declval的实现和用用法
```c++
// std::declval的实现
namespace std {
    template<class T>
    add_rvalue_reference_t<T> declval() noexcept; // 仅声明，无需定义
}
```


std::declval是一个在编译时用于类型推断的工具，它可以用来获取一个类型的引用，而不需要实际构造该类型的对象。这在处理无法默认构造或不想构造对象的类型时特别有用。上述代码展示了std::declval的实现（实际上是一个未定义的函数模板，仅用于类型推断）和一个使用场景，即推断类成员函数的返回类型。

```c++
#include <iostream>
#include <type_traits>

// 示例类
class MyClass {
public:
    int myFunction() const {
        return 42;
    }
};

// 用于在编译时推断成员函数的返回类型
template <typename T>
auto testFunctionReturnType() -> decltype(std::declval<T>().myFunction()) {
    // 注意：这里不会实际调用T::myFunction，因此可以用于不可默认构造的类型
    return std::declval<T>().myFunction();
}

int main() {
    // 验证推断的类型是否为int
    static_assert(std::is_same<decltype(testFunctionReturnType<MyClass>()), int>::value, "返回类型应为int");
    std::cout << "推断的返回类型为int" << std::endl;
    return 0;
}
```

在C++标准库中，除了`std::declval`、`std::enable_if`和`std::void_t`之外，还有许多专门用于模板元编程的类模板和类型特征。以下是一些常用的：

1. **std::conditional**
   ```c++
   template< bool B, class T, class F >
   using conditional = typename conditional<B,T,F>::type;
   ```
   根据布尔常量`B`的值选择两种类型之一。

2. **std::is_same**
   ```c++
   template< class T, class U >
   struct is_same;
   ```
   检查两个类型是否相同。

3. **std::remove_reference**
   ```c++
   template< class T >
   struct remove_reference;
   ```
   移除类型的引用修饰符。

4. **std::remove_const**
   ```c++
   template< class T >
   struct remove_const;
   ```
   移除类型的`const`修饰符。

5. **std::integral_constant**
   ```c++
   template<class T, T v>
   struct integral_constant;
   ```
   表示一个编译时常量值。

6. **std::is_base_of**
   ```c++
   template< class Base, class Derived >
   struct is_base_of;
   ```
   检查一个类型是否是另一个类型的基类。

7. **std::is_convertible**
   ```c++
   template< class From, class To >
   struct is_convertible;
   ```
   检查一个类型是否可以转换为另一个类型。

8. **std::decay**
   ```c++
   template< class T >
   struct decay;
   ```
   将类型转换为它的“衰减”类型，模拟通过值传递参数时的类型转换。

这些工具和类型特征在模板元编程中非常有用，它们可以帮助开发者编写出更通用、更灵活的模板代码。
