#include <iostream>

[[deprecated("This function is deprecated. Use newFunction() instead.")]] void
oldFunction() {
  std::cout << "This is the old function." << std::endl;
}

[[nodiscard]] int calculate() { return 42; }

int main() {
  oldFunction(); // Generates a deprecation warning
  int result =
      calculate(); // Generates a warning if the return value is ignored

  return 0;
}
