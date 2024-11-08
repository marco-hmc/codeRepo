// 1. * *std::conditional**
//    ```c++ template <bool B, class T, class F>
//      using conditional = typename conditional<B, T, F>::type;
// ``` 根据布尔常量`B`的值选择两种类型之一。

// 6. **std::is_base_of**
//    ```c++
//    template< class Base, class Derived >
//    struct is_base_of;
//    ```
//    检查一个类型是否是另一个类型的基类。

// 7. **std::is_convertible**
//    ```c++
//    template< class From, class To >
//    struct is_convertible;
//    ```
//    检查一个类型是否可以转换为另一个类型。
