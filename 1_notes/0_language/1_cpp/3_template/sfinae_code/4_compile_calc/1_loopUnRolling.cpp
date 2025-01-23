#include <chrono>
#include <iostream>

/*
1. 什么是循环展开？
    循环展开是一种优化技术，用于减少循环的开销。
    通过在编译时展开循环，可以减少循环的迭代次数，从而提高程序的性能。

2. 循环展开的优点是什么？
    o3: 
        withUnrolling: 0.021066ms
        withoutUnrolling: 
    o1: 
        withoutUnrolling: 0.024991 ms
        withUnrolling: 0.004657 ms
*/
void calc(int i) {
    int result = 1;
    for (int j = 1; j <= i; ++j) {
        result *= j;
    }
    std::cout << "Iteration " << i << " result: " << result << '\n';
}

template <int UnrollFactor>
void loopWithUnrolling(int iterations) {
    int i = 0;
    for (; i <= iterations - UnrollFactor; i += UnrollFactor) {
        for (int j = 0; j < UnrollFactor; ++j) {
            calc(i + j);  // 执行计算任务
        }
    }
    for (; i < iterations; ++i) {
        calc(i);  // 执行计算任务
    }
}

// 未优化版本
void loopWithoutUnrolling(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        calc(i);
    }
}

int main() {
    int iterations = 20;

    // 未优化版本计时
    auto start = std::chrono::high_resolution_clock::now();
    loopWithoutUnrolling(iterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken without unrolling: " << duration.count() << " ms"
              << std::endl;

    // 优化版本计时
    start = std::chrono::high_resolution_clock::now();
    loopWithUnrolling<4>(iterations);  // 使用展开因子为4
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken with unrolling: " << duration.count() << " ms"
              << std::endl;
    return 0;
}
