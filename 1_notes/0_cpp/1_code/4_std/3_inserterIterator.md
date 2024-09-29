## 插入迭代器

### 1. concepts
#### 1.1 什么是插入迭代器？

插入迭代器是一种特殊类型的迭代器，用于将元素插入到容器中，而不是替换容器中的现有元素。插入迭代器的主要功能是将元素插入到容器的末尾、开头或指定位置。它们通常与标准库算法一起使用，以便在容器中插入元素。

#### 1.2 插入迭代器有哪些类型？

插入迭代器主要有以下几种类型：

1. **`std::back_insert_iterator`**：
   - 使用 `push_back` 方法将元素插入到容器的末尾。
   - 适用于支持 `push_back` 方法的容器，如 `std::vector`, `std::deque`, 和 `std::list`。

2. **`std::front_insert_iterator`**：
   - 使用 `push_front` 方法将元素插入到容器的开头。
   - 适用于支持 `push_front` 方法的容器，如 `std::deque` 和 `std::list`。

3. **`std::insert_iterator`**：
   - 使用 `insert` 方法将元素插入到容器的指定位置。
   - 适用于支持 `insert` 方法的容器，如 `std::vector`, `std::deque`, `std::list`, 和 `std::set`。

#### 1.3 有什么用途？

插入迭代器的主要用途包括：

1. **与标准库算法一起使用**：
   - 插入迭代器通常与标准库算法（如 `std::copy`, `std::transform`, `std::fill` 等）一起使用，以便将元素插入到容器中。例如，使用 `std::copy` 将一个容器的元素复制到另一个容器的末尾。

2. **简化代码**：
   - 插入迭代器可以简化代码，使代码更具可读性和可维护性。例如，使用 `std::back_inserter` 可以避免手动调用 `push_back` 方法来插入元素。

3. **动态扩展容器**：
   - 插入迭代器允许在运行时动态扩展容器的大小，而不需要预先知道容器的最终大小。例如，使用 `std::back_inserter` 可以在不预先分配空间的情况下将元素插入到 `std::vector` 中。

#### 1.4 如何使用插入迭代器
```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> vec2;
    std::transform(vec.begin(), vec.end(), std::back_inserter(vec2),
                   [](int n) { return n * 2; });
    std::cout << "After back_inserter: ";

    for (int n : vec2) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

如果不使用插入迭代器，就依赖vec有正确的大小。

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> vec2(vec.size());
    std::transform(vec.begin(), vec.end(), vec2.begin(), [](int n) { return n * 2; });

    std::cout << "After transform: ";
    for (int n : vec2) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 2. 代码

插入迭代器的实现是为了与标准库中的一些算法（如 `std::for_each`、`std::transform` 和 `std::copy` 等）配合使用。这些算法的设计理念是支持函数式编程，确保状态的不变性，从而有助于支持 C++17 标准中的并行策略（parallel policy）。

在 C++17 标准中，引入了并行算法的支持，使得开发者可以利用多核处理器的优势来提高程序的性能。插入迭代器在这种情况下尤为重要，因为它们可以确保在并行执行时，数据插入操作是安全且高效的。

为了更好地理解插入迭代器的实现，可以参考 `std::transform` 的实现方式。

#### 2.1 std::transform的实现
```cpp
// 单一输入范围的 `std::transform`
template <typename InputIt, typename OutputIt, typename UnaryOperation>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op) {
    while (first != last) {
        *d_first++ = unary_op(*first++);
    }
    return d_first;
}

// 双输入范围的 `std::transform`
template <typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryOperation>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op) {
    while (first1 != last1) {
        *d_first++ = binary_op(*first1++, *first2++);
    }
    return d_first;
}

```

#### 2.2 std::back_insert_iterator的实现
```c++
#include <iterator>

template <typename Container>
class back_insert_iterator {
protected:
    Container* container;

public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    explicit back_insert_iterator(Container& c) : container(&c) {}

    back_insert_iterator& operator=(const typename Container::value_type& value) {
        container->push_back(value);
        return *this;
    }

    back_insert_iterator& operator=(typename Container::value_type&& value) {
        container->push_back(std::move(value));
        return *this;
    }

    back_insert_iterator& operator*() { return *this; }
    back_insert_iterator& operator++() { return *this; }
    back_insert_iterator& operator++(int) { return *this; }
};

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& c) {
    return back_insert_iterator<Container>(c);
}
```

#### 2.3 总结

简单来说，插入迭代器的实现主要是通过重载 operator= 操作符来实现的。这个操作符会调用容器的 push_back 函数，将元素插入到容器的末尾


### 98. 附录
#### 1. 其他插入迭代器的实现
```c++
// front_insert 插入迭代器
front_insert_iterator& operator=(const typename Container::value_type& value) {
    container->push_front(value);
    return *this;
}

front_insert_iterator& operator=(typename Container::value_type&& value) {
    container->push_front(std::move(value));
    return *this;
}
```

```c++
// insert 插入迭代器
insert_iterator& operator=(const typename Container::value_type& value) {
    iter = container->insert(iter, value);
    ++iter;
    return *this;
}

insert_iterator& operator=(typename Container::value_type&& value) {
    iter = container->insert(iter, std::move(value));
    ++iter;
    return *this;
}
```
