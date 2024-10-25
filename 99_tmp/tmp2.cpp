#include <sys/wait.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

// 定义一个结构体，包含一个整数和填充数据
struct PaddedInt {
    int value;
    char padding[64 - sizeof(int)];  // 确保每个变量占据一个独立的缓存行
};

constexpr int runSeconds = 3;

void increment(PaddedInt &paddedInt, std::atomic<bool> &stop_flag) {
    while (!stop_flag.load()) {
        ++paddedInt.value;
    }
}

void processA() {
    PaddedInt i = {0};
    std::atomic<bool> stop_flag(false);

    std::thread t(increment, std::ref(i), std::ref(stop_flag));

    std::this_thread::sleep_for(std::chrono::seconds(runSeconds));
    stop_flag.store(true);

    t.join();
    std::cout << "Process A: i = " << i.value / 1e8 << std::endl;
}

void processB() {
    PaddedInt i1 = {0}, i2 = {0}, i3 = {0}, i4 = {0};
    std::atomic<bool> stop_flag1(false);
    std::atomic<bool> stop_flag2(false);
    std::atomic<bool> stop_flag3(false);
    std::atomic<bool> stop_flag4(false);

    std::thread t1(increment, std::ref(i1), std::ref(stop_flag1));
    std::thread t2(increment, std::ref(i2), std::ref(stop_flag2));
    std::thread t3(increment, std::ref(i3), std::ref(stop_flag3));
    std::thread t4(increment, std::ref(i4), std::ref(stop_flag4));

    std::this_thread::sleep_for(std::chrono::seconds(runSeconds));
    stop_flag1.store(true);
    stop_flag2.store(true);
    stop_flag3.store(true);
    stop_flag4.store(true);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Process B: i1 = " << i1.value / 1e8
              << ", i2 = " << i2.value / 1e8 << ", i3 = " << i3.value / 1e8
              << ", i4 = " << i4.value / 1e8 << std::endl;
}

int main() {
    processB();
    return 0;
}