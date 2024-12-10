#include <atomic>
#include <iostream>
#include <thread>

/*

### 1. 所以原子变量都有 `exchange()` 方法和 `store` 吗？解释一下这两个方法怎么使用？

C++ 标准库中的 `std::atomic` 类提供了多种方法来操作原子变量，其中包括 `exchange()` 和 `store()` 方法。

- **`exchange()` 方法**：
  - 用于将原子变量的当前值替换为新值，并返回旧值。
  - 语法：`atomic_var.exchange(new_value, memory_order)`
  - 示例：
    ```cpp
    std::atomic<int> atomic_var(0);
    int old_value = atomic_var.exchange(1); // 将 atomic_var 的值设置为 1，并返回旧值 0
    ```

- **`store()` 方法**：
  - 用于将新值存储到原子变量中。
  - 语法：`atomic_var.store(new_value, memory_order)`
  - 示例：
    ```cpp
    std::atomic<int> atomic_var(0);
    atomic_var.store(1); // 将 atomic_var 的值设置为 1
    ```

### 2. 为什么 `lock()` 函数中要使用 `while` 循环？会导致忙等待吗？

- **使用 `while` 循环**：
  - `lock()` 函数中的 `while` 循环用于实现自旋锁。自旋锁会不断尝试获取锁，直到成功为止。
  - 代码示例：
    ```cpp
    void lock() {
        while (flag.exchange(true, std::memory_order_relaxed)) {
            // 忙等待
        }
        std::atomic_thread_fence(std::memory_order_acquire);
    }
    ```

- **忙等待**：
  - 是的，`while` 循环会导致忙等待（busy-waiting），即线程在循环中不断检查条件，而不进行任何有意义的工作。
  - 忙等待会消耗 CPU 资源，但在某些情况下（如锁持有时间很短），自旋锁可能比阻塞锁更高效。

### 3. 为什么 `unlock()` 函数中要使用 `std::atomic_thread_fence(std::memory_order_release)`？

- **`std::atomic_thread_fence(std::memory_order_release)`**：
  - 用于确保在释放锁之前，所有先前的内存操作不会被重排序到这个操作之后。
  - 这可以确保在释放锁之前，所有对共享数据的修改都对其他线程可见。
  - 代码示例：
    ```cpp
    void unlock() {
        std::atomic_thread_fence(std::memory_order_release);
        flag.store(false, std::memory_order_relaxed);
    }
    ```

### 4. 解释一下 `std::atomic_thread_fence` 怎么用？

- **`std::atomic_thread_fence`**：
  - 是一个全局内存栅栏，用于控制内存操作的顺序。
  - 它不会对特定的原子变量进行操作，而是对所有内存操作生效。
  - 常用的内存顺序有：
    - `std::memory_order_relaxed`：不进行任何同步或排序操作。
    - `std::memory_order_acquire`：确保后续的内存操作不会被重排序到这个操作之前。
    - `std::memory_order_release`：确保先前的内存操作不会被重排序到这个操作之后。
  - 代码示例：
    ```cpp
    std::atomic<int> atomic_var(0);

    // 确保在获取锁之后的内存操作不会被重排序到获取锁之前
    std::atomic_thread_fence(std::memory_order_acquire);

    // 确保在释放锁之前的内存操作不会被重排序到释放锁之后
    std::atomic_thread_fence(std::memory_order_release);
    ```

希望这些解释对你有所帮助！如果有其他问题，请随时提问。
*/
class mutex {
    std::atomic<bool> flag{false};

  public:
    void lock() {
        while (flag.exchange(true, std::memory_order_relaxed)) {
            ;
        }
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void unlock() {
        std::atomic_thread_fence(std::memory_order_release);
        flag.store(false, std::memory_order_relaxed);
    }
};

int main() {
    int a = 0;
    mutex mtx_a;
    std::thread t1([&]() {
        mtx_a.lock();
        a += 1;
        mtx_a.unlock();
    });
    std::thread t2([&]() {
        mtx_a.lock();
        a += 2;
        mtx_a.unlock();
    });

    t1.join();
    t2.join();

    std::cout << a << '\n';
    return 0;
}
