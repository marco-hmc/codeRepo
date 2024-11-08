#include <future>
#include <iostream>

int factorial(int N) {
  int res = 1;
  for (int i = N; i > 1; i--)
    res *= i;
  std::cout << "Result is: " << res << '\n';

  return res;
}

void test_1() {
  int x;
  std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
  x = fu.get(); // get()函数会等待子线程结束,然后将返回值传给x.并且future对象只能被调用一次
}

int main() {
  test_1();
  return 0;
}
/*
  1. std::async
    是一个函数模板，它可以启动一个异步任务，并返回一个std::future对象。
    这个std::future对象可以用于获取异步任务的结果。

  2. std::future
    是一个类模板，它表示一个异步操作的结果。你可以调用std::future::get来获取异步操作的结果。
    如果异步操作还没有完成，std::future::get会阻塞，直到异步操作完成。

  3. std::future的设计意图是什么？
    可以看成是线程之间的通信。
    1. 如果要从子线程获取变量到主线程,可以通过互斥锁和状态变量的形式。
        若子线程计算完毕则notify_all,唤醒主进程
    2. 还可以通过future实现.
*/