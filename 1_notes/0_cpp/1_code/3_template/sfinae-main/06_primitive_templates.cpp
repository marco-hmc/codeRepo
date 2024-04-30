#include <iostream>

template <int S> int f() { return S; }

template <int A, int B> constexpr int sum() { return A + B; }

int main() {
  std::cout << f<2>() << "\n";
  std::cout << f<256>() << "\n";
  std::cout << f<10>() << "\n";

  std::cout << sum<1, 1>() << "\n";
  std::cout << sum<2, 3>() << "\n";
  std::cout << sum<0, -500>() << "\n";
  // std::cout << sum<0, sum<40, 40>>() << "\n";
  constexpr int temp = sum<40, 40>();
  std::cout << sum<0, temp>() << "\n";
  return 0;
}