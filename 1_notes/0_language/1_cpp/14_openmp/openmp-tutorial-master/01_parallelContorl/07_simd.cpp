#include <omp.h>

#include <iostream>

int main() {
    const int N = 1000;
    int a[N], b[N], c[N];

    // 初始化数组
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

// 使用 SIMD 指令向量化循环
#pragma omp simd
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // 打印结果
    for (int i = 0; i < 10; i++) {
        std::cout << "c[" << i << "] = " << c[i] << std::endl;
    }

    return 0;
}