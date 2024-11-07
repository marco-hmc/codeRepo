// #### 3. std::declval的实现和用用法
// ```c++
// // std::declval的实现
// namespace std {
//     template<class T>
//     add_rvalue_reference_t<T> declval() noexcept; // 仅声明，无需定义
// }
// ```

// std::declval是一个在编译时用于类型推断的工具，它可以用来获取一个类型的引用，而不需要实际构造该类型的对象。这在处理无法默认构造或不想构造对象的类型时特别有用。上述代码展示了std::declval的实现（实际上是一个未定义的函数模板，仅用于类型推断）和一个使用场景，即推断类成员函数的返回类型。

// ```c++
// #include <iostream>
// #include <type_traits>

// // 示例类
// class MyClass {
// public:
//     int myFunction() const {
//         return 42;
//     }
// };

// // 用于在编译时推断成员函数的返回类型
// template <typename T>
// auto testFunctionReturnType() -> decltype(std::declval<T>().myFunction()) {
//     // 注意：这里不会实际调用T::myFunction，因此可以用于不可默认构造的类型
//     return std::declval<T>().myFunction();
// }

// int main() {
//     // 验证推断的类型是否为int
//     static_assert(std::is_same<decltype(testFunctionReturnType<MyClass>()), int>::value, "返回类型应为int");
//     std::cout << "推断的返回类型为int" << std::endl;
//     return 0;
// }
// ```
