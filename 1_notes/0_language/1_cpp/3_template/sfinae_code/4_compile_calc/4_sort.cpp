#include <array>
#include <iostream>

// 编译时排序算法（使用递归选择排序）
template <typename T, std::size_t N>
constexpr void compile_time_sort(std::array<T, N>& arr) {
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

int main() {
    constexpr std::array<int, 5> arr = {5, 3, 8, 1, 2};

    // 编译时排序
    std::array<int, 5> sorted_arr = arr;
    compile_time_sort(sorted_arr);

    // 打印排序后的结果
    for (int num : sorted_arr) {
        std::cout << num << " ";
    }

    return 0;
}
