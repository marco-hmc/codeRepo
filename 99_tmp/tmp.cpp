#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int shared_data = 0;

void thread_safe_function() {
    std::lock_guard<std::mutex> lock(mtx);
    shared_data++;
    std::cout << "Thread-safe function: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟长时间操作
}

void reentrant_function() {
    std::lock_guard<std::mutex> lock(mtx);
    shared_data++;
    std::cout << "Reentrant function: " << shared_data << std::endl;
}

int main() {
    std::thread t1(thread_safe_function);
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 确保 t1 持有锁
    std::thread t2(reentrant_function);

    t1.join();
    t2.join();

    return 0;
}