## [Concepts](https://en.cppreference.com/w/cpp/concepts)

* C++20 可以用 concepts 约束类型，代码更简洁

```cpp
template <typename T>
concept Dereferenceable = requires(T x) {
  *x;
};

template <typename T>
  requires Dereferenceable<T>
void f(T& i) {
  *i = 0;
}

/* 等价写法
 * template <typename T>
 *   requires requires(T x) { *x; }
 * void f(T& i) {
 *   *i = 0;
 * }
 */

int main() {
  int i = 42;
  f(i);  // 未满足关联约束
}
```
