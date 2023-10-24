#include <iostream>
#include <vector>
#include <algorithm>

bool is_even(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    std::vector<int> evens;

    // 使用 std::copy_if 将满足偶数条件的元素复制到 evens 中
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens), is_even);

    // 输出结果
    for (int num : evens) {
        std::cout << num << " ";
    }

    return 0;
}