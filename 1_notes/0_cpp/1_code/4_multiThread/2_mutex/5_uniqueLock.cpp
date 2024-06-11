// unique_lock constructor example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock, std::unique_lock
                                     // std::adopt_lock, std::defer_lock

// `std::unique_lock`是C++标准库中的一个类模板,用于实现互斥锁的管理和控制.它提供了一种更灵活的方式来管理互斥锁,相比于`std::lock_guard`,`std::unique_lock`提供了更多的功能和选项.

// 除了基本的锁定和释放功能,`std::unique_lock`还提供了以下特性:

// 1.
// **延迟锁定和手动解锁**:与`std::lock_guard`不同,`std::unique_lock`可以在构造时选择是否立即锁定互斥锁,以及在需要时手动解锁.这使得在某些情况下可以更灵活地控制锁的范围和持有时间.

// 2.
// **可转移的所有权**:`std::unique_lock`的所有权可以在不同的线程之间转移.这意味着可以将一个`std::unique_lock`对象传递给另一个线程,从而实现线程间的互斥锁传递.

// 3.
// **条件变量支持**:`std::unique_lock`提供了与条件变量一起使用的支持.它可以与`std::condition_variable`一起使用,以实现线程间的同步和通信.

// 下面是一个使用`std::unique_lock`的简单示例:

std::mutex foo, bar;
void task_a () {
 std::lock (foo,bar);         // simultaneous lock (prevents deadlock)
 std::unique_lock<std::mutex> lck1 (foo,std::adopt_lock);
 std::unique_lock<std::mutex> lck2 (bar,std::adopt_lock);
 std::cout << "task a\n";
 // (unlocked automatically on destruction of lck1 and lck2)
}

void task_b () {
 // foo.lock(); bar.lock(); // replaced by:
 std::unique_lock<std::mutex> lck1, lck2;
 lck1 = std::unique_lock<std::mutex>(bar,std::defer_lock);
 lck2 = std::unique_lock<std::mutex>(foo,std::defer_lock);
 std::lock (lck1,lck2);       // simultaneous lock (prevents deadlock)
 std::cout << "task b\n";
 // (unlocked automatically on destruction of lck1 and lck2)
}

int main ()
{
 std::thread th1 (task_a);
 std::thread th2 (task_b);

 th1.join();
 th2.join();

 return 0;
}

/*
1. `std::unique_lock`和`std::lock_guard`的区别：

   `std::unique_lock`和`std::lock_guard`都是RAII风格的锁，用于管理互斥锁的生命周期。但是，`std::unique_lock`比`std::lock_guard`更灵活。

   `std::lock_guard`在构造时自动锁定互斥锁，在析构时自动解锁互斥锁，但是在其生命周期内不能改变锁的状态。这使得`std::lock_guard`简单易用，但是不够灵活。

   `std::unique_lock`在构造时可以选择是否锁定互斥锁，可以在其生命周期内多次锁定和解锁互斥锁，还可以转移所有权。这使得`std::unique_lock`更灵活，但是使用起来需要更多的注意。

2. `std::unique_lock`的额外功能：

   - 延迟锁定：
        `std::unique_lock`可以在构造时不锁定互斥锁，然后在需要的时候再锁定互斥锁。
   - 手动锁定和解锁：
        `std::unique_lock`可以在其生命周期内多次锁定和解锁互斥锁。
   - 锁所有权的转移：
        `std::unique_lock`可以将锁的所有权转移给另一个`std::unique_lock`对象。
   - 条件变量：
        `std::unique_lock`可以和`std::condition_variable`一起使用，用于等待条件或者通知条件。
*/