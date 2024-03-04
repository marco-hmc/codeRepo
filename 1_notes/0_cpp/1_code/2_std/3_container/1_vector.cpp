- vector去重

  ```c++
    // method1
    sort(vec.begin(), vec.end());
vec.erase(unique(vec.begin(), vec.end()), vec.end());

// method2
set<int> s(vec.begin(), vec.end());
vec.assign(s.begin(), s.end());
```

    - vector求交集

  ```c++ vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
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

    - vector去重

  ```c++
    // method1
    sort(vec.begin(), vec.end());
vec.erase(unique(vec.begin(), vec.end()), vec.end());

// method2
set<int> s(vec.begin(), vec.end());
vec.assign(s.begin(), s.end());
```

#include <iostream>
#include <string>
#include <vector>

    using namespace std;
/*
实现string常见的操作:
        (1)构造/赋值:
        (2)基本操作:size(), empty(),  push_back(), pop_back(), insert(),
erase(), clear(), swap();
*/

void myVectorTest() {
  // 1. 初始化
  vector<int> myVec = {1, 3, 5, 7, 9};
  vector<int> myVec1 = {4, 6, 8};
  cout << "the length of myVec:" << myVec.size() << endl;
  myVec.push_back(0); // 在尾部添加字符
  cout << "after pushing, myVec is: " << endl;
  for (auto tmp : myVec) {
    cout << tmp << ' ';
  }
  /*
  insert()版本:
          (1)insert(p, t)
  //在迭代器p之前创建一个值为t,返回指向新添加的元素的迭代器 (2)insert(p, b, e)
  //将迭代器[b, e)指定的元素插入到p所指位置,返回第一个插入元素的迭代器
          (3)insert(p, il)    //将列表中的元素插入,返回第一个插入元素的迭代器
                                //关于迭代器确定范围都是左闭右开!!!!
  */
  auto ret =
      myVec.insert(myVec.begin() + 1, 2); // 插入单个元素,返回该元素迭代器
  cout << "after inserting , myVec is : " << endl;
  for (auto tmp : myVec) {
    cout << tmp << ' ';
  }
  cout << "返回的迭代器值为:" << *ret << endl;

  auto ret1 =
      myVec.insert(myVec.begin() + 1, myVec1.begin(),
                   myVec1.end()); // 插入系列元素,返回第一个插入元素迭代器
  cout << "after inserting , myVec is : " << endl;
  for (auto tmp : myVec) {
    cout << tmp << ' ';
  }
  cout << "返回的迭代器值为:" << *ret1 << endl;
  /*
insert()版本:
  (1)erase(p)         //删除迭代器p所指元素,返回下一个元素的迭代器
  (2)erase(b, e)      //删除迭代器[b, e) 范围内的元素;
                        //关于迭代器确定范围都是左闭右开!!!!
*/
  auto ret2 = myVec.erase(myVec.begin() + 1); // 删除单个迭代器指向的元素,
  cout << "after earsing , myVec is : " << endl;
  for (auto tmp : myVec) {
    cout << tmp << ' ';
  }
  cout << "返回的迭代器值为:" << *ret2 << endl;

  auto ret3 = myVec.erase(myVec.begin() + 1,
                          myVec.begin() + 4); // 返回迭代器对指向的范围内的元素
  cout << "after earsing , myVec is : " << endl;
  for (auto tmp : myVec) {
    cout << tmp << ' ';
  }
  cout << "返回的迭代器值为:" << *ret3 << endl;

  swap(myVec, myVec1); // 交换两个容器的值,其实实质上并不交换
  cout << '\n';
}

int main() {
  myVectorTest();
  cout << "done" << endl;
}

#include <algorithm> //sort函数/交并补函数
#include <iostream>
#include <iterator> //求交并补使用到的迭代器
#include <vector>

using namespace std;

// 打印容器vector
void print_vector(vector<int> v) {
  if (v.size() > 0) {
    cout << "{";
    for (int i = 0; i < int(v.size()); i++) {
      cout << v[i] << ",";
    }
    cout << "\b}";
  } else {
    cout << "{}";
  }
}

// 容器vector中元素的去重
vector<int> unique_element_in_vector(vector<int> v) {
  vector<int>::iterator vector_iterator;
  sort(v.begin(), v.end());
  vector_iterator = unique(v.begin(), v.end());
  if (vector_iterator != v.end()) {
    v.erase(vector_iterator, v.end());
  }
  return v;
}

// 两个vector求交集
vector<int> vectors_intersection(vector<int> v1, vector<int> v2) {
  vector<int> v;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                   back_inserter(v)); // 求交集
  return v;
}

// 两个vector求并集
vector<int> vectors_set_union(vector<int> v1, vector<int> v2) {
  vector<int> v;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  set_union(v1.begin(), v1.end(), v2.begin(), v2.end(),
            back_inserter(v)); // 求交集
  return v;
}

// 判断vector的某一元素是否存在
bool is_element_in_vector(vector<int> v, int element) {
  vector<int>::iterator it;
  it = find(v.begin(), v.end(), element);
  if (it != v.end()) {
    return true;
  } else {
    return false;
  }
}

int main() {
  vector<int> v1, v2, v;
  v1.push_back(22);
  v1.push_back(22);
  v1.push_back(23);
  v2.push_back(23);
  v2.push_back(24);
  cout << "v1是否存在1这个元素?" << is_element_in_vector(v1, 1) << endl;
  cout << "对v1去重:";
  v1 = unique_element_in_vector(v1);
  print_vector(v1);
  cout << endl;
  cout << "求v1与v2的交集:";
  v = vectors_intersection(v1, v2);
  print_vector(v);
  cout << endl;
  cout << "求v1与v2的并集:";
  v = vectors_set_union(v1, v2);
  print_vector(v);
  return 0;
}
