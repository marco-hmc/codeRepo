#include <immintrin.h>  // AVX512头文件

#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

// Implementation 1: 简单的累加求平均值
double calculateAverage1(const std::vector<int>& nums) {
    if (nums.empty()) return 0.0;  // 如果vector为空，返回0.0
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    return sum / nums.size();
}

// Implementation 2: 使用long long避免溢出
double calculateAverage2(const std::vector<int>& nums) {
    if (nums.empty()) return 0.0;  // 空向量检查
    long long sum = std::accumulate(nums.begin(), nums.end(), 0LL);
    return static_cast<double>(sum) / nums.size();
}

// Implementation 3: 分批处理避免溢出
double calculateAverage3(const std::vector<int>& nums) {
    if (nums.empty()) return 0.0;

    std::vector<long long> partialSums;  // 用于分批累加的容器
    long long sum = 0;
    for (int num : nums) {
        // 检查加法前是否接近溢出
        if (num > 0 && sum > std::numeric_limits<long long>::max() - num) {
            // 将当前总和加到分批累加的容器中
            partialSums.push_back(sum);
            sum = 0;  // 重置当前总和
        }
        sum += num;
    }
    // 确保最后一批也被加入
    partialSums.push_back(sum);

    // 计算所有分批累加的总和
    long long finalSum = 0;
    for (long long partialSum : partialSums) {
        finalSum += partialSum;
    }

    return static_cast<double>(finalSum) / nums.size();
}

// Implementation 4: 使用AVX512进行向量加法
double calculateAverageAVX512(const std::vector<int>& nums) {
    if (nums.empty()) return 0.0;

    __m512i sumVec = _mm512_setzero_si512();  // 初始化为0
    int i = 0;
    for (; i + 15 < nums.size(); i += 16) {
        __m512i dataVec = _mm512_loadu_si512(
            reinterpret_cast<const __m512i*>(&nums[i]));  // 加载数据
        sumVec = _mm512_add_epi32(sumVec, dataVec);       // 向量加法
    }

    // 将向量和转换为标量
    int sumArray[16];
    _mm512_storeu_si512(reinterpret_cast<__m512i*>(sumArray), sumVec);
    long long sum = 0;
    for (int j = 0; j < 16; ++j) {
        sum += sumArray[j];
    }

    // 处理剩余的元素
    for (; i < nums.size(); ++i) {
        sum += nums[i];
    }

    return static_cast<double>(sum) / nums.size();
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Average (Implementation 1): " << calculateAverage1(nums)
              << std::endl;
    std::cout << "Average (Implementation 2): " << calculateAverage2(nums)
              << std::endl;
    std::cout << "Average (Implementation 3): " << calculateAverage3(nums)
              << std::endl;
    std::cout << "Average (Implementation 4): " << calculateAverageAVX512(nums)
              << std::endl;

    return 0;
}