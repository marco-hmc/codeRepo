* 为什么右值可以被常量左值引用 引用?
   ```cpp
   const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
   ```

* 为什么要设置nullptr
    ```cpp
    A(A&& a):pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "移动" << pointer << std::endl;
    }
    ```

* 右值引用是左值还是右值?

* 什么是完美转发?std::forward<T>, 什么是引用坍缩?