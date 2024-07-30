#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
public:
  ThreadPool(size_t threadNum = 8) : mPool(std::make_shared<Pool>()) {
    assert(threadNum > 0);
    try {
      for (size_t i = 0; i < threadNum; i++) {
        std::thread([pool = mPool] {
          std::unique_lock<std::mutex> locker(pool->mtx);
          locker.unlock();
          while (!pool->close) {
            locker.lock(); // 获得锁才能往下执行
            if (!pool->tasks.empty()) {
              auto task = pool->tasks.front(); // 从任务队列取任务执行
              pool->tasks.pop();
              locker
                  .unlock(); // 取完解锁，让池接收新任务，或者让其他线程处理其他任务
              task();        // 执行任务
            } else {
              pool->cond.wait(locker); // 无任务，等待，通过竞争锁被唤醒
            }
          }
        }).detach();
      }
    } catch (...) {
      {
        std::lock_guard<std::mutex> locker(mPool->mtx);
        mPool->close = true; // closed = true，关闭所有线程
      }
      mPool->cond.notify_all(); // 唤醒所有线程，执行关闭
      throw std::runtime_error("ThreadPool Init Failed!");
    }
  }

  // 往线程池任务队列添加任务
  template <typename Func> void addTask(Func &&task) {
    {
      std::lock_guard<std::mutex> lg(mPool->mtx);
      mPool->tasks.emplace(std::forward<Func>(task)); // forward完美转发右值引用
    }
    mPool->cond.notify_one();
  }

  ~ThreadPool() {
    if (mPool != nullptr) {
      {
        std::lock_guard<std::mutex> lg(mPool->mtx);
        mPool->close = true;
      }
      mPool->cond.notify_all();
    }
  }

  ThreadPool(const ThreadPool &) = delete;
  ThreadPool &operator=(const ThreadPool &) = delete;

private:
  struct Pool {
    std::queue<std::function<void()>> tasks; // 任务队列
    std::mutex mtx;
    std::condition_variable cond;
    bool close = false;
  };

  std::shared_ptr<Pool> mPool;
};
