// ####1. std::void_t的实现和用法
// ```c++ namespace std {
//     template <typename... Ts>
//     using void_t = void;
// }
// ``` 常用于编译时检查一个类型是否具有某个特定的成员类型、成员函数或属性。
//     例如，你可以这样使用它：

// ```c++ struct A {
//     using type = int;
// };
// struct B {};

// static_assert(has_type<A, std::void_t<A::type>>::value,
//               "A has a member named type");
// static_assert(!has_type<B, std::void_t<B::type>>::value,
//               "B does not have a member named type");
// ```
