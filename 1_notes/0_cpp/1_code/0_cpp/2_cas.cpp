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

int main() {
    const char* str = "Hello, World!";
    StringWithoutCopyAndSwap s(str);
    std::cout << "s.c_str(): " << s.c_str() << std::endl;

    const char* str1 = "Hello";
    const char* str2 = "World";
    StringWithoutCopyAndSwap s1(str1);
    StringWithoutCopyAndSwap s2(str2);
    s2 = s1;
    std::cout << "s2.c_str(): " << s2.c_str() << std::endl;

    return 0;
}