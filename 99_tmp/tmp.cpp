#include <iostream>
#include <thread>
#include <unistd.h>

int a = 0;
int b = 0;

void func_1() {
  a = 1; // 1
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << b << std::endl; // 2
}

void func_2() {
  b = 2; // 3
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << a << std::endl; // 4
}

int main() {
  std::thread t1(func_1);
  std::thread t2(func_2);
  t1.join();
  t2.join();
  return 0;
}