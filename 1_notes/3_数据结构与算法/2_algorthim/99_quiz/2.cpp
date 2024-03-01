// 求数组中最小的10个数,用堆写
#include <iostream>
#include <vector>
#include <queue>

std::vector<int> findSmallestNumbers(const std::vector<int>& arr, int k) {
    /**
     * @brief 使用std::priority_queue创建一个最小堆. 根节点最小; 最大堆,根节点最大.
     *
     * @tparam T 堆中元素的类型.
     * @tparam Container 存储堆元素的容器类型,默认为std::vector<T>.
     * @tparam Compare 元素比较函数对象类型,默认为std::less<T>,创建最大堆.
     *
     * @param minHeap 最小堆对象.
     *
     * @details std::priority_queue是一个容器适配器,它提供了堆的功能.堆是一种特殊的二叉树结构,具有以下特点:
     * 1. 堆中的每个节点的值都大于等于(或小于等于)其子节点的值.
     * 2. 堆中的最大(或最小)元素总是位于根节点.
     *
     * 使用std::priority_queue时,可以通过指定模板参数Container和Compare来自定义存储元素的容器类型和元素比较方式.
     * 默认情况下,Container为std::vector<T>,Compare为std::less<T>,即创建最大堆.
     * 若要创建最小堆,可以使用std::greater<T>作为Compare参数.
     *
     * @note std::priority_queue的常用操作包括push/pop/top等.
     *
     * 示例代码:
     * \code{.cpp}
     * std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
     * minHeap.push(5);
     * minHeap.push(2);
     * minHeap.push(7);
     *
     * int topElement = minHeap.top(); // 获取堆顶元素,结果为2
     * minHeap.pop(); // 弹出堆顶元素
     * \endcode
     */
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // Insert first k elements into the min heap
    for (int i = 0; i < k; i++) {
        minHeap.push(arr[i]);
    }

    // Process remaining elements
    for (int i = k; i < arr.size(); i++) {
        if (arr[i] < minHeap.top()) {
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }

    // Extract the smallest k elements from the min heap
    std::vector<int> smallestNumbers;
    while (!minHeap.empty()) {
        smallestNumbers.push_back(minHeap.top());
        minHeap.pop();
    }

    return smallestNumbers;
}

int main() {
    std::vector<int> arr = { 9, 4, 2, 7, 5, 1, 8, 3, 6, 10, 12, 11 };
    int k = 10;

    std::vector<int> smallestNumbers = findSmallestNumbers(arr, k);

    std::cout << "Smallest " << k << " numbers: ";
    for (int num : smallestNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
