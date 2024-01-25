#include  <vector>
using namespace std;
// * 3 种快排基准选择方法:

// 随机(rand函数)/固定(队首/队尾)/三数取中(队首/队中和队尾的中间数)

// * 4种优化方式:

// 优化1:当待排序序列的长度分割到一定大小后,使用插入排序

// 优化2:在一次分割结束后,可以把与Key相等的元素聚在一起,继续下次分割时,不用再对与key相等元素分割

// 优化3:优化递归操作

// 优化4:使用并行或多线程处理子序列
void swap(vector<int>& vec, int a, int b) {
    vec[a] = vec[a] ^ vec[b];
    vec[b] = vec[a] ^ vec[b];
    vec[a] = vec[a] ^ vec[b];
}
int partition(vector<int>& vec, int start, int end) {
    int pivot = vec[start + (end - start) / 2];
    while (start < end) {
        while (start < end and vec[start] < pivot) start++;
        while (start<end and vec[end]>pivot) end--;
        if (start < end) swap(vec, start, end);
    }
    return start;
}
void quickSort(vector<int>& vec, int start, int end) {
    if (start > end) return;
    int pivot = partition(vec, start, end);
    quickSort(vec, start, pivot - 1);
    quickSort(vec, pivot + 1, end);
}