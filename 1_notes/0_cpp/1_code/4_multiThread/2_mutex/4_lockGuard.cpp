#include <iostream>
#include <mutex>
#include <thread>

//   在C++中,`std::lock_guard` 和 `std::unique_lock` 的构造函数可以接受一个名为
//   `std::lock_policy` 的参数,这个参数可以是以下三种之一:

// 这三种策略提供了更灵活的锁定机制,可以根据具体的需求来选择使用.

std::mutex mtx; // mutex for critical section

void print_thread_id(int id) {
  mtx.lock();

  std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);
  std::cout << "thread #" << id << '\n';
}

int main() {
  std::thread threads[10];
  // spawn 10 threads:
  for (int i = 0; i < 10; ++i)
    threads[i] = std::thread(print_thread_id, i + 1);

  for (auto &th : threads)
    th.join();

  return 0;
}

/*
1. `std::lock_guard`的用途：

   `std::lock_guard`是一个简单的RAII包装器，用于管理互斥锁的生命周期。
   当你创建一个`std::lock_guard`对象时，它会自动获取互斥锁。
   当`std::lock_guard`对象离开作用域时，它的析构函数会自动释放互斥锁。
   这样可以确保在发生异常或提前返回时，互斥锁总是被正确地释放。

2. `std::lock_guard`能接受的模板参数：

   `std::lock_guard`是一个模板类，它的模板参数是一个互斥锁类型。
   这个类型需要满足BasicLockable的要求，也就是说，它需要提供`lock()`和`unlock()`两个成员函数。
   例如，`std::mutex`、`std::recursive_mutex`、`std::timed_mutex`和`std::recursive_timed_mutex`都可以作为`std::lock_guard`的模板参数。

3. `std::lock_guard`的std::lock_policy有啥用？有哪些std::lock_policy？

 - `std::adopt_lock`:
    表示互斥量已经被锁定,不需要再尝试锁定.
 - `std::defer_lock`:
    表示不立即锁定互斥量,
    稍后可以手动调用 `lock()` 方法来锁定.
 - `std::try_to_lock`:
    尝试锁定互斥量,如果互斥量已经被锁定,则立即返回,不会阻塞.

*/