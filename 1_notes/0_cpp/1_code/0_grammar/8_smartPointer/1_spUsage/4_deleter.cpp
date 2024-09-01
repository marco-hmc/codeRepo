#include <iostream>
#include <memory>

// 自定义deleter函数
struct CustomDeleter {
  void operator()(int *ptr) {
    std::cout << "Custom deleter is called\n";
    delete ptr;
  }
};

int main() {
  // 使用智能指针和自定义deleter
  std::unique_ptr<int, CustomDeleter> ptr(new int(42));

  // 使用智能指针访问资源
  std::cout << *ptr << '\n';

  // 智能指针会在作用域结束时自动释放资源
  return 0;
}