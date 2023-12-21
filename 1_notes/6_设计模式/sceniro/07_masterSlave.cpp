#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> tasks; // 任务队列
std::mutex mtx; // 互斥锁,用于保护任务队列
std::condition_variable cv; // 条件变量,用于线程间的通信

// 从线程函数
void workerThread(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待任务队列非空
        cv.wait(lock, [] { return !tasks.empty(); });

        // 取出任务
        int task = tasks.front();
        tasks.pop();

        // 执行任务
        std::cout << "Worker " << id << " processing task: " << task << std::endl;

        // 模拟任务执行时间
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // 返回结果给主线程
        std::cout << "Worker " << id << " finished task: " << task << std::endl;
    }
}

int main() {
    // 创建从线程
    std::thread workers[3];
    for (int i = 0; i < 3; i++) {
        workers[i] = std::thread(workerThread, i);
    }

    // 添加任务到任务队列
    for (int i = 0; i < 10; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(i);
        cv.notify_one(); // 通知从线程有新任务
    }

    // 等待从线程完成任务
    for (int i = 0; i < 3; i++) {
        workers[i].join();
    }

    return 0;
}
