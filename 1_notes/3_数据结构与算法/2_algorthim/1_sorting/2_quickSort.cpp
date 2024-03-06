#include <iostream>
#include <vector>

// 这段代码实现了快速排序算法,这是一种非常高效的排序算法,其基本思想是使用分治策略.

// [`partition`]函数是快速排序的核心部分.它接受一个数组和两个索引 `low` 和
// `high`,并将数组划分为两部分,使得左边的元素都小于一个选定的枢轴元素,右边的元素都大于枢轴元素.这个函数首先选择
// `high` 索引处的元素作为枢轴,然后从 `low` 到 `high - 1`
// 遍历数组.如果遇到的元素小于枢轴,就将其与数组中的下一个元素交换位置.最后,将枢轴元素放到正确的位置,使得它左边的元素都小于它,右边的元素都大于它.函数返回枢轴元素的索引.

// ['swap']函数用于交换两个元素的位置.它接受两个元素的引用,并使用
// [`iter_swap`]函数交换它们的值.注意,如果两个元素的地址相同,即它们实际上是同一个元素,那么
// [`swap`]函数不会做任何操作.

// [`quickSort`]函数是快速排序的主函数.它接受一个数组和两个索引 `low` 和
// `high`,并对索引范围内的数组进行排序.首先,它检查 `low` 是否小于
// `high`,如果不是,那么数组已经是有序的,函数直接返回.否则,它使用
// [`partition`]函数将数组划分为两部分,并得到枢轴元素的索引.然后,它对枢轴左边和右边的子数组分别进行快速排序.这是一个递归过程,直到所有的子数组都被排序.

using namespace std;

int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]);
  return i + 1;
}

void quickSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high);

    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
  }
}

int main() {
  vector<int> arr = {9, 5, 7, 2, 1, 8, 6, 3, 4};
  int n = arr.size();

  quickSort(arr, 0, n - 1);

  cout << "Sorted array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}