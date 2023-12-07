#include <iostream>
#include <vector>
#include <algorithm>

int square(int x) {
    return x * x;
}

int main() {
    std::vector<int> numbers = { 1, 2, 3, 4, 5 };
    std::vector<int> result;

    // 使用 std::transform 对 numbers 中的元素进行平方操作，并将结果存储到 result 中
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(result), square);

    // 输出结果
    for (int num : result) {
        std::cout << num << " ";
    }

    return 0;
}