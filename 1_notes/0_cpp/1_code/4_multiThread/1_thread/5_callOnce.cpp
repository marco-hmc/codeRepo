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
    v.emplace_back(print, i);
  }

  for (auto &t : v) {
    t.join();
  }
  cout << '\n';
}

// `std::once_flag`对象在`std::call_once`调用后就不能再被复用了。一旦`std::call_once`使用了某个`std::once_flag`对象，那么这个`std::once_flag`对象就被标记为已调用，无法再次使用。

// 因此，对于每个需要使用`std::call_once`的场景，你都需要一个新的`std::once_flag`对象。如果你尝试使用已经被`std::call_once`调用过的`std::once_flag`对象，那么`std::call_once`将不会执行传入的函数或代码块。
