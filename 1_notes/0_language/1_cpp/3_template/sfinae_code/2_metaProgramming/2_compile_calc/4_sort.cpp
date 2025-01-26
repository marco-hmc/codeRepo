#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>

// 线性同余生成器，用于生成编译时随机数
constexpr unsigned int lcg(unsigned int seed) {
    return (1103515245 * seed + 12345) % 2147483648;
}

// 生成随机数数组
template <std::size_t N, unsigned int Seed>
constexpr std::array<int, N> generate_random_array() {
    std::array<int, N> arr = {};
    unsigned int seed = Seed;
    for (std::size_t i = 0; i < N; ++i) {
        seed = lcg(seed);
        arr[i] = seed % 1000;  // 生成 0 到 999 之间的随机数
    }
    return arr;
}

// 编译时排序算法（使用递归选择排序）
template <typename T, std::size_t N>
constexpr void compile_time_sort_constexpr(std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N - 1; ++i) {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < N; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

template <typename T, std::size_t N>
constexpr std::array<T, N> sort_array(const std::array<T, N>& arr) {
    std::array<T, N> sorted_arr = arr;
    compile_time_sort(sorted_arr);
    return sorted_arr;
}

int main() {
    constexpr std::size_t array_size = 200;
    constexpr unsigned int seed = 12345;  // 随机数种子

    // 生成随机数数组
    constexpr std::array<int, 200UL> arr =
        generate_random_array<array_size, seed>();

    {
        auto sorted_arr = arr;
        auto start = std::chrono::high_resolution_clock::now();
        compile_time_sort(sorted_arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // 打印排序后的结果
        for (int num : sorted_arr) {
            std::cout << num << " ";
        }
        std::cout << "\n编译时排序耗时: " << duration.count() << " ms\n";
    }

    {
        auto sorted_arr = arr;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(sorted_arr.begin(), sorted_arr.end());
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // 打印排序后的结果
        for (int num : sorted_arr) {
            std::cout << num << " ";
        }
        std::cout << "\nstd排序耗时: " << duration.count() << " ms\n";
    }
    return 0;
}
