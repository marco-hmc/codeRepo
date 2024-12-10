#include <atomic>
#include <iostream>
#include <thread>

/*
  1. yield的概念是什么？作用是什么？
    `yield` 是一种控制流操作，用于暂停当前正在执行的线程，并将执行权交还给操作系统的线程调度器。
    这样，操作系统可以选择运行其他线程。
    `yield` 通常用于多线程编程中，以提高线程之间的协作和资源利用率。

    - **让出CPU时间片**：`yield` 让当前线程主动放弃 CPU 时间片，使得其他线程有机会获得执行权。这在某些情况下可以提高系统的响应性和资源利用率。
    - **避免忙等待**：在某些情况下，线程可能会进入忙等待状态（不断循环检查某个条件）。使用 `yield` 可以减少忙等待对 CPU 资源的占用。
    - **提高线程调度的公平性**：通过 `yield`，可以让线程调度器更公平地分配 CPU 时间片，避免某些线程长时间占用 CPU。

  2. yield用在什么场景？
      一般用来检查状态或者条件，状态或者条件不满足的时候，为了避免忙等待就让出。
      但是yield是只让出当前时间片的，如果预期是个长时间的等待，那么就不适合使用yield。可以直接用sleep.

*/

std::atomic<int> foo(0);
std::atomic<int> bar(0);

void set_foo(int x) { foo = x; }

void copy_foo_to_bar() {
    while (foo == 0) {
        std::this_thread::yield();
    }
    bar = static_cast<int>(foo);
}

void print_bar() {
    while (bar == 0) {
        std::this_thread::yield();
    }
    std::cout << "bar: " << bar << '\n';
}

int main() {
    std::thread first(print_bar);
    std::thread second(set_foo, 10);
    std::thread third(copy_foo_to_bar);
    first.join();
    second.join();
    third.join();
    return 0;
}
