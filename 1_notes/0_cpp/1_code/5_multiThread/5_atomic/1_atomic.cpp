#include <atomic>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

namespace identifier_1 {
std::atomic<int> count = {0};

int test_1() {
  std::thread t1([]() { count.fetch_add(1); });
  std::thread t2([]() {
    count++;    // identical to fetch_add
    count += 1; // identical to fetch_add
  });

  t1.join();
  t2.join();
  std::cout << count << '\n';
  return 0;
}
} // namespace identifier_1

namespace identifier_2 {

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x) {
  while (lock_stream.test_and_set()) {
  }
  stream << "thread #" << x << '\n';
  lock_stream.clear();
}

int test_2() {
  std::vector<std::thread> threads;
  for (int i = 1; i <= 10; ++i) {
    threads.emplace_back(append_number, i);
  }
  for (auto &th : threads) {
    th.join();
  }

  std::cout << stream.str();
  return 0;
}

} // namespace identifier_2

/////////////////////////////////////////////////////////////

int main() {
  identifier_1::test_1();
  identifier_2::test_2();
  return 0;
}
