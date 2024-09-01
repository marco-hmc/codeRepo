#include <iostream>
#include <thread>

void function_1() { std::cout << "null" << '\n'; }
void function_1(int i) { std::cout << "null" << '\n'; }

void function_2(int i) { std::cout << i << '\n'; }

void test_1() {
  std::thread t1(static_cast<void (*)()>(function_1));
  // std::thread t11(function_1, 2);
  std::thread t2(function_2, 1);
  t2.join();
}

///////////////////////////////////////////
int main() {
  test_1();
  return 0;
}

/*
  1. 为什么function_1传入要这样子？
    使用静态类型转换来明确调用没有参数的function_1版本d
    如果不进行类型转换，编译器无法确定应该调用哪个function_1版本
    因为thread接受function_1是作为参数的，后面补上参数也不知道用哪个
*/
