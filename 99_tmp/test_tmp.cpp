#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

// Test case 1: Empty range
void test_empty_range() {
  std::vector<int> nums;
  int init = 0;
  int result = parallel_accumulate(nums.begin(), nums.end(), init);
  assert(result == init);
  std::cout << "Test case 1 passed.\n";
}

// Test case 2: Single element range
void test_single_element_range() {
  std::vector<int> nums = {5};
  int init = 0;
  int result = parallel_accumulate(nums.begin(), nums.end(), init);
  assert(result == init + 5);
  std::cout << "Test case 2 passed.\n";
}

// Test case 3: Range with multiple elements
void test_multiple_elements_range() {
  std::vector<int> nums = {1, 2, 3, 4, 5};
  int init = 10;
  int result = parallel_accumulate(nums.begin(), nums.end(), init);
  int expected = std::accumulate(nums.begin(), nums.end(), init);
  assert(result == expected);
  std::cout << "Test case 3 passed.\n";
}

int main() {
  test_empty_range();
  test_single_element_range();
  test_multiple_elements_range();

  return 0;
}