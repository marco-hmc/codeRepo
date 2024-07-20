#include <iostream>

// inline int value = 42; // 使用inline修饰
// int value = 21; // 不使用inline修饰，尝试定义另一个同名变量

char value = 'x'; // 使用inline修饰
int value = 21;   // 不使用inline修饰，尝试定义另一个同名变量

int main() {
  std::cout << value << std::endl;
  return 0;
}