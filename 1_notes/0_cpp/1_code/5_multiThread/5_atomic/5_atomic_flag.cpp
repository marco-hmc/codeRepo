#include <atomic>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

namespace identifier1 {
std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x) {
    while (lock_stream.test_and_set()) {
    }
    stream << "thread #" << x << '\n';
    lock_stream.clear();
}

void test_1() {
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i) {
        threads.emplace_back(append_number, i);
    }
    for (auto &th : threads) {
        th.join();
    }

    std::cout << stream.str();
}
}  // namespace identifier1

int main() {
    identifier1::test_1();
    return 0;
}

/*
### 1. `atomic_flag` 和一般的 `atomic` 有什么区别？

- **`atomic_flag`**：
  - 是最简单的原子类型，只能表示 `true` 或 `false`。
  - 适用于需要简单标志位的场景。
  - 提供了更高效的原子操作，因为它不支持复杂的操作。

- **一般的 `atomic`**：
  - 是模板类，可以表示各种类型的原子变量，如 `int`、`bool`、`float` 等。
  - 支持更多的原子操作，如加减、交换、比较交换等。
  - 适用于需要对各种类型进行原子操作的场景。

### 2. `atomic_flag` 的初始化方式是什么？常见的成员函数有哪些？

- **初始化方式**：
  - `atomic_flag` 可以通过 `ATOMIC_FLAG_INIT` 宏进行初始化。
  - 也可以使用默认构造函数进行初始化。

  ```cpp
  std::atomic_flag flag = ATOMIC_FLAG_INIT;
  std::atomic_flag flag2;
  ```

- **常见的成员函数**：
  -[`test_and_set()`]：设置标志位为 `true`，并返回之前的值。
    用于设置atomic_flag对象的值为true，并返回之前的值。
    如果之前的值为true，则返回true，否则返回false。
  -[`clear()`]：清除标志位，将其设置为 `false`。

*/