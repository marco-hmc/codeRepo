#include "../include/threadPool.h"
#include <memory>
#include <mutex>

void Thread::start() {
  std::thread t(func_, threadId_);
  t.detach();
}

int Thread::getId() const { return threadId_; }

///////////////////////////////////////////////////////
ThreadPool::ThreadPool() {}
ThreadPool::~ThreadPool() {
  isPoolRunning_ = false;
  std::unique_lock<std::mutex> lock(taskQueMtx_);
  notEmpty_.notify_all();
  exitCond_.wait(lock, [&]() -> bool { return threads_.size() == 0; });
}

void ThreadPool::setMode(PoolMode mode) {}

void ThreadPool::start(int initThreadSize) {
  isPoolRunning_ = true;
  for (int i = 0; i < initThreadSize; ++i) {
    auto ptr = std::make_unique<Thread>(
        std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
    int threadId = ptr->getId();
    threads_.emplace(threadId, std::move(ptr));
  }

  for (int i = 0; i < initThreadSize; ++i) {
    threads_[i]->start();
    idleThreadSize_++;
  }
}

void ThreadPool::threadFunc(int threadId) {}

bool ThreadPool::checkRunningState() const { return false; }