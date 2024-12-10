#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

/*
    1. wait_for怎么用？和wait相比的区别是什么？
        - wait_for的概念：
            `std::condition_variable`的`wait_for`函数用于等待条件变量的通知，但是可以设置一个超时时间。
        - 区别：
            `std::condition_variable`的`wait_for`函数和`wait`函数的区别在于，`wait_for`函数可以设置一个超时时间，如果超时时间到了，那么`wait_for`函数会返回。
        - 使用：
            先上锁，然后调用`wait_for`函数，`wait_for`函数会解锁互斥锁，然后等待条件变量的通知，如果超时时间到了，那么`wait_for`函数会返回。
*/

std::condition_variable cv;
std::mutex cv_m;
int i;

void waits(int idx) {
    std::unique_lock<std::mutex> lk(cv_m);
    if (cv.wait_for(lk, idx * std::chrono::milliseconds(100),
                    [] { return i == 1; })) {
        std::cerr << "Thread " << idx << " finished waiting. i == " << i
                  << '\n';
    } else {
        std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
    }
}

void signals() {
    std::this_thread::sleep_for(std::chrono::milliseconds(120));
    std::cerr << "Notifying...\n";
    cv.notify_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
    }
    std::cerr << "Notifying again...\n";
    cv.notify_all();
}

int main() {
    std::thread t1(waits, 1);
    std::thread t2(waits, 2);
    std::thread t3(waits, 3);
    std::thread t4(signals);
    t1.join(), t2.join(), t3.join(), t4.join();
    return 0;
}
