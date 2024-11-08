#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
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

  // `insert_sorted`函数很通用.如果需要其适应不同类型的参数,这样改函数就能处理其他容器所承载的类型,甚至是容器的类似,比如`std::set`/`std::deque`/`std::list`等等.(这里需要注意的是成员函数`lower_bound`与
  // `std::lower_bound`等价,不过成员函数的方式会更加高效,因为其只用于对应的数据集合)

  // ```c++
  // template <typename C, typename T>
  // void insert_sorted(C &v, const T &item)
  // {
  //     const auto insert_pos (lower_bound(begin(v), end(v), item));
  //     v.insert(insert_pos, item);
  // }
  // ```

  void insert_sorted(vector<string> &v, const string &word) {
    const auto insert_pos(lower_bound(begin(v), end(v), word));
    v.insert(insert_pos, word);
  }

  int main() {
    cout << "done" << endl;

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

    {
      vector<string> v{"some",  "random", "words", "without",
                       "order", "aaa",    "yyy"};
      assert(false == is_sorted(begin(v), end(v)));
      sort(begin(v), end(v));
      assert(true == is_sorted(begin(v), end(v)));
      insert_sorted(v, "foobar");
      insert_sorted(v, "zzz");

      for (const auto &w : v) {
        cout << w << " ";
      }
      cout << '\n';
    }
    return 0;
  }
