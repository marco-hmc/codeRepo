#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

int main() {
    // 创建一个UniquePtr来管理一个整型对象
    UniquePtr<int> ptr(new int(42));

    // 使用UniquePtr访问所管理的对象
    std::cout << "Value: " << *ptr << std::endl;

    // 修改所管理的对象的值
    *ptr = 100;

    // 再次使用UniquePtr访问所管理的对象
    std::cout << "Value: " << *ptr << std::endl;

    // 释放UniquePtr所管理的对象
    ptr.reset();

    // 尝试访问已释放的对象会导致运行时错误
    // std::cout << "Value: " << *ptr << std::endl;

    return 0;
}
