#include <atomic>
#include <iostream>
#include <thread>

/*
  1. 原子变量的store和load操作是什么意思，有什么用？
    * store操作：将一个值存储到原子变量中，可以指定内存顺序(memory order)。
    * load操作：从原子变量中加载一个值，可以指定内存顺序(memory order)。
    * fetch_add操作：原子地将一个值加到原子变量中，返回原子变量的旧值。

    这些操作和相关运算符的操作本质是一直的，只是函数的方式可以指定内存徐，而运算符的方式是默认的内存顺序（最安全的）。
*/

namespace identifier1 {
    std::atomic<int> count = {0};

    int test_1() {
        std::thread t1([]() { count.fetch_add(1); });
        std::thread t2([]() {
            count++;     // same as count.fetch_add(1)
            count += 1;  // same as count.fetch_add(1)
        });

        t1.join();
        t2.join();
        std::cout << count << '\n';
        return 0;
    }
}  // namespace identifier1

namespace identifier2 {
    std::atomic<int> foo(0);

    void set_foo(int x) {
        foo.store(x, std::memory_order_relaxed);  // 等价于 foo = x;
    }

    void print_foo() {
        int x = 0;
        do {
            x = foo.load(std::memory_order_relaxed);  // 等价于 x = foo;
        } while (x == 0);
        std::cout << "foo: " << x << '\n';
    }

    void test_2() {
        std::thread first(print_foo);
        std::thread second(set_foo, 10);
        first.join();
        second.join();
    }
}  // namespace identifier2

/////////////////////////////////////////////////////////////

int main() {
    identifier1::test_1();
    identifier2::test_2();
    return 0;
}
