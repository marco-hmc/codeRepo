#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

/*
  1. wait的概念是什么？有什么陷阱？
     - wait的概念：
         `std::condition_variable`的`wait`函数用于等待条件变量的通知。
     - 陷阱：
         `std::condition_variable`的`wait`函数需要传入一个`std::unique_lock`对象，这个对象会在`wait`函数内部解锁互斥锁，然后等待条件变量的通知。
         但是，如果在`wait`函数内部等待的过程中，有其他线程修改了条件变量，那么`wait`函数会返回，但是这个时候条件可能已经不满足了。
         所以，`wait`函数需要和`std::unique_lock`一起使用，用于在等待条件变量的过程中解锁互斥锁，等到条件满足后再重新加锁。
     - 使用：
        先上锁，然后调用`wait`函数，`wait`函数会解锁互斥锁，然后等待条件变量的通知，当条件满足时，`wait`函数会重新加锁，然后返回。
*/

std::condition_variable cv;
std::mutex cv_m;
int i = 0;

void waits() {
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, [] { return i == 1; });
    std::cerr << "...finished waiting. i == 1\n";
}

void signals() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}

int main() {
    std::thread t1(waits);
    std::thread t2(waits);
    std::thread t3(waits);
    std::thread t4(signals);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
