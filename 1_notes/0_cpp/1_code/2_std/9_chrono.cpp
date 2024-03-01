
#include <iostream>
#include <chrono>

int main() {
    // 获取当前时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 将时间点转换为时间戳
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);

    // 输出时间戳
    std::cout << "当前时间戳: " << timestamp << std::endl;

    // 将时间戳转换为时间点
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(timestamp);

    // 获取当前日期和时间的字符串表示
    std::string timeString = std::ctime(&timestamp);

    // 输出日期和时间
    std::cout << "当前日期和时间: " << timeString << std::endl;

    // 获取程序运行时间
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // 模拟一段耗时操作
    for (int i = 0; i < 100000000; i++) {
        // do something
    }

    // 获取程序运行时间
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // 计算程序运行时间
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    // 输出程序运行时间
    std::cout << "程序运行时间: " << duration.count() << " 秒" << std::endl;

    return 0;
}
