- vector求交集

  ```c++ vector<int>
intersect(vector<int> &nums1, vector<int> &nums2) {
  vector<int> res;
  std::sort(nums1.begin(), nums1.end());
  std::sort(nums2.begin(), nums2.end());
  std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(),
                        insert_iterator<vector<int>>(res, res.begin()));
  return res; // res:2,2
}
// 即函数只执行复制,不是插入!但是模板 insert_iterator
// 可以将复制转换为插入,可以解决该问题.

set<int> x1, x2, x2;
// 交集
set_intersection(x1.begin(), x1.end(), x2.begin(), x2.end(),
                 inserter(x, x.begin()));
// 并集
set_union(x1.begin(), x1.end(), x2.begin(), x2.end(), inserter(x, x.begin()));
// 差集
set_difference(x1.begin(), x1.end(), x2.begin(), x2.end(),
               inserter(x, x.begin()));

```
