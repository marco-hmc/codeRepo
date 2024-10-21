\[([^\]]+)\]\([^\)]+\)
$1

to readingRepo
the lazy fox jumps over brown dog

## 怎么开始阅读一个大项目？

### 
1. 知道意图，看文档，问人
2. 断点调试
3. 修改
4. 重构（减少重复代码，函数提取）
5. 添加测试

#include <iostream>
#include <new>  // 用于 placement new
#include <string>

int main() {
    // 预先分配一块内存
    alignas(std::string) char buffer[sizeof(std::string)];

    // 使用 placement new 在指定内存位置上构造 std::string 对象
    std::string* strPtr = new (buffer) std::string("Hello, Placement New");

    // 打印字符串值
    std::cout << *strPtr << std::endl;

    // 显式调用 std::string 的析构函数
    strPtr->~std::string();

    return 0;
}