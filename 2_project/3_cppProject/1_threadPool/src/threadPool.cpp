#include "../include/threadPool.h"

#include <memory>
#include <mutex>
#include <thread>

Thread::Thread(ThreadFunc func) : func_(func), threadId_(generateId_++) {}

void Thread::start() {
  std::thread t(func_, threadId_);
  t.detach();
}

int Thread::getId() const { return threadId_; }

//////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool()
    : initThreadSize_(0), taskSize_(0), idleThreadSize_(0), curThreadSize_(0),
      taskQueMaxThreshHold_(TASK_MAX_THRESHOLD),
      threadSizeThreshHold_(THREAD_MAX_THRESHOLD),
      poolMode_(PoolMode::MODE_FIXED), isPoolRunning_(false) {}

ThreadPool::~ThreadPool() {
  isPoolRunning_ = false;

  // 等待线程池里面所有的线程返回
  // 有两种状态: 阻塞/ 正在执行任务中
  std::unique_lock<std::mutex> lock(taskQueMtx_);
  notEmpty_.notify_all();
  exitCond_.wait(lock, [&]() -> bool { return threads_.size() == 0; });
}

void ThreadPool::setMode(PoolMode mode) {
  if (checkRunningState())
    return;
  poolMode_ = mode;
}

void ThreadPool::setTaskQueMaxThreshHold(int threshold) {
  if (checkRunningState())
    return;
  taskQueMaxThreshHold_ = threshold;
}

void ThreadPool::setThreadSizeThreshHold(int threshold) {
  if (checkRunningState())
    return;
  if (poolMode_ == PoolMode::MODE_CACHED) {
    threadSizeThreshHold_ = threshold;
  }
}

void ThreadPool::start(int initThreadSize) {
  isPoolRunning_ = true;

  initThreadSize_ = initThreadSize;
  curThreadSize_ = initThreadSize;

  for (int i = 0; i < initThreadSize_; i++) {
    auto ptr = std::make_unique<Thread>(
        std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
    int threadId = ptr->getId();
    threads_.emplace(threadId, std::move(ptr));
  }

  for (int i = 0; i < initThreadSize_; i++) {
    threads_[i]->start();
    idleThreadSize_++;
  }
}

void ThreadPool::threadFunc(int threadid) {
  auto lastTime = std::chrono::high_resolution_clock().now();

  for (;;) {
    Task task;
    {
      std::unique_lock<std::mutex> lock(taskQueMtx_);

      std::cout << "tid:" << std::this_thread::get_id() << "尝试获取任务..."
                << std::endl;

      while (taskQue_.size() == 0) {
        if (!isPoolRunning_) {
          threads_.erase(threadid); // std::this_thread::getid()
          std::cout << "threadid:" << std::this_thread::get_id() << " exit!"
                    << std::endl;
          exitCond_.notify_all();
          return;
        }

        if (poolMode_ == PoolMode::MODE_CACHED) {

          if (std::cv_status::timeout ==
              notEmpty_.wait_for(lock, std::chrono::seconds(1))) {
            auto now = std::chrono::high_resolution_clock().now();
            auto dur = std::chrono::duration_cast<std::chrono::seconds>(
                now - lastTime);
            if (dur.count() >= THREAD_MAX_IDLE_TIME &&
                curThreadSize_ > initThreadSize_) {

              threads_.erase(threadid);
              curThreadSize_--;
              idleThreadSize_--;

              std::cout << "threadid:" << std::this_thread::get_id() << " exit!"
                        << std::endl;
              return;
            }
          }
        } else {

          notEmpty_.wait(lock);
        }
      }

      idleThreadSize_--;

      std::cout << "tid:" << std::this_thread::get_id() << "获取任务成功..."
                << std::endl;

      task = taskQue_.front();
      taskQue_.pop();
      taskSize_--;

      if (taskQue_.size() > 0) {
        notEmpty_.notify_all();
      }

      notFull_.notify_all();
    }

    if (task) {
      task();
    }

    idleThreadSize_++;
    lastTime = std::chrono::high_resolution_clock().now();
  }
}

bool ThreadPool::checkRunningState() const { return isPoolRunning_; }