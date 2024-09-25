#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 使用 std::remove_if 移除所有偶数
    auto it = std::remove_if(numbers.begin(), numbers.end(),
                             [](int x) { return x % 2 == 0; });

    // 实际移除元素
    numbers.erase(it, numbers.end());

    // 输出结果
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}