#include <atomic>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

namespace identifier_1 {
std::atomic<int> count = {0};

int test_1() {
    std::thread t1([]() { count.fetch_add(1); });
    std::thread t2([]() {
        count++;     // identical to fetch_add
        count += 1;  // identical to fetch_add
    });

    t1.join();
    t2.join();
    std::cout << count << '\n';
    return 0;
}
}  // namespace identifier_1

namespace identifier2 {
std::atomic<int> foo(0);

void set_foo(int x) { foo.store(x, std::memory_order_relaxed); }

void print_foo() {
    int x = 0;
    do {
        x = foo.load(std::memory_order_relaxed);
    } while (x == 0);
    std::cout << "foo: " << x << '\n';
}

void test() {
    std::thread first(print_foo);
    std::thread second(set_foo, 10);
    first.join();
    second.join();
}
}  // namespace identifier2

/////////////////////////////////////////////////////////////

int main() {
    identifier_1::test_1();
    identifier2::test();
    return 0;
}

/*
  1. 原子变量的store和load操作是什么意思，有什么用？
  * store操作：将一个值存储到原子变量中，可以指定内存顺序(memory order)。
  * load操作：从原子变量中加载一个值，可以指定内存顺序(memory order)。
  * store和load操作是原子变量的基本操作，用于读写原子变量的值，可以保证操作的原子性和内存顺序。
*/