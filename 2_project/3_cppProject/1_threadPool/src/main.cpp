// 线程池项目-最终版.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using namespace std;

#include "../include/threadPool.h"

int sum1(int a, int b) {
  this_thread::sleep_for(chrono::seconds(2));
  return a + b;
}
int sum2(int a, int b, int c) {
  this_thread::sleep_for(chrono::seconds(2));
  return a + b + c;
}
void io_thread(int listenfd) {}
void worker_thread(int clientfd) {}
int main() {
  ThreadPool pool;
  // pool.setMode(PoolMode::MODE_CACHED);
  pool.start(2);

  future<int> r1 = pool.submitTask(sum1, 1, 2);
  future<int> r2 = pool.submitTask(sum2, 1, 2, 3);
  future<int> r3 = pool.submitTask(
      [](int b, int e) -> int {
        int sum = 0;
        for (int i = b; i <= e; i++)
          sum += i;
        return sum;
      },
      1, 100);
  future<int> r4 = pool.submitTask(
      [](int b, int e) -> int {
        int sum = 0;
        for (int i = b; i <= e; i++)
          sum += i;
        return sum;
      },
      1, 100);
  future<int> r5 = pool.submitTask(
      [](int b, int e) -> int {
        int sum = 0;
        for (int i = b; i <= e; i++)
          sum += i;
        return sum;
      },
      1, 100);

  cout << r1.get() << endl;
  cout << r2.get() << endl;
  cout << r3.get() << endl;
  cout << r4.get() << endl;
  cout << r5.get() << endl;
}