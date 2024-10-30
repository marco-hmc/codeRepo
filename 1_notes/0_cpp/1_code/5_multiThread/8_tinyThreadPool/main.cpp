#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "thread_pool.hpp"

int main() {
    ThreadPool pool(4);
    std::vector< std::future<std::string> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(pool.enqueue([i] {
            std::cout << "hello " << i << '\n';

            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::cout << "world " << i << '\n';
            return std::string("---thread ") + std::to_string(i) +
                   std::string(" finished.---");
        }));
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << '\n';

    return 0;
}
