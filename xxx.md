### 虚函数实战案例

#### 初始代码

```cpp
int sum(vector<int> v) {
    int res = 0;
    for (int i = 0; i < v.size(); i++) {
        res = res + v[i];
    }
    return res;
}

int product(vector<int> v) {
    int res = 1;
    for (int i = 0; i < v.size(); i++) {
        res = res * v[i];
    }
    return res;
}
```

#### 抽象公共部分

```cpp
int reduce(vector<int> v) {
    int res = ???;            // sum 时这里是 0，product 时这里是 1
    for (int i = 0; i < v.size(); i++) {
        res = res ??? v[i];   // sum 时这里是 +，product 时这里是 *
    }
    return res;
}
```

#### 使用虚函数

```cpp
struct Reducer {
    virtual int init() = 0;
    virtual int add(int a, int b) = 0;
};

int reduce(vector<int> v, Reducer *reducer) {
    int res = reducer->init();
    for (int i = 0; i < v.size(); i++) {
        res = reducer->add(res, v[i]);
    }
    return res;
}
```

#### 实现具体策略

```cpp
struct SumReducer : Reducer {
    int init() override {
        return 0;
    }

    int add(int a, int b) override {
        return a + b;
    }
};

struct ProductReducer : Reducer {
    int init() override {
        return 1;
    }

    int add(int a, int b) override {
        return a * b;
    }
};
```

#### 使用策略模式

```cpp
reduce(v, new SumReducer());     // 等价于之前的 sum(v)
reduce(v, new ProductReducer()); // 等价于之前的 product(v)
```

### 多重策略

#### 修改 reduce 函数以支持不同输入源

```cpp
int reduce(Reducer *reducer) {
    int res = reducer->init();
    while (true) {
        int tmp;
        cin >> tmp;
        if (tmp == -1) break;
        res = reducer->add(res, tmp);
    }
    return res;
}
```

#### 抽象输入源

```cpp
struct Inputer {
    virtual optional<int> fetch() = 0;
};

int reduce(Inputer *inputer, Reducer *reducer) {
    int res = reducer->init();
    while (auto tmp = inputer->fetch()) {
        res = reducer->add(res, *tmp);
    }
    return res;
}
```

#### 实现具体输入源

```cpp
struct CinInputer : Inputer {
    optional<int> fetch() override {
        int tmp;
        cin >> tmp;
        if (tmp == -1)
            return nullopt;
        return tmp;
    }
};

struct VectorInputer : Inputer {
    vector<int> v;
    int pos = 0;

    VectorInputer(vector<int> v) : v(v) {}
    
    optional<int> fetch() override {
        if (pos == v.size())
            return nullopt;
        return v[pos++];
    }
};
```

#### 使用不同输入源和策略

```cpp
reduce(new CinInputer(), new SumReducer());
reduce(new VectorInputer(v), new SumReducer());
reduce(new CinInputer(), new ProductReducer());
reduce(new VectorInputer(v), new ProductReducer());
```

### 适配器模式

#### 实现适配器

```cpp
struct StopInputerAdapter : Inputer {
    Inputer *inputer;
    int stopMark;

    StopInputerAdapter(Inputer *inputer, int stopMark)
        : inputer(inputer), stopMark(stopMark) {}

    optional<int> fetch() override {
        auto tmp = inputer->fetch();
        if (tmp == stopMark)
            return nullopt;
        return tmp;
    }
};
```

#### 使用适配器

```cpp
reduce(new StopInputerAdapter(new CinInputer(), -1), new SumReducer());
reduce(new StopInputerAdapter(new VectorInputer(v), -1), new SumReducer());
reduce(new VectorInputer(v), new SumReducer());
```

### 过滤器模式

#### 实现过滤器

