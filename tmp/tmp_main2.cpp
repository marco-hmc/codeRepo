#include <iostream>
#include <map>

template <typename T, unsigned int N>
static constexpr unsigned int arrCount(T (&)[N]) {
  return N;
}

int main() {
  const std::map<int, std::string> myMap = {
      {1, "one"}, {2, "two"}, {3, "three"}};

  // 使用 operator[] 访问元素
  std::cout << "Value at key 2: " << myMap.at(2) << std::endl;

  return 0;
}
