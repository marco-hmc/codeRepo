// #### 2. std::enable_if的实现和用法
// ```c++
// namespace std {
//     template<bool B, class T = void>
//     struct enable_if {};

//     template<class T>
//     struct enable_if<true, T> { typedef T type; };
// }
// ```

// std::enable_if的第一个参数是一个编译时常量表达式，用于控制是否启用某个函数或类型。
// 如果表达式为true，std::enable_if将有一个名为type的成员类型，等同于它的第二个参数（如果提供）。

// ```c++
// template <typename T>
// typename std::enable_if<std::is_integral<T>::value, T>::type
// process(T value) {
//     std::cout << "处理整数: " << value << std::endl;
//     return value;
// }

// template <typename T>
// typename std::enable_if<std::is_floating_point<T>::value, T>::type
// process(T value) {
//     std::cout << "处理浮点数: " << value << std::endl;
//     return value;
// }
// ```

// `std::enable_if_t`另一个常见的用法是用来开启模板

// ```c++
// template <
//   class Foo,
//   class Bar,
//   typename = std::enable_if_t<xxx>
// >

// ```
// typename =的用法定义了一个默认模板参数，这个参数的存在依赖于std::enable_if_t表达式的结果。如果xxx的结果为true，则这个模板重载被启用；否则，由于SFINAE，这个模板重载被编译器忽略，不会参与到重载解析中。这样，开发者可以根据类型特征在编译时控制模板的选择和使用。
