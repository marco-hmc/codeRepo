#include <functional>
#include <iostream>

int main() {
  std::less<int> less_than;

  int a = 5;
  int b = 10;

  if (less_than(a, b)) {
    std::cout << "a is less than b" << std::endl;
  } else {
    std::cout << "a is not less than b" << std::endl;
  }

  return 0;
}
