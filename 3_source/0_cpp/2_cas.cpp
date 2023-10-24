#include <iostream>
#include <cstring>

class StringWithoutCopyAndSwap {
private:
    char* data;

public:
    StringWithoutCopyAndSwap(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // 实现拷贝构造函数
    StringWithoutCopyAndSwap(const StringWithoutCopyAndSwap& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 实现析构函数
    ~StringWithoutCopyAndSwap() {
        delete[] data;
    }

    // 实现赋值运算符
    StringWithoutCopyAndSwap& operator=(const StringWithoutCopyAndSwap& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    const char* c_str() const {
        return data;
    }
};

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
