#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
    std::ios::sync_with_stdio(false); // Linux 中，sync false 会导致 cout 变为完全缓冲
    std::cout << "Hello,";
    std::this_thread::sleep_for(1s);
    std::cout << "World\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Exiting\n";
    return 0;
}
