#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<bool> ready(false);
std::atomic<bool> winner(false);

void count1m(int id) {
    while (!ready) {
    }

    for (int i = 0; i < 1000000; ++i) {
    }

    if (!winner.exchange(true)) {
        std::cout << "thread #" << id << " won!\n";
    }
};

int main() {
    std::cout << "spawning 10 threads that count to 1 million...\n";
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i) {
        threads.emplace_back(count1m, i);
    }

    ready = true;
    for (auto &th : threads) {
        th.join();
    }

    return 0;
}
