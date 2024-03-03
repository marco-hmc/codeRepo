## 数据结构与算法

* vector/list以及map/set这些的数据结构是怎么样的?(连续型内存,类似数组;红黑树)
* 上述结构中插入数据和删除数据的时间复杂度是怎么样的?
* 红黑树是什么样的数据结构?红黑树和B数的区别?
* 
### 1. 算法篇

#### 1.1 二分

- 模板

  - ```c++
    while(left<=right){
        mid = left + (right - left)/ 2; // 等价于(right+left)/2,但是可避免溢出
        if(nums[mid]>target)
            right = mid -1 ; // 因为mid不是，所以可以排除
        else if(num[mid]<target)
            left = mid + 1;
        else
            return mid;
    }
    ```

#### 1.2 



### 2. 数据结构篇

#### 2.1 链表

- 哨兵机制，即设置一个虚拟头结点

  - ```c++
    // link: https://leetcode-cn.com/problems/remove-linked-list-elements/submissions/
    // method1
    class Solution {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            ListNode* preHead = new ListNode(0);
            ListNode* pre = preHead;
            pre->next = head;
            ListNode* cur = head;
            while(cur!=nullptr){
                if(cur->val == val){
                    ListNode* next = cur->next;
                    pre->next = next;
                    cur = cur->next;
                }else{
                    cur = cur->next;
                    pre = pre->next;
                }
            }
            return preHead->next;
        }
    };
    // method2 注意这个方法是不行的
    // 我想不出一个简洁的方式说明，读者自行体会。
    class Solution
    {
    public:
        ListNode* removeElements(ListNode* head, int val) {
            ListNode* pre = new ListNode(0);
            pre->next = head;
            ListNode* cur = head;
            while(cur!=nullptr){
                if(cur->val == val){
                    ListNode* next = cur->next;
                    pre->next = next;
                    cur = cur->next;
                }else{
                    cur = cur->next;
                    pre = pre->next;
                }
            }
            return head;
        }
    };
    ```

#### 2.2 字符串

- 最长公共子序列/最长公共子串

  > s1: cnblogs   s2: belong
  >
  > - 最长公共子序列
  >
  >   - blog
  >
  >   - 用二维数组c\[i]\[j]表示s1[0:i]，s2[0:j]中的最长公共子序列，则可得到状态转移方程
  >
  >     ![image-20220408162843706](https://s2.loli.net/2022/04/08/rc8a9F4LxJzwlIk.png)
  >
  > - 最长公共子串: lo
  >
  >   - lo
  >
  >   - 用二维数组c\[i]\[j]表示s1[0:i]，s2[0:j]中的最长公共子串，则可得到状态转移方程
  >
  >     ![image-20220408163005542](https://s2.loli.net/2022/04/08/y9bDG2CsPTMQdw6.png)
  >
  >     结果为max(c\[i]\[j])

- 最长回文子串

  > - 中心扩散法
  >
  > - 翻转子串，两个子串找最长公共子串



### 99. 奇技淫巧

#### 99.1 vector

- vector去重

  ```c++
  //method1
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  
  //method2
  set<int>s(vec.begin(), vec.end());
  vec.assign(s.begin(), s.end());
  ```

- vector求交集

  ```c++
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
          vector<int> res;
          std::sort(nums1.begin(),nums1.end());
          std::sort(nums2.begin(),nums2.end());        		std::set_intersection(nums1.begin(),nums1.end(),nums2.begin(),nums2.end(),insert_iterator<vector<int>>(res,res.begin()));
          return res;    // res：2，2
  }
  //即函数只执行复制，不是插入！但是模板 insert_iterator 可以将复制转换为插入，可以解决该问题。
  
  set<int>x1,x2,x2;
  //交集
  set_intersection(x1.begin(),x1.end(),x2.begin(),x2.end(),inserter(x,x.begin()));
  //并集
  set_union(x1.begin(),x1.end(),x2.begin(),x2.end(),inserter(x,x.begin()));
  //差集
  set_difference(x1.begin(),x1.end(),x2.begin(),x2.end(),inserter(x,x.begin()));
  
  ```

  

#### 99.2 string

- 类型转换

  ```c++
  // 转字符串
  string str1 = to_string(123456);
  // 字符串转
  int v1 = stoi("123");
  long v2 = stol("111");
  float v2 = stol("1.11");
  double v2 = stol("1.11");
  ```

- 含空格的字符串读取

  ```c++
  // method1
  string s;
  getline(cin, s);
  // 注意如果先cin,再geline，要先清空cin.
  cin>>a;
  cin.ignore(); // 如果没有这个，s1是""
  string s1;
  getline(cin, s1);
  ```

- 字符串查找

  ```c++
  string s1="abcdefg";
  string s2="fg";
  
  if(s1.find(s2) != s1.npos){
      int pos = s1.find(s2);
      cout << s1.substr(pos, s2.size()) << endl;
  }
  ```

  

* 特殊的地方,不允许使用STL容器,自己实现链表或是数组,要写出完整功能,包括构造析构函数.注意边界情况和内存泄漏
