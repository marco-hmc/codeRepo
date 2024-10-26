std::mutex mtx;
std::condition_variable cond;
std::deque<int> queue;

int dequeue() {
    std::unique_lock<std::mutex> lock(mtx);
    cond.wait(lock,
              [] { return !queue.empty(); });  // 使用 lambda 表达式检查条件
    int top = queue.front();
    queue.pop_front();
    return top;
}

int dequeue2() {
    // queue pop掉最后一个,并返回
    MutexLockGuard lock(mutex);
    while (queue.empty()) {  // 不能用if,必须用while,避免虚假唤醒
        cond.wait();
    }
    int top = queue.front();
    queue.pop_front();
    return top;
}

  int dequeue3() {
      // queue pop掉最后一个,并返回
      MutexLockGuard lock(mutex);
      while (queue.empty()) {  // 不能用if,必须用while,避免虚假唤醒
          cond.wait();
      }
      int top = queue.front();
      queue.pop_front();
      return top;
  }