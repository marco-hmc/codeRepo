#include <iostream>
#include <thread>

void task1() { std::cout << "Executing Task 1" << std::endl; }

void task2() { std::cout << "Executing Task 2" << std::endl; }

int main() {
  std::thread t1(task1);

  // 在运行时决定执行哪个任务
  if (false) {
    std::thread t2 = std::move(t1); // 将线程控制权从 t1 转移到 t2
                                    // std::thread t2 = t1; // 编译错误
    t2.join();
  } else {
    t1 = std::thread(task2); // 重新赋值,接管新线程的控制权
    t1.join();
  }

  return 0;
}