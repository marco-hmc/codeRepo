## memory_order_consume
### 数据依赖性和内存顺序

在多线程编程中，数据依赖性意味着一个操作的结果被另一个操作使用。例如，如果一个变量的值依赖于另一个变量的值，那么这两个操作之间就存在数据依赖性。

`std::memory_order_consume` 确保在同一线程中，所有依赖于加载操作结果的后续操作不会被重排序到加载操作之前。这意味着，如果一个操作读取了一个原子变量，并且后续的操作依赖于这个读取的结果，那么这些操作的顺序将被强制保持。

### 示例代码

以下是一个示例代码，展示了 `std::memory_order_consume` 的使用：

```cpp
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int*> ptr;
int data;

void producer() {
    int* p = new int(42);
    data = 100; // 写入数据
    ptr.store(p, std::memory_order_release); // 发布指针
}

void consumer() {
    int* p;
    while (!(p = ptr.load(std::memory_order_consume))) {
        // 等待指针被发布
    }
    // 由于 memory_order_consume，以下操作不会被重排序到 ptr.load 之前
    std::cout << "Data: " << data << ", *p: " << *p << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
```

### 解释

1. **生产者线程 (`producer`)**：
   - 创建一个新的整数指针 `p`，指向值为 42 的整数。
   - 将 `data` 设置为 100。
   - 使用 `std::memory_order_release` 将指针 `p` 存储到原子变量 `ptr` 中。这一步确保在发布指针之前，所有对 `data` 的写入操作都已经完成。

2. **消费者线程 (`consumer`)**：
   - 不断尝试从原子变量 `ptr` 中加载指针 `p`，直到成功。
   - 使用 `std::memory_order_consume` 加载指针 `p`。这确保了所有依赖于 `p` 的操作（如读取 `data` 和解引用 `p`）不会被重排序到加载操作之前。
   - 打印 `data` 和 `*p` 的值。

### 总结

`std::memory_order_consume` 确保在同一线程中，所有依赖于加载操作结果的后续操作不会被重排序到加载操作之前。这对于确保数据依赖性非常重要，因为它保证了在加载操作之后的所有操作都能看到正确的结果。在上面的示例中，消费者线程在加载指针 `p` 之后，能够正确地读取 `data` 和解引用 `p`，因为这些操作不会被重排序到加载操作之前。