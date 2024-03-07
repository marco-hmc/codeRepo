#include <iostream>
#include <thread>
using namespace std;

// 普通函数 无参
void function_1() { cout << "null" << endl; }

void function_1(int i) { cout << "null" << endl; }
// 普通函数 1个参数
void function_2(int i) { cout << i << endl; }

// 普通函数 2个参数
void function_3(int i, std::string m) { cout << i << m << endl; }

void test_1() {
  // std::thread t1(function_1);
  std::thread t2(function_2, 1);
  std::thread t3(function_3, 1, "hello");
  t2.join();
  t3.join();
}

// void test_2(){
//     std::thread t1(function_1);
// }

int main() {
  test_1();
  // test_2(); // 报错，因为无法识别哪个函数
  return 0;
}