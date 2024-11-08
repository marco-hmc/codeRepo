// 1. **std::conditional**
//    ```c++
//    template< bool B, class T, class F >
//    using conditional = typename conditional<B,T,F>::type;
//    ```
//    根据布尔常量`B`的值选择两种类型之一。
