#include <omp.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <random>
#include <thread>
#include <vector>

// 判断是否为目标值
bool isTarget(int n) { return n == 100; }

// 单线程版本
void findIfSingleThread(const std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::find_if(data.begin(), data.end(), isTarget);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (result != data.end()) {
        std::cout << "Single-threaded: Found 100 at index "
                  << std::distance(data.begin(), result) << " in "
                  << duration.count() << " seconds.\n";
    } else {
        std::cout << "Single-threaded: 100 not found in " << duration.count()
                  << " seconds.\n";
    }
}

// OpenMP 版本
void findIfOpenMP(const std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    int result = -1;
    bool found = false;

#pragma omp parallel for shared(found)
    for (size_t i = 0; i < data.size(); ++i) {
        if (!found && isTarget(data[i])) {
#pragma omp critical
            {
                if (!found) {
                    result = i;
                    found = true;
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (found) {
        std::cout << "OpenMP: Found 100 at index " << result << " in "
                  << duration.count() << " seconds.\n";
    } else {
        std::cout << "OpenMP: 100 not found in " << duration.count()
                  << " seconds.\n";
    }
}

// 线程池类
class ThreadPool {
   public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    size_t workersCount() const { return workers.size(); }

   private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    this->condition.wait(lock, [this] {
                        return this->stop || !this->tasks.empty();
                    });
                    if (this->stop && this->tasks.empty()) return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers) worker.join();
}

template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
    using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<returnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<returnType> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// 线程池版本
void findIfThreadPool(const std::vector<int>& data, ThreadPool& pool) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<int>> futures;
    std::atomic<bool> found(false);
    std::atomic<int> result(-1);

    size_t chunkSize = data.size() / pool.workersCount();
    for (size_t i = 0; i < data.size(); i += chunkSize) {
        futures.emplace_back(pool.enqueue([&, i, chunkSize] {
            for (size_t j = i; j < i + chunkSize && j < data.size(); ++j) {
                if (!found && isTarget(data[j])) {
                    result = j;
                    found = true;
                    break;
                }
            }
            return result.load();
        }));
    }

    for (auto& future : futures) {
        future.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (found) {
        std::cout << "ThreadPool: Found 100 at index " << result << " in "
                  << duration.count() << " seconds.\n";
    } else {
        std::cout << "ThreadPool: 100 not found in " << duration.count()
                  << " seconds.\n";
    }
}

int main() {
    const int dataSize = 1'000'000;
    std::vector<int> data(dataSize);
    std::iota(data.begin(), data.end(),
              0);  // Fill with 0, 1, 2, ..., dataSize-1

    // 随机打乱数据
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    findIfSingleThread(data);
    findIfOpenMP(data);

    ThreadPool pool(std::thread::hardware_concurrency());
    findIfThreadPool(data, pool);

    return 0;
}