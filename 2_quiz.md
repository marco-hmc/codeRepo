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

* 类型放松 协变返回:
只能用于返回类型是指针或引用的情况
覆盖函数的类型必须与它所覆盖的虚函数类型完全一致,但是C++吧,就觉得既然都is-a,那么可以说,如果原返回类型是Base*,那么覆盖的函数可以返回Derived*,类似的,返回的类型是Base&,那么覆盖函数可以返回Derived&.这叫协变返回.<br>
