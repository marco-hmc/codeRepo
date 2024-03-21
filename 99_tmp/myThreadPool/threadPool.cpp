#include <atomic>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

using Task = std::function<void(int)>;

class MyThread {
public:
  MyThread() {}
  ~MyThread() {}
  void start() {}
  int getId() const { return id_; }

private:
  Task func_;
  int id_;
};

class MyThreadPool {
public:
  MyThreadPool() {}
  void start(int num) {}

  template <typename Func, typename... Args>
  auto submitTask(Func &&func, Args &&...args)
      -> std::future<decltype(func(args...))> {
    using RType = decltype(func(args...));

    auto task = std::make_shared<std::packaged_task<RType>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<RType> future = task->get_future();

    std::unique_lock<std::mutex> lock(taskQueMtx_);
    if (!notFull_.wait_for(lock, std::chrono::seconds(1), [&]() -> bool {
          return tasks_.size() < (size_t)taskQueMaxThreshHold_;
        })) {
      std::cerr << "task queue is full, submit task fail." << std::endl;
      auto task = std::make_shared<std::packaged_task<RType()>>(
          []() -> RType { return RType(); });
      (*task)();
      return task->get_future();
    }
  }

private:
  std::unordered_map<int, std::unique_ptr<MyThread>> threads_;
  int initThreadSize_;
  int threadMaximumSize_;
  std::atomic_int curThreadSize_;
  std::atomic_int idleThreadSize_;

  std::queue<Task> tasks_;
  std::mutex taskQueMtx_;
  // std::atomic_int taskSize_;
};

int main() {}