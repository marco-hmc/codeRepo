// constructing lock_guard with adopt_lock
#include <iostream> // std::cout
#include <mutex>    // std::mutex, std::lock_guard, std::adopt_lock
#include <thread>   // std::thread

//   在C++中,`std::lock_guard` 和 `std::unique_lock` 的构造函数可以接受一个名为
//   `std::lock_policy` 的参数,这个参数可以是以下三种之一:

// 1. `std::adopt_lock`:表示互斥量已经被锁定,不需要再尝试锁定.
// 2. `std::defer_lock`:表示不立即锁定互斥量,稍后可以手动调用 `lock()`
// 方法来锁定.
// 3.
// `std::try_to_lock`:尝试锁定互斥量,如果互斥量已经被锁定,则立即返回,不会阻塞.

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
