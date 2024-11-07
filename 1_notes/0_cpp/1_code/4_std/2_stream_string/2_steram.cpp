#include <iostream>
#include <sstream>
#include <string>


int main() {
  std::string str = "123 456";
  std::istringstream iss(str);

  int a, b;
  iss >> a >> b;

  std::cout << "a: " << a << ", b: " << b << '\n';

  return 0;
}