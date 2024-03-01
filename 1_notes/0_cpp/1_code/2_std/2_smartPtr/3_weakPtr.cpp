#include <iostream>

template <typename T>
class weakPtr {
private:
    T* ptr;
public:
    weakPtr() : ptr(nullptr) {}

    weakPtr(T* p) : ptr(p) {}

    bool expired() const {
        return ptr == nullptr;
    }

    std::shared_ptr<T> lock() const {
        if (expired()) {
            return nullptr;
        }
        return std::shared_ptr<T>(ptr);
    }
};

int main() {
    // 创建一个对象
    std::shared_ptr<int> sharedPtr(new int(42));

    // 创建一个weakPtr对象
    weakPtr<int> weak(sharedPtr.get());

    // 检查weakPtr是否过期
    std::cout << "Expired: " << (weak.expired() ? "true" : "false") << std::endl;

    // 获取指向对象的shared_ptr
    std::shared_ptr<int> lockedPtr = weak.lock();
    if (lockedPtr) {
        std::cout << "Value: " << *lockedPtr << std::endl;
    }
    else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    return 0;
}
