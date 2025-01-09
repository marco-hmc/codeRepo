#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/*

    1. mutex是什么？
        互斥锁（mutex）是一种用于保护共享资源的同步机制。当一个线程需要访问共享资源时，它需要先获取互斥锁，然后才能访问这个资源。
        当线程访问完共享资源后，它需要释放互斥锁，以便其他线程可以访问这个资源。
        互斥锁可以防止多个线程同时访问共享资源，从而避免数据竞争和其他并发问题。
    
    2. std::mutex怎么用？
        * 构造函数
            `std::mutex`是一个类，它的构造函数没有形参，用于创建一个互斥锁对象。
        * 主要成员函数
            - `lock()`: 用于获取互斥锁。如果当前没有其他线程持有这个锁，那么这个函数会立即获取锁并返回。
                如果锁已经被其他线程持有，那么这个函数会阻塞当前线程，直到锁变得可用。
            - `unlock()`: 用于释放互斥锁。如果当前线程持有这个锁，那么这个函数会释放锁。
                如果当前线程没有持有这个锁，那么这个函数的行为是未定义的。
        * 其他成员函数
            - `try_lock()`: 尝试获取互斥锁。如果互斥锁当前没有被其他线程持有，那么这个函数会立即获取锁并返回`true`。
                如果互斥锁已经被其他线程持有，那么这个函数不会阻塞，而是立即返回`false`。

*/

namespace identifier_lock {
    std::mutex mtx;

    void critical_section(int id) {
        mtx.lock();
        std::cout << "Thread " << id << " entered critical section."
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Thread " << id << " leaving critical section."
                  << std::endl;
        mtx.unlock();
    }

    void run() {
        std::thread t1(critical_section, 1);
        std::thread t2(critical_section, 2);

        t1.join();
        t2.join();
    }
}  // namespace identifier_lock

int main() {
    identifier_lock::run();
    return 0;
}
