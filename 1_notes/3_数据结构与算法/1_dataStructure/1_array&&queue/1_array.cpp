#include <algorithm>
#include <iostream>
#include <vector>

void rotateArray(std::vector<int> &arr, int k) {
    int n = arr.size();
    k = k % n;

    std::reverse(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.begin() + k);
    std::reverse(arr.begin() + k, arr.end());
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    int k = 3;

    rotateArray(arr, k);
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}
