#include <iostream>
#include <queue>
#include <string>

int main() {
  using item_type = std::pair<int, std::string>;
  std::priority_queue<item_type> q;

  std::initializer_list<item_type> il{
      {1, "dishes"},
      {0, "watch tv"},
      {2, "do homework"},
      {0, "read comics"},
  };
  for (const auto &p : il) {
    q.push(p);
  }
  while (!q.empty()) {
    std::cout << q.top().first << ": " << q.top().second << '\n';
    q.pop();
  }
  std::cout << '\n';
}

// 1. priority_queue如何自定义比较函数
// 2. priority_queue如何构造