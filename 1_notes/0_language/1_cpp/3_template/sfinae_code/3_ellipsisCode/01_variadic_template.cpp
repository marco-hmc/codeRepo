## 变参模板（Variadic Template）

* C++11 引入了 [sizeof...](https://en.cppreference.com/w/cpp/language/sizeof...) 在编译期计算参数包中的元素数，C++17 引入了 if constexpr 判断编译期值，编译期结果为 true 才会实例化代码

```cpp
#include <iostream>
#include <string>
#include <utility>

namespace jc {
    template <typename T, typename... Args>
    void print(const T& t, Args&&... args) {
        std::cout << t << std::endl;
        if constexpr (sizeof...(args) >
                      0) {  // 不能用 if，因为零长包也会实例化代码
            print(std::forward<Args>(args)...);  // 当条件满足时才实例化
        }
    }

}  // namespace jc

int main() {
    jc::print(3.14, 42, std::string{"hello"}, "world"); }
```
