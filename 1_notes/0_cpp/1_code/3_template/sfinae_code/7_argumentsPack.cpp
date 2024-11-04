#include <iostream>

template <typename T> void print(const T &t) {
  std::cout << t << '\n'; // 基本情况
}

template <typename T, typename... Args>
void print(const T &t, const Args &...args) {
  std::cout << t << ", ";
  print(args...); // 递归调用
}

template <typename... Args> void print(Args &&...args) {
  auto dummy = {(std::cout << args << ", ", 0)...};
  (void)dummy; // 避免未使用变量警告
}

template <typename... Args> void print2(Args &&...args) {
  (std::cout << ... << args) << '\n'; // 右折叠打印所有参数
}

template <typename... Args> void countArgs(Args &&...args) {
  std::cout << "Number of arguments: " << sizeof...(args) << '\n';
}

// C++11 引入了变参模板，用省略号表示一个，类型名后接省略号表示任意数量给定类型的参数。
// 在表达式后跟省略号，如果表达式中有参数包，就会把表达式应用到参数包中的每个参数。如果表达式中出现两次参数包，对整个表达式扩展，而不会做笛卡尔积计算

template <typename... Args>
void f(const Args&... args) {
  print(args + 1...);    // ERROR：1... 是带多个小数点的字面值，不合法
  print(args + 1 ...);   // OK
  print((args + 1)...);  // OK
}