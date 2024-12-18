#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/*
  1. call_once是什么？
    `std::call_once`是一个C++标准库函数，用于确保一个函数或代码块只被执行一次。
    `std::call_once`接受一个`std::once_flag`对象和一个函数或代码块作为参数。
    `std::call_once`会检查`std::once_flag`对象是否已经被调用过，如果没有，那么它会调用传入的函数或代码块。
*/

namespace identifier1 {
    int winner;
    std::once_flag winner_flag;

    void set_winner(int x) { winner = x; }

    void wait_1000ms(int id) {
        for (int i = 0; i < 1000; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::call_once(winner_flag, set_winner, id);
    }

    void test2() {
        std::vector<std::thread> threads;
        threads.reserve(10);
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back(wait_1000ms, i + 1);
        }

        std::cout
            << "waiting for the first among 10 threads to count 1000ms...\n";

        for (auto &th : threads) {
            th.join();
        }

        std::cout << "winner thread: " << winner << '\n';
    }
}  // namespace identifier1

int main() { identifier1::test2(); }
