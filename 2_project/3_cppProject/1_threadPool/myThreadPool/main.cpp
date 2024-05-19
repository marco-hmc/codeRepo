#include "include/threadPool.h"
#include <future>
#include <iostream>

void test_1() {
  ThreadPool threadPool;
  threadPool.setMode(PoolMode::MODE_FIXED);
  threadPool.start(2);

  std::future<int> result1 =
      threadPool.submitTask([](int a, int b) { return a + b; }, 1, 2);
  std::future<int> result2 =
      threadPool.submitTask([](int a, int b) { return a + b; }, 1, 100);

  std::cout << result1.get() << std::endl;
  std::cout << result2.get() << std::endl;
}

int main() {
  test_1();
  return 0;
}