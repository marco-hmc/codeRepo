#include <iostream>
#include <vector>
#include <algorithm>

void original_method() {
    std::vector<int> numbers = { 1, 2, 3, 4, 2, 5, 2, 6, 7, 2 };
    int target = 2;

    // 使用循环逐个删除目标元素
    for (auto it = numbers.begin(); it != numbers.end();) {
        if (*it == target) {
            it = numbers.erase(it);
        }
        else {
            ++it;
        }
    }

    // 输出移除后的结果
    for (int num : numbers) {
        std::cout << num << " ";
    }
}

void erase_remove_trick() {
    std::vector<int> numbers = { 1, 2, 3, 4, 2, 5, 2, 6, 7, 2 };

    // 使用 std::remove 将所有的 2 移到末尾，并返回新的范围末尾
    auto new_end = std::remove(numbers.begin(), numbers.end(), 2);

    // 使用 std::vector::erase 删除从新范围末尾到原范围末尾的元素
    numbers.erase(new_end, numbers.end());

    // 输出移除后的结果
    for (int num : numbers) {
        std::cout << num << " ";
    }
}

int main() {
    original_method();
    erase_remove_trick();
    return 0;
}
