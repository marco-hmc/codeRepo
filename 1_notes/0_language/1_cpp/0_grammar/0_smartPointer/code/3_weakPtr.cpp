#include <iostream>
#include <memory>

template <typename T>
class weakPtr {
   private:
    T *ptr;

   public:
    weakPtr() : ptr(nullptr) {}
    weakPtr(T *p) : ptr(p) {}

    bool expired() const { return ptr == nullptr; }

    std::shared_ptr<T> lock() const {
        if (expired()) {
            return nullptr;
        }
        return std::shared_ptr<T>(ptr);
    }
};

class A;
class B;

class A {
   public:
    std::shared_ptr<B> pointer;
    ~A() { std::cout << "A was destroyed" << '\n'; }
};

class B {
   public:
    std::shared_ptr<A> pointer;
    ~B() { std::cout << "B was destroyed" << '\n'; }
};

void test_1() {
    /*
    这段代码中,`std::shared_ptr<A>`和`std::shared_ptr<B>`互相持有对方的引用,形成了一个循环引用.这会导致内存泄漏.
    在这个例子中,`a`和`b`都是`std::shared_ptr`,它们使用引用计数来管理内存.当`std::shared_ptr`的引用计数降为0时,它会自动删除所管理的对象.
    但是,如果两个`std::shared_ptr`互相引用,那么它们的引用计数永远不会降为0,因此它们所管理的对象永远不会被删除,导致内存泄漏.
    为了解决这个问题,可以使用`std::weak_ptr`来打破循环引用.`std::weak_ptr`是一种不控制对象生命周期的智能指针,它不会增加引用计数.
    当你需要使用`std::weak_ptr`指向的对象时,可以使用`lock`函数来获取一个`std::shared_ptr`.如果该对象还存在,`lock`函数会成功返回一个`std::shared_ptr`,否则返回`nullptr`.
*/
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
}

class MyClass {
   public:
    std::shared_ptr<MyClass> selfPtr;  // 使用shared_ptr来持有自身的强引用
    MyClass() { std::cout << "MyClass 构造函数被调用" << '\n'; }
    ~MyClass() { std::cout << "MyClass 析构函数被调用" << '\n'; }
};

void test_2() {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    sharedPtr->selfPtr = sharedPtr;  // 将shared_ptr赋值给自身的成员变量
    std::weak_ptr<MyClass> weakPtr =
        sharedPtr;  // 使用weak_ptr来持有shared_ptr的弱引用

    if (std::shared_ptr<MyClass> sharedPtr2 =
            weakPtr.lock()) {  // 使用lock()方法获取shared_ptr的强引用
        std::cout << "weak_ptr有效,对象仍然存在" << '\n';
    } else {
        std::cout << "weak_ptr无效,对象已被销毁" << '\n';
    }
}

int main() {
    std::shared_ptr<int> sharedPtr(new int(42));
    weakPtr<int> weak(sharedPtr.get());

    std::cout << "Expired: " << (weak.expired() ? "true" : "false") << '\n';

    std::shared_ptr<int> lockedPtr = weak.lock();
    if (lockedPtr) {
        std::cout << "Value: " << *lockedPtr << '\n';
    } else {
        std::cout << "Weak pointer expired." << '\n';
    }
    return 0;
}
