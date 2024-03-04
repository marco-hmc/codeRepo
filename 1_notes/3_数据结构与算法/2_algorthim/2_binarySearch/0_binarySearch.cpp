#include <iostream>
#include <vector>

using namespace std;

// 二分搜索函数
int binarySearch(vector<int> &nums, int target) {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1; // 如果未找到目标元素,则返回-1
}

int main() {
  vector<int> nums = {1, 3, 5, 7, 9, 11, 13};
  int target = 7;

  int result = binarySearch(nums, target);

  if (result != -1) {
    cout << "目标元素 " << target << " 在数组中的索引位置为: " << result
         << endl;
  } else {
    cout << "目标元素 " << target << " 未找到" << endl;
  }

  return 0;
}
