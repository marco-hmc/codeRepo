#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

void print_int(std::future<int> &fut) {
  int x = fut.get();
  std::cout << "value: " << x << '\n';
}

int main() {
  std::promise<int> foo;
  std::promise<int> bar =
      std::promise<int>(std::allocator_arg, std::allocator<int>());

  std::future<int> fut = bar.get_future();

  std::thread th(print_int, std::ref(fut));

  bar.set_value(20);

  th.join();
  return 0;
}

/*
1. promise怎么用？讲解一下用法。
  std::promise是C++11引入的一个类模板，它可以用于在一个线程中存储一个值或异常，然后在另一个线程中获取这个值或异常。这样可以实现线程间的同步。

  std::promise<int> prom;
  std::future<int> fut = prom.get_future();
  prom.set_value(10);
  int x = fut.get();

*/