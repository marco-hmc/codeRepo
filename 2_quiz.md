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

* unique_ptr是怎么实现的?为什么把形参为左值引用的禁了,只放开了形参为右值引用的?

* shared_ptr是怎么实现的?为什么refCount要是指针?

* 常量左值引用可以绑定到临时对象吗?

* 为什么结构化绑定不能使用 constexpr 修饰或被申明为 static

* 为什么静态变量不可以在类里面初始化?

* cpp文件是怎么运行起来的

