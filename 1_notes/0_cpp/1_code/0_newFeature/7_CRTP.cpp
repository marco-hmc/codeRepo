// ## 7 CRTP

// CRTP,全称Curiously Recurring Template Pattern(奇异递归模板模式),是一种在C++中使用模板来实现静态多态性的技术.

// 在CRTP中,一个类通过继承自己的模板实例来实现特定的行为.这听起来可能有些奇怪,但实际上这是一种非常强大的技术,可以用来实现编译时的多态性,避免虚函数带来的运行时开销.

template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // 实现具体的功能
    }
};

int main() {
    Derived d;
    d.interface();  // 调用Derived::implementation()
    return 0;
}
// 在这个例子中,Base是一个模板类,它有一个名为interface的函数,这个函数调用了Derived类的implementation函数.Derived类继承自Base<Derived>,并提供了implementation函数的实现.

// 当我们在main函数中创建一个Derived对象并调用其interface函数时,实际上调用的是Derived::implementation函数.这就是CRTP的工作原理:它允许我们在编译时确定要调用的函数,从而实现静态多态性.