#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// 使用 std::atomic 实现 compareAndSwap
class AtomicCounter {
  public:
    AtomicCounter() : counter(0) {}

    // compareAndSwap 函数
    bool compareAndSwap(int expected, int desired) {
        return counter.compare_exchange_strong(expected, desired);
    }

    // 获取当前计数值
    int get() const { return counter.load(); }

  private:
    std::atomic<int> counter;
};

void increment(AtomicCounter& counter, int id) {
    for (int i = 0; i < 1000; ++i) {
        int expected = counter.get();
        while (!counter.compareAndSwap(expected, expected + 1)) {
            expected = counter.get();
        }
    }
    std::cout << "Thread " << id << " finished.\n";
}

int main() {
    AtomicCounter counter;
    std::vector<std::thread> threads;

    // 创建多个线程来并发地增加计数器
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment, std::ref(counter), i);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << counter.get() << std::endl;
    return 0;
}