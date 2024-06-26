## 

### 1. 静态绑定和虚函数
```c++
#include <iostream>

struct A {
    virtual void foo (int a = 1) {
        std::cout << "A" << a;
    }
};

struct B : A {
    virtual void foo (int a = 2) {
        std::cout << "B" << a;
    }
};

int main () {
    A *b = new B;
    b->foo();
}
```

### 2. 输出
```c++
#include <algorithm>
#include <iostream>

int main() {
  int x = 10;
  int y = 10;

  const int &max = std::max(x, y);
  const int &min = std::min(x, y);

  x = 11;
  y = 9;

  std::cout << max << min;
}
```

### 3. 空模板参数
```c++
template <typename... Ts> struct X {
  X(Ts... args) : Var(0, args...) {}
  int Var;
};

int main() { X<> x; }
```
是否可通过编译？是否可运行？

### 4. std::string不常见的构造
```c++
#include <iostream>
#include <string>

int main() {
  using namespace std::string_literals;
  std::string s1("hello world", 5);
  std::string s2("hello world"s, 5);

  std::cout << s1 << s2;
}
```

### 4. 数组和指针的大小
```c++
#include <iostream>
using namespace std;

size_t get_size_1(int *arr) { return sizeof arr; }
size_t get_size_2(int arr[]) { return sizeof arr; }
size_t get_size_3(int (&arr)[10]) { return sizeof(arr); }

int main() {
  int array[10];
  // Assume sizeof(int*) != sizeof(int[10])
  cout << (sizeof(array) == get_size_1(array));
  cout << (sizeof(array) == get_size_2(array));
  cout << (sizeof(array) == get_size_3(array));
}
```

### 5. 函数声明陷阱
```c++
#include <iostream>
struct X {
  X() { std::cout << "X"; }
};

int main() { X x(); }
```