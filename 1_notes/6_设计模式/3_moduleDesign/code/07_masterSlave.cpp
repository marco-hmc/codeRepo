#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

std::queue<int> tasks;
std::mutex mtx;
std::condition_variable cv;

void workerThread(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !tasks.empty(); });

        int task = tasks.front();
        tasks.pop();
        std::cout << "Worker " << id << " processing task: " << task << '\n';
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Worker " << id << " finished task: " << task << '\n';
    }
}

int main() {
    std::vector<std::thread> workers;
    workers.reserve(3);
    for (int i = 0; i < 3; ++i) {
        workers.emplace_back(workerThread, i);
    }

    for (int i = 0; i < 10; ++i) {
        {
            std::scoped_lock lock(mtx);
            tasks.push(i);
        }
        cv.notify_one();
    }

    for (auto& worker : workers) {
        worker.join();
    }

    return 0;
}