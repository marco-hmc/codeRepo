#include <iostream>
#include <thread>

// 定义一个全局的 thread_local 变量
thread_local int threadId;

void printThreadId() {
  // 打印当前线程的 ID
  std::cout << "Thread ID: " << threadId << std::endl;
}

int main() {
  // 创建两个线程
  std::thread t1([]() {
    // 在线程函数中设置 threadId 的值
    threadId = 1;
    printThreadId();
  });

  std::thread t2([]() {
    // 在线程函数中设置 threadId 的值
    threadId = 2;
    printThreadId();
  });

  // 等待两个线程执行完毕
  t1.join();
  t2.join();

  return 0;
}