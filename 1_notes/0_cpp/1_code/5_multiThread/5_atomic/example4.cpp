#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> foo(0);

void set_foo(int x) { foo.store(x, std::memory_order_relaxed); }

void print_foo() {
  int x = 0;
  do {
    x = foo.load(std::memory_order_relaxed);
  } while (x == 0);
  std::cout << "foo: " << x << '\n';
}

int main() {
  std::thread first(print_foo);
  std::thread second(set_foo, 10);
  first.join();
  second.join();
  return 0;
}

/*
1. 原子变量的store和load操作是什么意思，有什么用？
* store操作：将一个值存储到原子变量中，可以指定内存顺序(memory order)。
* load操作：从原子变量中加载一个值，可以指定内存顺序(memory order)。
* store和load操作是原子变量的基本操作，用于读写原子变量的值，可以保证操作的原子性和内存顺序。

*/