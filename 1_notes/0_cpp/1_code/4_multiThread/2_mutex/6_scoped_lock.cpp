#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void printMessage(const std::string &message) {
  std::scoped_lock lock(mtx); // 创建scoped_lock对象并锁定互斥量
  for (int i = 0; i < 5; ++i) {
    std::cout << message << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  // 作用域结束时，scoped_lock对象自动释放互斥量
}

int main() {
  std::thread t1(printMessage, "Hello");
  std::thread t2(printMessage, "World");

  t1.join();
  t2.join();

  return 0;
}