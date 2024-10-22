#include <future>
#include <iostream>

#include "include/templateUtils.h"
#include "include/threadPool.h"

void test_1() {
  ThreadPool threadPool;
  threadPool.setMode(ThreadPool::PoolMode::MODE_FIXED);
  threadPool.start(2);

  std::future<int> result1 =
      threadPool.submitTask([](int a, int b) { return a + b; }, 1, 2);
  std::future<int> result2 =
      threadPool.submitTask([](int a, int b) { return a + b; }, 1, 100);

  std::cout << result1.get() << '\n';
  std::cout << result2.get() << '\n';
}

void test_2() {
    auto task1 = [](int a, int b) { return a + b; };
    std::cout << task1(1, 2) << '\n';
    std::cout << task1(1, 100) << '\n';
}

int main() {
  (void)measureTime(test_1);
  (void)measureTime(test_2);

  return 0;
}