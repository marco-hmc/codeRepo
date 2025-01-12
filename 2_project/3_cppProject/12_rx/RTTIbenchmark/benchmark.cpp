#include <chrono>
#include <iostream>

extern void testDynamicCast(int times = 1000000);
extern void testRTTI(int times = 1000000);

template <typename Func, typename... Args>
void measureExecutionTime(Func func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(args...);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\t-Execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << "ms" << std::endl;
}

int main() {
    std::cout << "  Dynamic cast test" << std::endl;
    measureExecutionTime(testDynamicCast, 1000000);

    std::cout << "  RTTI test" << std::endl;
    measureExecutionTime(testRTTI, 1000000);
    return 0;
}
