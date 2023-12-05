
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor" << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor" << std::endl;
    }
};

int main() {
    // 使用weak_ptr的场景
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = sharedPtr;

    if (auto sharedPtr2 = weakPtr.lock()) {
        std::cout << "Using weak_ptr: " << sharedPtr2 << std::endl;
    }
    else {
        std::cout << "weak_ptr is expired" << std::endl;
    }

    // 不使用weak_ptr导致抛出异常的代码例子
    std::shared_ptr<MyClass> sharedPtr3 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> sharedPtr4 = sharedPtr3;

    try {
        std::shared_ptr<MyClass> sharedPtr5 = sharedPtr3;
    }
    catch (const std::bad_weak_ptr& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
