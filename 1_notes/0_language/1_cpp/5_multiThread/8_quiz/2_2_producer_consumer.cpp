#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable produce, consume;
int cargo = 0;

void consumer() {
    std::unique_lock<std::mutex> lck(mtx);
    while (cargo == 0) {
        consume.wait(lck);
    }
    std::cout << cargo << '\n';
    cargo = 0;
    produce.notify_one();
}

void producer(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (cargo != 0) {
        produce.wait(lck);
    }
    cargo = id;
    consume.notify_one();
}

int main() {
    std::thread consumers[10];
    std::thread producers[10];

    for (int i = 0; i < 10; ++i) {
        consumers[i] = std::thread(consumer);
        producers[i] = std::thread(producer, i + 1);
    }

    for (int i = 0; i < 10; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
