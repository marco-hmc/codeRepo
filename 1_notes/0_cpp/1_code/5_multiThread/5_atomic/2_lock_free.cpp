#include <atomic>
#include <iostream>

struct A {
    int a[100];
};
struct B {
    int x, y;
};

int main() {
    std::cout << std::boolalpha << "std::atomic<A> is lock free? "
              << std::atomic<A>{}.is_lock_free() << '\n'
              << "std::atomic<B> is lock free? "
              << std::atomic<B>{}.is_lock_free() << '\n';
    return 0;
}

/*
  1. 自定义原子类型哪些是 lock-free 的，哪些不是？
  * 基本数据类型：大多数平台上的基本数据类型（如int、float、double等）通常是无锁的。
  * 小型结构体：包含少量基本数据类型的结构体，通常也是无锁的，前提是它们的大小和对齐方式适合平台的原子操作。
  * 大型结构体和数组：包含大量数据或复杂数据结构的类型，通常不是无锁的，因为它们的大小超出了平台原子操作的能力。

  注意：std::atomic<T> 的 is_lock_free() 方法返回 true 并不意味着 std::atomic<T>
  的所有操作都是无锁的，只是表示 std::atomic<T> 的 lock-free 特性是平台支持的。

  2. 有锁和无锁的区别是什么
  与锁相比，无锁编程具有以下优点：

  无锁编程通常比锁的开销更小，因为它不需要线程间的上下文切换和等待。
  无锁编程可以避免死锁和饥饿等与锁相关的问题。
  无锁编程可以提供更好的并发性能，特别是在高并发环境下。
  然而，无锁编程也有一些限制和注意事项：

  无锁编程需要硬件支持原子操作，因此不是所有的平台和体系结构都支持无锁编程。
  无锁编程通常更复杂，需要更多的编程技巧和对并发编程的深入理解。
  无锁编程可能会导致更复杂的代码和更难以调试的问题。
*/