#include <iostream>
#include <cstring>

class StringWithCopyAndSwap {
private:
    char* data;

public:
    StringWithCopyAndSwap(const char* str = "") : data(new char[strlen(str) + 1]) {
        strcpy(data, str);
    }

    // 实现拷贝构造函数
    StringWithCopyAndSwap(const StringWithCopyAndSwap& other) : data(new char[strlen(other.data) + 1]) {
        strcpy(data, other.data);
    }

    // 实现析构函数
    ~StringWithCopyAndSwap() {
        delete[] data;
    }

    // 实现 swap 函数
    void swap(StringWithCopyAndSwap& other) {
        std::swap(data, other.data);
    }

    // 实现赋值运算符
    StringWithCopyAndSwap& operator=(StringWithCopyAndSwap other) {
        swap(other);
        return *this;
    }

    const char* c_str() const {
        return data;
    }
};
