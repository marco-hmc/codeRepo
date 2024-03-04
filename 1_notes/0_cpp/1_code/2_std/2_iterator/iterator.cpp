#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> nums = {1, 2, 3, 4, 4, 5, 6, 7, 8, 9};

  // 使用 lower_bound 查找第一个大于等于 4 的元素
  auto lower = std::lower_bound(nums.begin(), nums.end(), 4);
  if (lower != nums.end()) {
    std::cout << "First element greater than or equal to 4: " << *lower
              << std::endl;
  }

  // 使用 equal_range 查找所有等于 4 的元素
  auto range = std::equal_range(nums.begin(), nums.end(), 4);
  std::cout << "All elements equal to 4: ";
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return 0;
}