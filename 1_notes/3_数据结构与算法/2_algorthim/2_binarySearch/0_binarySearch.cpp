#include <iostream>
#include <vector>

int binarySearch(std::vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    std::vector<int> nums = {1, 3, 5, 7, 9, 11, 13};
    int target = 7;

    int result = binarySearch(nums, target);

    if (result != -1) {
        std::cout << "目标元素 " << target
                  << " 在数组中的索引位置为: " << result << std::endl;
    } else {
        std::cout << "目标元素 " << target << " 未找到" << std::endl;
    }

    return 0;
}
