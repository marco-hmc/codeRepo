#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> messageQueue;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟生产消息的耗时操作

        std::lock_guard<std::mutex> lock(mtx);
        messageQueue.push(i);
        std::cout << "Producer: Produced message " << i << std::endl;

        cv.notify_one(); // 通知消费者线程有新消息可用
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !messageQueue.empty(); }); // 等待直到有消息可用

        int message = messageQueue.front();
        messageQueue.pop();
        std::cout << "Consumer: Consumed message " << message << std::endl;

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 模拟消费消息的耗时操作
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
