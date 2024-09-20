#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

struct Node { int value; Node* next; };
std::atomic<Node*> list_head (nullptr);

void append(int val) {
  Node *oldHead = list_head;
  Node *newNode = new Node{val, oldHead};

  while (!list_head.compare_exchange_weak(oldHead, newNode)) {
    newNode->next = oldHead;
  }
}

void printFunc() {
  Node *it;
  while (it = list_head) {
    list_head = it->next;
    delete it;
  }
}

int main() {

  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(append, i);
  }
  for (auto &th : threads) {
    th.join();
  }

  for (Node *it = list_head; it != nullptr; it = it->next) {
    std::cout << ' ' << it->value;
  }
  std::cout << '\n';

  printFunc();
  return 0;
}

/*
1. compare_exchange_weak怎么用的？
`compare_exchange_weak` 是 C++ 标准库中 `std::atomic`
类提供的一种原子操作，用于实现无锁编程。它的主要作用是比较并交换值，通常用于实现复杂的同步原语，如无锁队列、无锁栈等。

### 函数签名

```cpp
bool compare_exchange_weak(T& expected, T desired, std::memory_order order =
std::memory_order_seq_cst) noexcept; bool compare_exchange_weak(T& expected, T
desired, std::memory_order success, std::memory_order failure) noexcept;
```

### 参数解释

- `expected`：一个引用参数，表示预期的值。如果当前原子对象的值与 `expected`
相等，则将其更新为 `desired`；否则，将当前原子对象的值写入 `expected`。
- `desired`：表示希望设置的新值。
- `order`：内存顺序，默认为 `std::memory_order_seq_cst`，表示顺序一致性。
- `success` 和 `failure`：分别表示成功和失败时的内存顺序。

### 返回值

- 如果当前原子对象的值与 `expected` 相等，则返回 `true`，并将原子对象的值更新为
`desired`。
- 如果当前原子对象的值与 `expected` 不相等，则返回
`false`，并将当前原子对象的值写入 `expected`。

### 使用示例

以下是一个使用 `compare_exchange_weak` 的示例，展示了如何在无锁栈中使用该操作：

```cpp
#include <atomic>
#include <iostream>

struct Node {
    int value;
    Node* next;
};

class LockFreeStack {
public:
    LockFreeStack() : head(nullptr) {}

    void push(int value) {
        Node* new_node = new Node{value, nullptr};
        Node* old_head = head.load();
        do {
            new_node->next = old_head;
        } while (!head.compare_exchange_weak(old_head, new_node));
    }

    bool pop(int& value) {
        Node* old_head = head.load();
        do {
            if (old_head == nullptr) {
                return false; // 栈为空
            }
        } while (!head.compare_exchange_weak(old_head, old_head->next));
        value = old_head->value;
        delete old_head;
        return true;
    }

private:
    std::atomic<Node*> head;
};

int main() {
    LockFreeStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    int value;
    while (stack.pop(value)) {
        std::cout << "Popped: " << value << std::endl;
    }

    return 0;
}
```

### 解释

1. **初始化栈**：`LockFreeStack` 类中，`head` 是一个原子指针，指向栈顶节点。
2. **push 操作**：
   - 创建一个新节点 `new_node`。
   - 使用 `compare_exchange_weak` 尝试将 `new_node` 插入栈顶。如果 `head` 的值在
`compare_exchange_weak` 调用期间被其他线程修改，则 `old_head`
会被更新为新的栈顶，循环继续，直到插入成功。
3. **pop 操作**：
   - 使用 `compare_exchange_weak` 尝试将 `head` 更新为下一个节点。如果 `head`
的值在 `compare_exchange_weak` 调用期间被其他线程修改，则 `old_head`
会被更新为新的栈顶，循环继续，直到更新成功。
   - 如果栈为空，返回 `false`。

### 总结

- `compare_exchange_weak`
是一种原子操作，用于比较并交换值，常用于实现无锁数据结构。
- 它通过比较当前值与预期值，如果相等则更新为新值，否则更新预期值为当前值。
- 该操作在实现复杂的同步原语时非常有用，能够避免锁的使用，提高并发性能。

*/