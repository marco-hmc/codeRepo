#include <cassert>
#include <exception>

template <typename T>
class SmartPtr {
private:
    T* ptr; // 指向被管理的资源
    int* count; // 引用计数器

public:
    SmartPtr(T* p) : ptr(p), count(new int(1)) {}

    SmartPtr(const SmartPtr& other) : ptr(other.ptr), count(other.count) {
        (*count)++;
    }

    ~SmartPtr() {
        (*count)--;
        if (*count == 0) {
            delete ptr;
            delete count;
        }
    }

    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            (*count)--;
            if (*count == 0) {
                delete ptr;
                delete count;
            }
            ptr = other.ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }
};

int main() {
    // Test the SmartPtr class
    int* num = new int(42);
    SmartPtr<int> ptr1(num);
    SmartPtr<int> ptr2 = ptr1;

    // Test dereferencing operator *
    assert(*ptr1 == 42);
    assert(*ptr2 == 42);

    // Test arrow operator ->
    assert(ptr1.operator->() == num);
    assert(ptr2.operator->() == num);


    // Test assignment operator =
    int* num2 = new int(99);
    SmartPtr<int> ptr3(num2);
    ptr3 = ptr1;
    assert(*ptr3 == 42);

    // Test destruction of SmartPtr objects
    {
        SmartPtr<int> ptr4 = ptr1;
        SmartPtr<int> ptr5 = ptr1;
        assert(*ptr4 == 42);
        assert(*ptr5 == 42);
    }

    // Test self-assignment
    ptr1 = ptr1;
    assert(*ptr1 == 42);

    // Test destruction of last SmartPtr object
    {
        SmartPtr<int> ptr6 = ptr1;
        assert(*ptr6 == 42);
    }

    // Test destruction of SmartPtr object with nullptr
    SmartPtr<int> ptr7(nullptr);

    // Test dereferencing nullptr
    try {
        int value = *ptr7;
        // The above line should throw an exception, so the following line should not be executed
        assert(false);
    }
    catch (const std::exception& e) {
     // Expected exception
    }

    // Test arrow operator with nullptr
    try {
        int* value = ptr7.operator->();
        // The above line should throw an exception, so the following line should not be executed
        assert(false);
    }
    catch (const std::exception& e) {
     // Expected exception
    }

    delete num;
    delete num2;

    return 0;
}