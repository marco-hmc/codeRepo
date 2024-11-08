#include <iostream>
#include <typeinfo>

namespace jc {

template <typename T>
class A {
    // 类作用域内的 A 是注入类名，等价于 A<T>
    friend std::ostream& operator<<(std::ostream& os, const A& rhs) {
        return os << "A<" << typeid(T).name() << "> = " << rhs.n;
    }

    friend void f() {}

   private:
    int n = 0;
};

}  // namespace jc

// 由于函数被调用时才实例化，如果不调用实例化时会出错的函数，代码也能通过编译
int main() {
    jc::A<void> a;  // 实例化 operator<<(std::ostream&, const A<void>&) 和 f()
    std::cout << a;  // A<void> = 0
    // jc::A<int> b;    // 错误：第二次实例化 f()，重定义
}