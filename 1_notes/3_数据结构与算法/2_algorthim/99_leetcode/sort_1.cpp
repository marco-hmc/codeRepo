#include <iostream>
#include <vector>
#include <cmath>

// 找出排序数组中离第k个数最近的m个数,最近的意思是相减绝对值最小.同时在main函数使用简单的测试用例进行测试
std::vector<int> findClosestNumbers(const std::vector<int>& arr, int k, int m) {
    std::vector<int> closestNumbers;
    int n = arr.size();
    int kIndex = -1;

    // Find the index of the kth number
    for (int i = 0; i < n; i++) {
        if (arr[i] == k) {
            kIndex = i;
            break;
        }
    }

    if (kIndex == -1) {
      std::cout << "Error: kth number not found in the array." << '\n';
      return closestNumbers;
    }

    int left = kIndex - 1;
    int right = kIndex + 1;

    while (m > 0 && left >= 0 && right < n) {
        int diffLeft = std::abs(arr[left] - k);
        int diffRight = std::abs(arr[right] - k);

        if (diffLeft <= diffRight) {
            closestNumbers.push_back(arr[left]);
            left--;
        } else {
            closestNumbers.push_back(arr[right]);
            right++;
        }

        m--;
    }

    while (m > 0 && left >= 0) {
        closestNumbers.push_back(arr[left]);
        left--;
        m--;
    }

    while (m > 0 && right < n) {
        closestNumbers.push_back(arr[right]);
        right++;
        m--;
    }

    return closestNumbers;
}

int main() {
    std::vector<int> arr = { 1, 3, 5, 7, 9, 11, 13, 15 };
    int k = 7;
    int m = 3;

    std::vector<int> closestNumbers = findClosestNumbers(arr, k, m);

    std::cout << "Closest numbers to " << k << ": ";
    for (int num : closestNumbers) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}
