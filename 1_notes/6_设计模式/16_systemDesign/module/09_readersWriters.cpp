#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;  // 互斥锁,用于保护共享资源的访问
std::condition_variable cv;  // 条件变量,用于读者和写者之间的同步
int readers = 0;  // 当前读者的数量
bool writing = false;  // 是否有写者正在写入

void reader(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (writing) {
        cv.wait(lock);
    }
    readers++;
    lock.unlock();

    // 读取共享资源
    std::cout << "Reader " << id << " is reading" << '\n';

    lock.lock();
    readers--;
    if (readers == 0) {
        cv.notify_all();
    }
}

void writer(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (writing || readers > 0) {
        cv.wait(lock);
    }
    writing = true;
    lock.unlock();

    // 写入共享资源
    std::cout << "Writer " << id << " is writing" << '\n';

    lock.lock();
    writing = false;
    cv.notify_all();
}

int main() {
    const int numReaders = 5;
    const int numWriters = 2;

    std::thread readers[numReaders];
    std::thread writers[numWriters];

    // 创建读者线程
    for (int i = 0; i < numReaders; i++) {
        readers[i] = std::thread(reader, i);
    }

    // 创建写者线程
    for (int i = 0; i < numWriters; i++) {
        writers[i] = std::thread(writer, i);
    }

    // 等待所有读者线程和写者线程结束
    for (int i = 0; i < numReaders; i++) {
        readers[i].join();
    }
    for (int i = 0; i < numWriters; i++) {
        writers[i].join();
    }

    return 0;
}
