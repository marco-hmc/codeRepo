#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
void original_method() {
  std::vector<int> numbers = {1, 2, 3, 4, 2, 5, 2, 6, 7, 2};
  int target = 2;

  // 使用循环逐个删除目标元素
  for (auto it = numbers.begin(); it != numbers.end();) {
    if (*it == target) {
      it = numbers.erase(it);
    } else {
      ++it;
    }
  }

  // 输出移除后的结果
  for (int num : numbers) {
    std::cout << num << " ";
  }
}

void erase_remove_trick() {
  std::vector<int> numbers = {1, 2, 3, 4, 2, 5, 2, 6, 7, 2};

  // 使用 std::remove 将所有的 2 移到末尾,并返回新的范围末尾
  auto new_end = std::remove(numbers.begin(), numbers.end(), 2);

  // 使用 std::vector::erase 删除从新范围末尾到原范围末尾的元素
  numbers.erase(new_end, numbers.end());

  // 输出移除后的结果
  for (int num : numbers) {
    std::cout << num << " ";
  }
}

void test_1() {
  original_method();
  erase_remove_trick();
}

void test_2() {
  vector<int> v{1, 2, 3, 2, 5, 2, 6, 2, 4, 8};
  const auto new_end(remove(begin(v), end(v), 2));
  v.erase(new_end, end(v));
  for (auto i : v) {
    cout << i << ", ";
  }
  cout << '\n';
  const auto odd([](int i) { return i % 2 != 0; });
  v.erase(remove_if(begin(v), end(v), odd), end(v));
  v.shrink_to_fit();
  for (auto i : v) {
    cout << i << ", ";
  }
  cout << '\n';
}

int main() {
  test_1();
  test_2();
  return 0;
}
