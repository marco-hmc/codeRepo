#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>

// 自定义返回类型
class Foo {
public:
    Foo(bool success, const std::string& message) : success(success), message(message) {}
    bool success;
    std::string message;
};

// 下载任务类型
using DownloadTask = std::function<Foo()>;
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
    static DownloadManager& getInstance() {
        static DownloadManager instance;
        return instance;
    }

    std::future<Foo> addDownloadTask(const std::string& uuid, int priority) {
        auto promise = std::make_shared<std::promise<Foo>>();
        auto future = promise->get_future();
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            downloadQueue.push({priority, [this, uuid, promise]() {
                Foo result = ABC_Download(uuid);
                promise->set_value(result);
                return result;
            }});
        }
        cv.notify_one();
        return future;
    }

    void addDownloadTaskAsync(const std::string& uuid, int priority,
                              std::function<void(Foo)> callback) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            downloadQueue.push({priority, [this, uuid, callback]() {
                Foo result = ABC_Download(uuid);
                callback(result);
                return result;
            }});
        }
        cv.notify_one();
    }

    void addDownloadTaskSimple(const std::string& uuid, int priority) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            downloadQueue.push({priority, [this, uuid]() {
                Foo result = ABC_Download(uuid);
                return result;
            }});
        }
        cv.notify_one();
    }

private:
    DownloadManager() : stopFlag(false) {
        downloadThread = std::thread(&DownloadManager::processDownloads, this);
    }

    ~DownloadManager() {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            stopFlag = true;
        }
        cv.notify_all();
        if (downloadThread.joinable()) {
            downloadThread.join();
        }
    }

    DownloadManager(const DownloadManager&) = delete;
    DownloadManager& operator=(const DownloadManager&) = delete;

    void processDownloads() {
        while (true) {
            TaskWithPriority taskWithPriority;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                cv.wait(lock, [this]() { return !downloadQueue.empty() || stopFlag; });
                if (stopFlag && downloadQueue.empty()) {
                    break;
                }
                taskWithPriority = downloadQueue.top();
                downloadQueue.pop();
            }
            // 执行下载任务
            taskWithPriority.second();
        }
    }

    Foo ABC_Download(const std::string& uuid) {
        std::cout << "Downloading file with UUID: " << uuid << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟下载时间
        std::cout << "Downloaded file with UUID: " << uuid << std::endl;
        return Foo(true, "Download successful");  // 模拟下载成功
    }

    std::thread downloadThread;
    std::priority_queue<TaskWithPriority, std::vector<TaskWithPriority>, CompareTask> downloadQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> stopFlag;
};

int main() {
    DownloadManager& manager = DownloadManager::getInstance();

    // 添加下载任务并等待完成
    auto future1 = manager.addDownloadTask("uuid1", 1);
    auto future2 = manager.addDownloadTask("uuid2", 3);
    auto future3 = manager.addDownloadTask("uuid3", 2);

    // 等待任务完成
    future1.wait();
    future2.wait();
    future3.wait();

    // 检查任务结果
    std::cout << "Download uuid1 result: " << future1.get().message << std::endl;
    std::cout << "Download uuid2 result: " << future2.get().message << std::endl;
    std::cout << "Download uuid3 result: " << future3.get().message << std::endl;

    // 添加异步下载任务
    manager.addDownloadTaskAsync("uuid4", 1, [](Foo result) {
        if (result.success) {
            std::cout << "Async download completed successfully: " << result.message << std::endl;
        } else {
            std::cout << "Async download failed: " << result.message << std::endl;
        }
    });

    // 添加简单下载任务
    manager.addDownloadTaskSimple("uuid5", 2);

    // 等待一段时间以便下载任务完成
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}