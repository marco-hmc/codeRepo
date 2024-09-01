// 数组循环右移 将一个长度为n的数组A的元素循环右移k位
// 比如 数组 1, 2, 3, 4, 5 循环右移3位之后变成 3, 4, 5, 1, 2
#include <algorithm>
#include <iostream>
#include <vector>


void rotateArray(std::vector<int> &arr, int k) {
  int n = arr.size();
  k = k % n; // handle cases where k > n

  // Reverse the entire array
  std::reverse(arr.begin(), arr.end());

  // Reverse the first k elements
  std::reverse(arr.begin(), arr.begin() + k);

  // Reverse the remaining elements
  std::reverse(arr.begin() + k, arr.end());
}

int main() {
  std::vector<int> arr = {1, 2, 3, 4, 5};
  int k = 3;

  rotateArray(arr, k);

  // Print the rotated array
  for (int num : arr) {
    std::cout << num << " ";
  }
  std::cout << '\n';

  return 0;
}
