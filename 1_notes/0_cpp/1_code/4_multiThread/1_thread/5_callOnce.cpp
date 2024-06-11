#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
once_flag callflag;

static void once_print() { cout << '!'; }

static void print(size_t x) {
  std::call_once(callflag, once_print);
  cout << x;
}

int main() {
  vector<thread> v;

  for (size_t i{0}; i < 10; ++i) {
    v.emplace_back(print, i);
  }

  for (auto &t : v) {
    t.join();
  }
  cout << '\n';
}

/*
1. call_once是什么？

   `std::call_once`是一个C++标准库函数，用于确保一个函数或代码块只被执行一次。
   `std::call_once`接受一个`std::once_flag`对象和一个函数或代码块作为参数。
   `std::call_once`会检查`std::once_flag`对象是否已经被调用过，如果没有，那么它会调用传入的函数或代码块。
*/