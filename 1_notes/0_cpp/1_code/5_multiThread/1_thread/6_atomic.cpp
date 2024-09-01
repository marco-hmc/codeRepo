#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> global_counter(0);

void increase_global(int n) {
  for (int i = 0; i < n; ++i)
    ++global_counter;
}

void increase_reference(std::atomic<int> &variable, int n) {
  for (int i = 0; i < n; ++i)
    ++variable;
}

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}
  void increase_member(int n) {
    for (int i = 0; i < n; ++i)
      fetch_add(1);
  }
};

int main() {
  std::vector<std::thread> threads;

  std::cout << "increase global counter with 10 threads...\n";
  for (int i = 1; i <= 10; ++i)
    threads.push_back(std::thread(increase_global, 1000));

  std::cout << "increase counter (foo) with 10 threads using   reference...\n";
  std::atomic<int> foo(0);
  for (int i = 1; i <= 10; ++i) {
    threads.push_back(std::thread(increase_reference, std::ref(foo), 1000));
  }

  std::cout << "increase counter (bar) with 10 threads using member...\n";
  C bar;
  for (int i = 1; i <= 10; ++i) {
    threads.push_back(std::thread([&bar]() { bar.increase_member(1000); }));
  }

  std::cout << "synchronizing all threads...\n";
  for (auto &th : threads)
    th.join();

  std::cout << "global_counter: " << global_counter << '\n';
  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';

  return 0;
}

/*
1. 什么是原子操作？
   原子操作是不可分割的操作。在多线程编程中，原子操作是指一个操作要么完全执行，要么完全不执行，不会被其他线程中断。

*/