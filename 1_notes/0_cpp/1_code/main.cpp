#include <iostream>
#include <chrono>

int main() {
    std::cout << "system_clock: "
        << double(std::chrono::system_clock::period::num) / std::chrono::system_clock::period::den
        << " seconds" << std::endl;
    std::cout << "steady_clock: "
        << double(std::chrono::steady_clock::period::num) / std::chrono::steady_clock::period::den
        << " seconds" << std::endl;
    std::cout << "high_resolution_clock: "
        << double(std::chrono::high_resolution_clock::period::num) / std::chrono::high_resolution_clock::period::den
        << " seconds" << std::endl;
    return 0;
}