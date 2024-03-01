#include <iostream>

template <typename T>
class SharedPtr {
public:
    T* ptr;
    int* refCount;

    SharedPtr(T* p) : ptr(p), refCount(new int(1)) {}

    ~SharedPtr() {
        reset();
    }

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount);
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    int use_count() const {
        return *refCount;
    }

    void reset() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
        ptr = nullptr;
        refCount = nullptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }
};

int main() {
    SharedPtr<int> sp1(new int(5));
    SharedPtr<int> sp2(sp1);

    std::cout << "sp1: " << *sp1 << ", use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2: " << *sp2 << ", use_count: " << sp2.use_count() << std::endl;

    sp1.reset();

    std::cout << "sp1: " << sp1.get() << ", use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2: " << *sp2 << ", use_count: " << sp2.use_count() << std::endl;

    return 0;
}
