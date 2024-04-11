## memory order

### 1. 什么是内存序
内存序（Memory Order）是一个计算机科学的概念，主要用于描述多处理器系统中内存操作的顺序。

在单处理器系统中，程序中的指令总是按照它们在程序中出现的顺序（即程序顺序）执行的。但是在多处理器系统中，由于各种优化技术（如指令重排和缓存），程序中的指令可能不会按照程序顺序执行。这就可能导致在一个处理器上看到的内存值和在另一个处理器上看到的内存值不一致，从而引发各种并发问题。

为了解决这个问题，计算机科学家引入了内存序的概念。内存序定义了内存操作（如读取和写入）在多处理器系统中的可见顺序。根据内存序的不同，我们可以将内存模型分为几种类型，如强内存模型（Strong Memory Model）和弱内存模型（Weak Memory Model）。

在强内存模型中，所有的内存操作都按照程序顺序执行。这种模型简单易懂，但是可能会限制系统的性能。

在弱内存模型中，内存操作可能不按照程序顺序执行。这种模型可以提高系统的性能，但是编程会更复杂，因为程序员需要显式地使用内存屏障（Memory Barrier）或原子操作（Atomic Operation）来保证内存操作的顺序。


### 2. 内存序的一个例子
```c++
#include <iostream>
#include <thread>
#include <unistd.h>

int a = 0;
int b = 0;

void func_1() {
  a = 1; // 1
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << b << std::endl; // 2
}

void func_2() {
  b = 2; // 3
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << a << std::endl; // 4
}

int main() {
  std::thread t1(func_1);
  std::thread t2(func_2);
  t1.join();
  t2.join();
  return 0;
}
```

* 使用sleep_for，是因为在大多数现代操作系统中，线程的时间片通常是几十毫秒到几百毫秒，所以在实际运行时，func_1 和 func_2 很可能会在同一个时间片内完成，也就是说，它们实际上是串行执行的。这就可能导致你看到的输出总是 "0,1" 或 "1,0"。