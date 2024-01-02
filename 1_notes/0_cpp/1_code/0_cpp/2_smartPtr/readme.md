#### 1. 释放器
#### 2. 异常安全
#### 3. weak_ptr
shared_ptr<Node> bar(new Node(),funcf);

```cpp
//初始化方式1
std::unique_ptr<int> sp1(new int(123));

//初始化方式2
std::unique_ptr<int> sp2;
sp2.reset(new int(123));

//初始化方式3
std::unique_ptr<int> sp3 = std::make_unique<int>(123);
```
你应该尽量使用初始化方式 3 的方式去创建一个 **std::unique_ptr** 而不是方式 1 和 2,因为形式 3 更安全,原因 Scott Meyers 在其<Effective Modern C++>中已经解释过了,有兴趣的读者可以阅读此书相关章节.

> 令很多人对 C++11 规范不满的地方是,C++11 新增了 std::make_shared() 方法创建一个 std::shared_ptr 对象,却没有提供相应的 std::make_unique() 方法创建一个 std::unique_ptr 对象,这个方法直到 C++14 才被添加进来.当然,在 C++11 中你很容易实现出这样一个方法来:

鉴于 **std::auto_ptr** 的前车之鉴,**std::unique_ptr** 禁止复制语义,为了达到这个效果,**std::unique_ptr** 类的拷贝构造函数和赋值运算符(operator =)被标记为 **delete**.

- 分清楚场合应该使用哪种类型的智能指针;

  通常情况下,如果你的资源不需要在其他地方共享,那么应该优先使用 **std::unique_ptr**,反之使用 **std::shared_ptr**,当然这是在该智能指针需要管理资源的生命周期的情况下;如果不需要管理对象的生命周期,请使用 **std::weak_ptr**.
