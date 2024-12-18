#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

struct pCout : public std::stringstream {
    static inline std::mutex cout_mutex;
    ~pCout() override {
        std::lock_guard<std::mutex> l{cout_mutex};
        std::cout << rdbuf();
    }
};

std::queue<size_t> q;
std::mutex q_mutex;
bool production_stopped{false};

std::condition_variable go_produce;
std::condition_variable go_consume;

static void producer(size_t id, size_t items, size_t stock) {
    for (size_t i = 0; i < items; ++i) {
        std::unique_lock<std::mutex> lock(q_mutex);
        go_produce.wait(lock, [&] { return q.size() < stock; });
        q.push(id * 100 + i);

        pCout{} << " Producer " << id << " --> item " << std::setw(3)
                << q.back() << '\n';

        go_consume.notify_all();
        std::this_thread::sleep_for(90ms);
    }

    pCout{} << "EXIT: Producer " << id << '\n';
}

static void consumer(size_t id) {
    while (!production_stopped || !q.empty()) {
        std::unique_lock<std::mutex> lock(q_mutex);
        if (go_consume.wait_for(lock, 1s, [] { return !q.empty(); })) {
            pCout{} << " item " << std::setw(3) << q.front() << " --> Consumer "
                    << id << '\n';
            q.pop();

            go_produce.notify_all();
            std::this_thread::sleep_for(130ms);
        }
    }

    pCout{} << "EXIT: Producer " << id << '\n';
}

int main() {
    std::vector<std::thread> workers;
    workers.reserve(3);
    for (size_t i = 0; i < 3; ++i) {
        workers.emplace_back(producer, i, 15, 5);
    }

    std::vector<std::thread> consumers;
    consumers.reserve(5);
    for (size_t i = 0; i < 5; ++i) {
        consumers.emplace_back(consumer, i);
    }

    for (auto &t : workers) {
        t.join();
    }
    production_stopped = true;
    for (auto &t : consumers) {
        t.join();
    }
}