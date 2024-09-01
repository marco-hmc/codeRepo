#include <iostream>
#include <string>
#include <variant>

struct CustomType {
  int value;
};

int main() {
  std::variant<int, float, std::string, CustomType> myVariant;

  // Store an integer
  myVariant = 42;
  std::cout << "Value: " << std::get<int>(myVariant) << '\n';

  // Store a float
  myVariant = 3.14f;
  std::cout << "Value: " << std::get<float>(myVariant) << '\n';

  // Store a string
  myVariant = std::string("Hello, world!");
  std::cout << "Value: " << std::get<std::string>(myVariant) << '\n';

  // Store a custom type
  CustomType customObj{100};
  myVariant = customObj;
  std::cout << "Value: " << std::get<CustomType>(myVariant).value << '\n';

  return 0;
}
