#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex rw_mutex;
int readers = 0;

void reader(int id) {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);
    readers++;
    std::cout << "Reader " << id << " is reading" << '\n';
    readers--;
}

void writer(int id) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);
    std::cout << "Writer " << id << " is writing" << '\n';
}

int main() {
    const int numReaders = 5;
    const int numWriters = 2;

    std::vector<std::thread> threads;

    threads.reserve(numReaders);
    for (int i = 0; i < numReaders; i++) {
        threads.emplace_back(reader, i);
    }

    for (int i = 0; i < numWriters; i++) {
        threads.emplace_back(writer, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}