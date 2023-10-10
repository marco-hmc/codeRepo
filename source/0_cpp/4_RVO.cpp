#include <iostream>

// 在没有RVO的情况下，会调用拷贝构造函数将 obj 复制到 newObj 中，输出：
// Constructor called
// Copy constructor called

// 但是，如果编译器进行了RVO优化，它会直接将 obj 放在 newObj 的内存空间中，而不是进行显式的拷贝操作。因此，只会输出：
// Constructor called

class MyObject {
public:
    MyObject() {
        std::cout << "Constructor called" << std::endl;
    }

    MyObject(const MyObject& other) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

MyObject createObject() {
    MyObject obj;
    return obj;
}

int main() {
    MyObject newObj = createObject();
    return 0;
}
