#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/*
  1. `std::unique_lock`和`std::lock_guard`的区别：
    * `std::lock_guard`在构造时自动锁定互斥锁，在析构时自动解锁互斥锁，但是在其生命周期内不能改变锁的状态。
    * `std::unique_lock`在构造时可以选择是否锁定互斥锁，可以在其生命周期内多次锁定和解锁互斥锁，还可以转移所有权。

  void task_with_lock_guard() {
      std::lock_guard<std::mutex> guard1(foo); // 必须在构造时传入互斥锁
      std::lock_guard<std::mutex> guard2(bar); // 必须在构造时传入互斥锁
      std::cout << "task with lock_guard\n";
  }

  2. `std::unique_lock`相较于`std::lock_guard`的额外功能：
    - 延迟锁定：
          `std::unique_lock`可以在构造时不锁定互斥锁，然后在需要的时候再锁定互斥锁。
    - 手动锁定和解锁：
          `std::unique_lock`可以在其生命周期内多次锁定和解锁互斥锁。
    - 锁所有权的转移：
          `std::unique_lock`可以将锁的所有权转移给另一个`std::unique_lock`对象。
    - 条件变量：
          `std::unique_lock`可以和`std::condition_variable`一起使用，用于等待条件或者通知条件。

*/

namespace identifier1 {
    std::mutex foo, bar;

    void task_a() {
        std::lock(foo, bar);  // simultaneous lock (prevents deadlock)
        std::unique_lock<std::mutex> lck1(foo, std::adopt_lock);
        std::unique_lock<std::mutex> lck2(bar, std::adopt_lock);
        std::cout << "task a\n";
    }

    void task_b() {
        std::unique_lock<std::mutex> lck1;
        std::unique_lock<std::mutex> lck2;
        lck1 = std::unique_lock<std::mutex>(bar, std::defer_lock);
        lck2 = std::unique_lock<std::mutex>(foo, std::defer_lock);
        std::lock(lck1, lck2);  // simultaneous lock (prevents deadlock)
        std::cout << "task b\n";
    }

    void test_1() {
        std::thread th1(task_a);
        std::thread th2(task_b);

        th1.join();
        th2.join();
    }
}  // namespace identifier1

int main() {
    identifier1::test_1();
    return 0;
}
