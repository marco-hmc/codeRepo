#include <iostream>
#include <new>  // 用于 placement new
#include <string>

using namespace std;
int main() {
    // 预先分配一块内存
    alignas(std::string) char buffer[sizeof(std::string)];

    // 使用 placement new 在指定内存位置上构造 std::string 对象
    std::string* strPtr = new (buffer) std::string("Hello, Placement New");

    // 打印字符串值
    std::cout << *strPtr << std::endl;

    // 显式调用 std::string 的析构函数
    strPtr->std::~string();

    return 0;
}