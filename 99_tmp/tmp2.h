#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// 下载任务类型
using DownloadTask = std::function<bool()>;
using TaskWithPriority = std::pair<int, DownloadTask>;

// 比较函数，用于优先队列
struct CompareTask {
    bool operator()(const TaskWithPriority& lhs, const TaskWithPriority& rhs) {
        // 优先级高的任务优先
        return lhs.first < rhs.first;
    }
};

// 下载管理器类
class DownloadManager {
   public:
    DownloadManager();
    ~DownloadManager();

    std::future<bool> addDownloadTaskWithFuture(const std::string& uuid,
                                                int priority);
    void addDownloadTaskWithCallback(const std::string& uuid, int priority,
                                     std::function<void(bool)> callback);
    void addDownloadTask(const std::string& uuid, int priority);

   private:
    void processDownloads();
    bool ABC_Download(const std::string& uuid);

    std::thread downloadThread;
    std::priority_queue<TaskWithPriority, std::vector<TaskWithPriority>,
                        CompareTask>
        downloadQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> stopFlag;
};

#endif  // DOWNLOADMANAGER_H