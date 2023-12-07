#### (11) Top K问题(可以采取的方法有哪些,各自优点?)(重点)
*Top K 问题的常见形式:*
>给定10000个整数,找第K大(第K小)的数<br>
 给定10000个整数,找出最大(最小)的前K个数<br>
给定100000个单词,求前K词频的单词<br>

*解决Top K问题若干种方法*
* 使用最大最小堆.求最大的数用最小堆,求最小的数用最大堆.
* Quick Select算法.使用类似快排的思路,根据pivot划分数组.
* 使用排序方法,排序后再寻找top K元素.
* 使用选择排序的思想,对前K个元素部分排序.
* 将1000.....个数分成m组,每组寻找top K个数,得到m×K个数,在这m×k个数里面找top K个数.

1. 使用最大最小堆的思路 (以top K 最大元素为例)<br>
按顺序扫描这10000个数,先取出K个元素构建一个大小为K的最小堆.每扫描到一个元素,如果这个元素大于堆顶的元素(这个堆最小的一个数),就放入堆中,并删除堆顶的元素,同时整理堆.如果这个元素小于堆顶的元素,就直接pass.最后堆中剩下的元素就是最大的前Top K个元素,最右的叶节点就是Top 第K大的元素.

>note:最小堆的插入时间复杂度为log(n),n为堆中元素个数,在这里是K.最小堆的初始化时间复杂度是nlog(n)

C++中的最大最小堆要用标准库的priority_queue来实现.
```C++
struct Node {
    int value;
    int idx;
    Node (int v, int i): value(v), idx(i) {}
    friend bool operator < (const struct Node &n1, const struct Node &n2) ; 
};

inline bool operator < (const struct Node &n1, const struct Node &n2) {
    return n1.value < n2.value;
}

priority_queue<Node> pq; // 此时pq为最大堆
```

2. 使用Quick Select的思路(以寻找第K大的元素为例)<br>
Quick Select脱胎于快速排序,提出这两个算法的都是同一个人.算法的过程是这样的:
首先选取一个枢轴,然后将数组中小于该枢轴的数放到左边,大于该枢轴的数放到右边.
此时,如果左边的数组中的元素个数大于等于K,则第K大的数肯定在左边数组中,继续对左边数组执行相同操作;
如果左边的数组元素个数等于K-1,则第K大的数就是pivot;
如果左边的数组元素个数小于K,则第K大的数肯定在右边数组中,对右边数组执行相同操作.

这个算法与快排最大的区别是,每次划分后只处理左半边或者右半边,而快排在划分后对左右半边都继续排序.
```
//此为Java实现
public int findKthLargest(int[] nums, int k) {
  return quickSelect(nums, k, 0, nums.length - 1);
}

// quick select to find the kth-largest element
public int quickSelect(int[] arr, int k, int left, int right) {
  if (left == right) return arr[right];
  int index = partition(arr, left, right);
  if (index - left + 1 > k)
    return quickSelect(arr, k, left, index - 1);
  else if (index - left + 1 == k)
    return arr[index];
  else
    return quickSelect(arr, k - (index - left + 1), index + 1, right);

}
```

3. 使用选择排序的思想对前K个元素排序 ( 以寻找前K大个元素为例)<br>
扫描一遍数组,选出最大的一个元素,然后再扫描一遍数组,找出第二大的元素,再扫描一遍数组,找出第三大的元素.....以此类推,找K个元素,时间复杂度为O(N*K)