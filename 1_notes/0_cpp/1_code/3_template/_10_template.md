
* 类型放松 协变返回:
只能用于返回类型是指针或引用的情况
覆盖函数的类型必须与它所覆盖的虚函数类型完全一致,但是C++吧,就觉得既然都is-a,那么可以说,如果原返回类型是Base*,那么覆盖的函数可以返回Derived*,类似的,返回的类型是Base&,那么覆盖函数可以返回Derived&.这叫协变返回.<br>



**1. 理解模板类型推导**

其他之前说过了，主要是T有三种情况：1.指针或引用。2.通用的引用。3.既不是指针也不是引用
    
    template<typename T>
    void f(T& param);   //param是一个引用
    
    int x = 27; // x是一个int
    const int cx = x; // cx是一个const int
    const int& rx = x; // rx是const int的引用
    上面三种在调用f的时候会编译出不一样的代码：
    f(x);  // T是int，param的类型时int&
    f(cx); // T是const int，param的类型是const int&
    f(rx); // T是const int， param的类型时const int&
    
    template<typename T>
    void f(T&& param); // param现在是一个通用的引用
    
    template<typename T>
    void f(T param); // param现在是pass-by-value

如果用数组或者函数指针来调用的话，模板会自动抽象成指针。
如果模板本身是第一种情况（指针或引用），那么就会自动编译成数组
---


* 模板类A中有一个static变量x,那么该程序中变量x的实例有几分?

### Compile-time integer sequences
The class template `std::integer_sequence` represents a compile-time sequence of integers. There are a few helpers built on top:
* `std::make_integer_sequence<T, N>` - creates a sequence of `0, ..., N - 1` with type `T`.
* `std::index_sequence_for<T...>` - converts a template parameter pack into an integer sequence.

Convert an array into a tuple:
```c++
template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
  return std::make_tuple(a[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a) {
  return a2t_impl(a, Indices());
}
```
