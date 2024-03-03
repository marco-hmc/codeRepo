(3) 二分搜索算法(1)
    lower_bound(beg, end, val) // 返回指向第一个小于等于val的迭代器
    (2) upper_bound(beg, end, val) // 返回指向第一个大于val的迭代器
    (3) equal_range(beg, end, val) // 返回以上一个pair包含以上两个函数返回参数

    while (left <= right) {
  mid = left + (right - left) / 2; // 等价于(right+left)/2,但是可避免溢出
  if (nums[mid] > target)
    right = mid - 1; // 因为mid不是,所以可以排除
  else if (num[mid] < target)
    left = mid + 1;
  else
    return mid;
}