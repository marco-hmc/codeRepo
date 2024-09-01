// #### (21)希尔排序说一下 / 手撕
// https ://www.cnblogs.com/chengxiao/p/6104371.html
// 希尔排序是把记录按下标的一定增量分组, 对每组使用直接插入排序算法排序;随着增量逐渐减少, 每组包含的关键词越来越多, 当增量减至1时, 整个文件恰被分成一组, 算法便终止.

#include <iostream>
#include <vector>

void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    std::vector<int> arr = { 9, 5, 7, 2, 1, 8, 3, 6, 4 };

    std::cout << "Before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    shellSort(arr);

    std::cout << "After sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}
