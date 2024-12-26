## 浅实例化（Shallow Instantiation）

### 一种简单的减少报错信息长度的方式是提前使用参数

```cpp
template <typename T>
void f1(T& i) {
  *i = 0;  // 假设 T 为指针类型
}

template <typename T>
void f2(T& i) {
  f1(i);
}

template <typename T>
void f3(typename T::Type i) {
  f2(i);
}

template <typename T>
void f4(const T&) {
  class ShallowChecks {  // 未调用，不影响运行期
    static void deref(typename T::Type p) { *p; }
  };
  typename T::Type i = 42;
  f3<T>(i);
}

struct A {
  using Type = int;
};

int main() {
  f4(A{});  // 实例化 f4<A>(const A&) 时检测到错误
}

/*
 * error C2100: 非法的间接寻址
 * message : 查看对正在编译的函数 模板 实例化“void f4<A>(const T &)”的引用
 *         with
 *         [
 *             T=A
 *         ]
 */
```

## 原型（Archetype）

### 模板的一个挑战是确保满足特定约束的实参都能通过编译，为了测试满足要求的模板参数，引入原型的概念。原型是用户定义的类，以尽可能小的方式来满足模板大多数要求，而不提供任何外来的操作

```cpp
// 要求 T 是可比较类型
template <typename T>
int find(const T* a, int n, const T& v) {
  int i = 0;
  while (i != n && a[i] != v) {
    ++i;
  }
  return i;
}

struct EqualityComparable {};

struct ConvertibleToBool {
  operator bool() const { return true; }  // 提供本类型到 bool 的隐式转换
};

ConvertibleToBool  // 返回类型要求能转换为 bool
operator==(const EqualityComparable&, const EqualityComparable&) {
  return ConvertibleToBool{};
}

// 实例化 find<EqualityComparable>
template int find(const EqualityComparable*, int, const EqualityComparable&);

int main() {}
```

### 实例化将失败，改用 `operator==` 比较即可解决此问题

```cpp
template <typename T>
int find(const T* a, int n, const T& v) {
  int i = 0;
  while (i != n && !(a[i] == v)) {
    ++i;
  }
  return i;
}
```

### 但这又在无意中对结果使用了 `operator!`，如果要发现这点，在 ConvertibleToBool 中禁用 `operator!` 即可，当其被使用时将报错

```cpp
struct ConvertibleToBool {
  operator bool() const { return true; }
  bool operator!() = delete;
};
```

### 可以再对原型做其他扩展，比如禁用 `operator&&` 和 `operator||` 来找出其他的一些模板定义中的问题

## 跟踪程序（Tracer）

### 以上都是编译或链接时的 bug，更大的挑战是确保程序在运行期表现正确
### Tracer 是一个用户定义的类，它能用作要测试的模板的实参。通常 tracer 也是一个原型，但包含一些额外的信息。下面是一个用于测试 [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort) 的 tracer，它提供 [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort) 需要的功能（比如 `operator==` 和 `operator>`），并给出算法开销的直观结果，但不揭示排序模板的正确性

```cpp
#include <algorithm>
#include <iostream>

class SortTracer {
 public:
  static long creations() { return n_created; }
  static long destructions() { return n_destroyed; }
  static long assignments() { return n_assigned; }
  static long comparisons() { return n_compared; }
  static long max_live() { return n_max_live; }

 public:
  SortTracer(int v = 0) : value(v), generation(1) {
    ++n_created;
    update_max_live();
    std::cerr << "SortTracer #" << n_created << ", created generation "
              << generation << " (total: " << n_created - n_destroyed << ")\n";
  }

  SortTracer(const SortTracer& rhs)
      : value(rhs.value), generation(rhs.generation + 1) {
    ++n_created;
    update_max_live();
    std::cerr << "SortTracer #" << n_created << ", copied as generation "
              << generation << " (total: " << n_created - n_destroyed << ")\n";
  }

  ~SortTracer() {
    ++n_destroyed;
    update_max_live();
    std::cerr << "SortTracer generation " << generation
              << " destroyed (total: " << n_created - n_destroyed << ")\n";
  }

  SortTracer& operator=(const SortTracer& rhs) {
    ++n_assigned;
    std::cerr << "SortTracer assignment #" << n_assigned << " (generation "
              << generation << " = " << rhs.generation << ")\n";
    value = rhs.value;
    return *this;
  }

  friend bool operator<(const SortTracer& lhs, const SortTracer& rhs) {
    ++n_compared;
    std::cerr << "SortTracer comparison #" << n_compared << " (generation "
              << lhs.generation << " < " << rhs.generation << ")\n";
    return lhs.value < rhs.value;
  }

  int val() const { return value; }

 private:
  int value;                           // integer value to be sorted
  int generation;                      // generation of this tracer
  inline static long n_created = 0;    // number of constructor calls
  inline static long n_destroyed = 0;  // number of destructor calls
  inline static long n_assigned = 0;   // number of assignments
  inline static long n_compared = 0;   // number of comparisons
  inline static long n_max_live = 0;   // maximum of existing objects

  // recompute maximum of existing objects
  static void update_max_live() {
    if (n_created - n_destroyed > n_max_live) {
      n_max_live = n_created - n_destroyed;
    }
  }
};

int main() {
  SortTracer input[] = {7, 3, 5, 6, 4, 2, 0, 1, 9, 8};

  // 打印初始值
  for (int i = 0; i < 10; ++i) {
    std::cerr << input[i].val() << ' ';
  }
  std::cerr << '\n';

  // 记录初始条件
  long created_at_start = SortTracer::creations();
  long max_live_at_start = SortTracer::max_live();
  long assigned_at_start = SortTracer::assignments();
  long compared_at_start = SortTracer::comparisons();

  // 执行
  std::cerr << "---[ Start std::sort() ]--------------------\n";
  std::sort<>(&input[0], &input[9] + 1);
  std::cerr << "---[ End std::sort() ]----------------------\n";

  // 检查结果
  for (int i = 0; i < 10; ++i) {
    std::cerr << input[i].val() << ' ';
  }
  std::cerr << "\n\n";

  // final report
  std::cerr << "std::sort() of 10 SortTracer's was performed by:\n"
            << SortTracer::creations() - created_at_start
            << " temporary tracers\n"
            << "up to " << SortTracer::max_live()
            << " tracers at the same time (" << max_live_at_start
            << " before)\n"
            << SortTracer::assignments() - assigned_at_start << " assignments\n"
            << SortTracer::comparisons() - compared_at_start
            << " comparisons\n\n";
}
```