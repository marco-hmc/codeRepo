#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

const int num_threads = 24;          // 增加线程数量
const int num_iterations = 1000000;  // 保持迭代次数不变

std::atomic<int> data_relaxed(0);
std::atomic<int> data_seq_cst(0);

void increment_relaxed() {
    for (int i = 0; i < num_iterations; ++i) {
        data_relaxed.fetch_add(1, std::memory_order_relaxed);
        // 减少计算复杂度
        int temp = data_relaxed.load(std::memory_order_relaxed);
        temp = (temp * 2) / 3;
    }
}

void increment_seq_cst() {
    for (int i = 0; i < num_iterations; ++i) {
        data_seq_cst.fetch_add(1, std::memory_order_seq_cst);
        // 减少计算复杂度
        int temp = data_seq_cst.load(std::memory_order_seq_cst);
        temp = (temp * 2) / 3;
    }
}

int main() {
    // 测试使用 std::memory_order_relaxed 的性能
    auto start_relaxed = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads_relaxed;
    for (int i = 0; i < num_threads; ++i) {
        threads_relaxed.emplace_back(increment_relaxed);
    }
    for (auto& t : threads_relaxed) {
        t.join();
    }
    auto end_relaxed = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_relaxed =
        end_relaxed - start_relaxed;
    std::cout << "Relaxed memory order duration: " << duration_relaxed.count()
              << " seconds\n";

    // 测试使用 std::memory_order_seq_cst 的性能
    auto start_seq_cst = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads_seq_cst;
    for (int i = 0; i < num_threads; ++i) {
        threads_seq_cst.emplace_back(increment_seq_cst);
    }
    for (auto& t : threads_seq_cst) {
        t.join();
    }
    auto end_seq_cst = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq_cst =
        end_seq_cst - start_seq_cst;
    std::cout << "Sequential consistent memory order duration: "
              << duration_seq_cst.count() << " seconds\n";

    return 0;
}