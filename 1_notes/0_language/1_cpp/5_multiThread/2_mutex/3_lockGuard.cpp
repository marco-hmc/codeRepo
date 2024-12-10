#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/*
1. `std::lock_guard`的用途：
   `std::lock_guard`是一个简单的RAII包装器，用于管理互斥锁的生命周期。

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

std::mutex mtx;

void print_thread_id(int id) {
    mtx.lock();
    std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);
    std::cout << "thread #" << id << '\n';
}

int main() {
    std::vector<std::thread> threads;
    threads.reserve(10);
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(print_thread_id, i + 1);
    }

    for (auto &th : threads) {
        th.join();
    }

    return 0;
}
