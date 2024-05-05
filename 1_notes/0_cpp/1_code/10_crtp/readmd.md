## CRTP
### 1. concept

#### 1.1 什么是CRTP

CRTP，全称为Curiously Recurring Template Pattern（奇异递归模板模式），是一种在 C++ 中使用模板来实现静态多态性的技术。

在 CRTP 中，一个类通过继承自己的模板实例来实现。例如：

```cpp
template <typename Derived>
class Base {};

class Derived : public Base<Derived> {};
```

在这个例子中，`Derived` 类继承自 `Base<Derived>`。这样，`Base` 类就可以在编译时知道其派生类的类型，从而实现静态多态性。

CRTP 的一个常见用途是提供基类中的函数，这些函数可以使用派生类的函数或者数据。例如，你可以在 `Base` 类中提供一个函数，这个函数调用 `Derived` 类中的一个函数。这样，你就可以在不知道具体派生类的情况下，通过基类的接口调用派生类的函数。

CRTP 的优点是它可以在编译时解析多态性，而不需要在运行时使用虚函数表，因此它通常比动态多态性（例如，通过虚函数实现）更高效。但是，CRTP 的缺点是它可能使代码更复杂，更难理解。

#### 1.2 CRTP解决了什么问题
#### 1.3 怎么用CRTP



