#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <utility>

const int TASK_MAX_THRESHOLD = 2;  // INT32_MAX;
const int THREAD_MAX_THRESHOLD = 1024;
const int THREAD_MAX_IDLE_TIME = 60;  // 单位:秒

class Thread {
   public:
    using ThreadFunc = std::function<void(int)>;

    explicit Thread(ThreadFunc func)
        : m_func(std::move(func)), m_threadId(m_generateId++) {}
    ~Thread() = default;

    Thread(const Thread &) = delete;
    Thread(Thread &&) = delete;
    Thread &operator=(const Thread &) = delete;
    Thread &operator=(Thread &&) = delete;

    void start();
    int getId() const;

   private:
    ThreadFunc m_func;
    static int m_generateId;
    int m_threadId;
};

int Thread::m_generateId = 0;

inline void Thread::start() {
    std::thread([this]() { m_func(m_threadId); }).detach();
}

inline int Thread::getId() const { return m_threadId; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadPool {
   public:
    enum class PoolMode {
        MODE_FIXED,
        MODE_CACHED,
    };

   public:
    ThreadPool() = default;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    ~ThreadPool();

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    bool checkRunningState() const;
    void setMode(PoolMode mode);
    void setTaskQueMaxThreshHold(int threshold);
    void setThreadSizeThreshHold(int threshold);

    template <typename Func, typename... Args>
    auto submitTask(Func &&func, Args &&...args)
        -> std::future<decltype(func(args...))>;

    void start(
        unsigned int initThreadSize = std::thread::hardware_concurrency());

   private:
    void threadFunc(int threadid);

   private:
    std::unordered_map<int, std::unique_ptr<Thread>> m_threads;

    unsigned int m_initThreadSize = 0;
    int m_threadSizeThreshHold = THREAD_MAX_THRESHOLD;
    std::atomic_int m_curThreadSize = 0;
    std::atomic_int m_idleThreadSize = 0;

    using Task = std::function<void()>;
    std::queue<Task> m_taskQue;
    std::atomic_int m_taskSize = 0;
    int m_taskQueueMaxThreshHold = TASK_MAX_THRESHOLD;

    std::mutex m_taskQueMtx;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    std::condition_variable m_exitCond;

    PoolMode m_mode = PoolMode::MODE_FIXED;
    std::atomic_bool m_running = false;
};

inline ThreadPool::~ThreadPool() {
    m_running = false;  // what if m_running is true?

    // for (auto &thread : m_threads) {
    //   thread.second->start();
    // }

    std::unique_lock<std::mutex> lock(m_taskQueMtx);
    m_notEmpty.notify_all();
    m_exitCond.wait(lock, [this]() { return m_threads.empty(); });
}

inline bool ThreadPool::checkRunningState() const { return m_running; }

inline void ThreadPool::setMode(PoolMode mode) {
    if (checkRunningState()) {
        throw std::runtime_error("Can't set mode when thread pool is running");
    }
    m_mode = mode;
}

inline void ThreadPool::setTaskQueMaxThreshHold(int threshold) {
    if (checkRunningState()) {
        throw std::runtime_error(
            "Can't set task queue max threshold when thread pool is running");
    }
    m_taskQueueMaxThreshHold = threshold;
}

inline void ThreadPool::setThreadSizeThreshHold(int threshold) {
    if (checkRunningState()) {
        throw std::runtime_error(
            "Can't set thread size threshold when thread pool is running");
    }
    m_threadSizeThreshHold = threshold;
}

template <typename Func, typename... Args>
auto ThreadPool::submitTask(Func &&func, Args &&...args)
    -> std::future<decltype(func(args...))> {
    using ReturnType = decltype(func(args...));

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<ReturnType> future = task->get_future();

    if (m_taskSize >= m_taskQueueMaxThreshHold) {
        throw std::runtime_error("Task queue is full");
    }

    m_taskQue.push([task]() { (*task)(); });
    ++m_taskSize;

    m_notEmpty.notify_one();

    return future;
}

inline void ThreadPool::start(unsigned int initThreadSize) {
    if (checkRunningState()) {
        throw std::runtime_error("Thread pool is already running");
    }

    m_running = true;
    m_initThreadSize = initThreadSize;

    for (int i = 0; i < m_initThreadSize; ++i) {
        m_threads[i] = std::make_unique<Thread>(
            [this](int threadid) { this->threadFunc(threadid); });
        m_threads[i]->start();
    }
}

inline void ThreadPool::threadFunc(int threadid) {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(m_taskQueMtx);

            while (m_taskQue.empty()) {
                if (!m_running) {
                    m_threads.erase(threadid);
                    m_exitCond.notify_one();
                    return;
                }
                m_notEmpty.wait(lock);
            }

            m_idleThreadSize--;
            task = std::move(m_taskQue.front());
            m_taskQue.pop();
            --m_taskSize;

            if (!m_taskQue.empty()) {
                m_notEmpty.notify_all();
            }

            m_notFull.notify_all();
        }

        if (task) {
            task();
        }
        m_idleThreadSize++;
    }
}