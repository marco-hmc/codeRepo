#include <iostream>
#include <memory>

class MyClass {
public:
    std::shared_ptr<MyClass> selfPtr; // 使用shared_ptr来持有自身的强引用

    MyClass() {
        std::cout << "MyClass 构造函数被调用" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass 析构函数被调用" << std::endl;
    }
};

int main() {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    sharedPtr->selfPtr = sharedPtr; // 将shared_ptr赋值给自身的成员变量

    std::weak_ptr<MyClass> weakPtr = sharedPtr; // 使用weak_ptr来持有shared_ptr的弱引用

    if (std::shared_ptr<MyClass> sharedPtr2 = weakPtr.lock()) { // 使用lock()方法获取shared_ptr的强引用
        std::cout << "weak_ptr有效,对象仍然存在" << std::endl;
    } else {
        std::cout << "weak_ptr无效,对象已被销毁" << std::endl;
    }

    return 0;
}
