#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template <typename Iterator, typename T> struct accumulate_block {
  void operator()(Iterator first, Iterator last, T &result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);

  if (!length) // 1
    return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1) / min_per_thread; // 2

  unsigned long const hardware_threads = std::thread::hardware_concurrency();

  unsigned long const num_threads = // 3
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length / num_threads; // 4

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1); // 5

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size); // 6
    threads[i] = std::thread(            // 7
        accumulate_block<Iterator, T>(), block_start, block_end,
        std::ref(results[i]));
    block_start = block_end; // 8
  }
  accumulate_block<Iterator, T>()(block_start, last,
                                  results[num_threads - 1]); // 9
  std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join)); // 10

  return std::accumulate(results.begin(), results.end(), init); // 11
}

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

// Test case 4: Range with negative elements
void test_negative_elements_range() {
  std::vector<int> nums = {-1, -2, -3, -4, -5};
  int init = 0;
  int result = parallel_accumulate(nums.begin(), nums.end(), init);
  int expected = std::accumulate(nums.begin(), nums.end(), init);
  assert(result == expected);
  std::cout << "Test case 4 passed.\n";
}

int main() {
  test_empty_range();
  test_single_element_range();
  test_multiple_elements_range();
  test_negative_elements_range();
}