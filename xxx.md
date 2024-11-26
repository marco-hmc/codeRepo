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