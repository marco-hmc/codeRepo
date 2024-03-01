#include <numeric>

template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first) {
  const auto values = {first, args...};
  return std::accumulate(values.begin(), values.end(), First{0});
}

int main() {
  sum(1, 2, 3, 4, 5); // 15
  sum(1, 2, 3);       // 6
  sum(1.5, 2.0, 3.7); // 7.2
  return 0;
}