```cpp
struct FilterStrategy {
    virtual bool shouldPass(int value) = 0;
};

struct FilterStrategyAbove : FilterStrategy {
    int threshold;

    FilterStrategyAbove(int threshold) : threshold(threshold) {}

    bool shouldPass(int value) override {
        return value > threshold;
    }
};

struct FilterStrategyBelow : FilterStrategy {
    int threshold;

    FilterStrategyBelow(int threshold) : threshold(threshold) {}

    bool shouldPass(int value) override {
        return value < threshold;
    }
};

struct FilterInputerAdapter : Inputer {
    Inputer *inputer;
    FilterStrategy *strategy;

    FilterInputerAdapter(Inputer *inputer, FilterStrategy *strategy)
        : inputer(inputer), strategy(strategy) {}

    optional<int> fetch() override {
        while (true) {
            auto tmp = inputer->fetch();
            if (!tmp.has_value()) {
                return nullopt;
            }
            if (strategy->shouldPass(*tmp)) {
                return tmp;
            }
        }
    }
};
```

#### 组合过滤策略

```cpp
struct FilterStrategyAnd : FilterStrategy {
    FilterStrategy *a;
    FilterStrategy *b;

    FilterStrategyAnd(FilterStrategy *a, FilterStrategy *b)
        : a(a), b(b) {}

    bool shouldPass(int value) override {
        return a->shouldPass(value) && b->shouldPass(value);
    }
};
```

#### 使用过滤器和适配器

```cpp
reduce(
    new FilterInputerAdapter(
        new StopInputerAdapter(
            new CinInputer(),
            -1
        ),
        new FilterStrategyAnd(
            new FilterStrategyAbove(0),
            new FilterStrategyBelow(100)
        )
    ),
    new SumReducer()
);
```

### 总结

通过使用策略模式、适配器模式和过滤器模式，可以实现灵活、可扩展的代码设计，满足单一职责原则、开闭原则和依赖倒置原则。这样设计的代码更易于维护和扩展。


这段文字讨论了在并发编程中使用同步和临界区（critical section）时的一些注意事项。以下是对这段文字的详细解释：

### 同步和临界区

在并发编程中，同步是指协调多个线程或进程的执行，以确保它们不会同时访问共享资源，从而避免数据竞争和不一致性。临界区是指一段代码，这段代码在任何时候只能由一个线程执行，以保护共享资源。

### 关键点

1. **使用临界区减少伪共享**：
   - 伪共享（false sharing）是指多个线程访问不同的数据，但这些数据位于同一个缓存行中，导致缓存一致性协议频繁触发，从而降低性能。
   - 使用临界区可以减少伪共享，因为临界区确保同一时间只有一个线程访问共享资源，从而避免了多个线程同时访问同一个缓存行。

2. **不要在紧密循环中放置临界区**：
   - 在紧密循环（tight loop）中放置临界区会导致串行化（serialization），即多个线程无法并行执行，而是必须一个接一个地进入临界区。
   - 这种做法会显著降低并发性能，因为线程需要等待其他线程退出临界区才能继续执行。

### 示例

以下是一个示例，展示了如何使用临界区保护共享资源，同时避免在紧密循环中放置临界区：

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;
int shared_resource = 0;

void increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 避免在紧密循环中放置临界区
        std::lock_guard<std::mutex> lock(mtx);
        ++shared_resource;
    }
}

int main() {
    const int num_threads = 4;
    const int iterations = 1000;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment, iterations);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value of shared_resource: " << shared_resource << std::endl;
    return 0;
}
```

### 解释

1. **定义共享资源和互斥锁**：
   - `std::mutex mtx;`：定义一个互斥锁，用于保护共享资源。
   - `int shared_resource = 0;`：定义一个共享资源。

2. **定义增量函数**：
   - `void increment(int iterations)`：定义一个函数，接受迭代次数作为参数。
   - 在循环中使用 `std::lock_guard<std::mutex> lock(mtx);` 保护对共享资源的访问，确保同一时间只有一个线程可以修改 `shared_resource`。

3. **创建和启动线程**：
   - 创建多个线程，每个线程执行 `increment` 函数。
   - 使用 `threads.emplace_back(increment, iterations);` 将线程添加到线程向量中。

4. **等待线程完成**：
   - 使用 `t.join();` 等待所有线程完成执行。

5. **输出共享资源的最终值**：
   - 输出 `shared_resource` 的最终值，确保所有线程正确地完成了增量操作。

### 总结

这段文字强调了在并发编程中使用临界区时需要注意的两个关键点：使用临界区减少伪共享，但不要在紧密循环中放置临界区，以避免串行化和性能下降。通过合理地使用临界区，可以提高并发程序的性能和可靠性。