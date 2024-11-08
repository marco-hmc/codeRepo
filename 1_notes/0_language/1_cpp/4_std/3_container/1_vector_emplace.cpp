#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
once_flag callflag;

static void once_print() { cout << '!'; }
static void print(size_t x) {
  std::call_once(callflag, once_print);
  cout << x;
}

int main() {
  vector<thread> v;

  for (size_t i{0}; i < 10; ++i) {
    // if not use emplace_back, will be like
    // thread t(print, i);
    // v.push_back(std::move(t));
    v.emplace_back(print, i);
  }

  for (auto &t : v) {
    t.join();
  }
  cout << '\n';
}