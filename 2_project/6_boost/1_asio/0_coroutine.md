## coroutine了解

### 1. 基础概念

#### 1.1 协程是什么？

协程（Coroutine）是一种比线程更轻量级的并发单元。与线程不同，协程不依赖于操作系统的线程调度，而是由程序自身控制的。协程可以在一个线程内实现多任务的切换，避免了线程上下文切换的开销。协程的主要特点是可以在执行过程中暂停，并在稍后恢复执行。

#### 1.2 协程有什么用？

协程主要用于实现并发编程，特别是在 I/O 密集型任务中。以下是协程的一些主要用途：

1. **异步编程**：协程可以在等待 I/O 操作（如网络请求、文件读写）时暂停执行，释放 CPU 资源给其他任务，从而提高程序的并发性能。
2. **生成器**：协程可以用作生成器，逐步生成数据，而不是一次性生成所有数据。这对于处理大数据集或流式数据非常有用。
3. **协作多任务**：协程可以在多个任务之间切换，模拟多任务处理，而不需要多线程或多进程的开销。
4. **简化代码**：协程可以使异步代码看起来像同步代码，简化了编写和维护异步代码的复杂性。

通过这些用途，协程在现代编程中变得越来越重要，特别是在需要高并发和高性能的应用程序中。

生成器的恢复执行由用户显式调用来决定。
异步函数的恢复执行由后台线程来决定。

#### 1.3 协程的优缺点是什么？
优点
* 轻量级：协程比线程更轻量级，创建和切换的开销更小。
* 无锁并发：协程可以避免多线程编程中的锁和竞态条件问题。
* 简化异步编程：协程可以使异步代码看起来像同步代码，简化了编写和维护异步代码的复杂性。
缺点
* 不适用于多核并行：协程在单个线程内运行，不能利用多核 CPU 的并行计算能力。
* 手动调度：协程的调度需要手动管理，增加了编程复杂性。
* 栈大小限制：协程的栈大小通常是固定的，可能会限制递归深度和局部变量的使用。

#### 1.4 协程的应用场景
网络编程（当成异步使用，提高可读性）：协程可以简化异步网络编程，使代码更易读。
数据处理（生成器，逐步处理数据）：协程可以用于处理大数据集，逐步生成和处理数据。
用户界面（ui协程和业务协程切换）：协程可以用于实现响应式用户界面，避免界面卡顿。

#### 1.5 协程实现的基本原理是什么？
协程的实现的关键在于上下文切换。 而上下文切换涉及到三个过程：保存状态、切换上下文、恢复状态。

保存状态主要涉及保存当前协程的执行上下文，包括以下内容：
* 程序计数器（PC）：指示当前执行的指令地址。
* 栈指针（SP）：指示当前栈顶的位置。
* 寄存器：保存当前协程的寄存器状态，包括通用寄存器和特殊寄存器。

恢复状态是指将之前保存的执行上下文恢复到当前协程中，使其能够继续执行。恢复状态的过程包括：
* 恢复程序计数器：将程序计数器恢复到保存时的值。
* 恢复栈指针：将栈指针恢复到保存时的值。
* 恢复寄存器：将寄存器恢复到保存时的状态。

而切换上下文就是保存当前协程状态，恢复到目标协程状态。

### 2. 协程使用的一般例子

#### 2.1 协程的切换
```c++
#include <boost/coroutine/coroutine.hpp>
#include <iostream>

void coroutine_function(boost::coroutines::coroutine<void>::push_type &yield) {
  std::cout << "Hello from coroutine!" << std::endl;
  yield();
  std::cout << "Back in coroutine!" << std::endl;
}

int main() {
  boost::coroutines::coroutine<void>::pull_type source(coroutine_function);
  std::cout << "Hello from main!" << std::endl;
  source();
  std::cout << "Back in main!" << std::endl;
  return 0;
}
/*
Hello from coroutine!
Hello from main!
Back in coroutine!
Back in main!
*/
```
* push_type和pull_type怎么理解？
  * push_type
    定义：push_type 是一个类型，用于将控制权推送到协程中。
    作用：在协程函数中，push_type 对象用于暂停协程的执行并返回到调用者。它通常作为协程函数的参数传递。
    使用场景：当协程需要暂停执行并返回到主程序或其他协程时，使用 push_type 对象的 operator() 来实现这一点。
  * pull_type
    定义：pull_type 是一个类型，用于从协程中拉取控制权。
    作用：在主程序或调用者中，pull_type 对象用于启动和恢复协程的执行。它通常在主程序中创建，并与协程函数关联。
    使用场景：当主程序或其他协程需要启动或恢复协程的执行时，使用 pull_type 对象的 operator() 来实现这一点。

#### 2.2 带返回值的协程
```c++
#include <boost/coroutine2/all.hpp>
#include <iostream>

void coroutine_function(boost::coroutines2::coroutine<int>::push_type &yield) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Coroutine yields: " << i << std::endl;
    yield(i);
  }
}

int main() {
  boost::coroutines2::coroutine<int>::pull_type source(coroutine_function);

  while (source) {
    int value = source.get();
    std::cout << "Main received: " << value << std::endl;
    source();
  }

  return 0;
}
```

### 98. 习题
```c++
#include <boost/coroutine2/all.hpp>
#include <iostream>

int main() {
  boost::coroutines2::coroutine<int>::pull_type source(
      [&](boost::coroutines2::coroutine<int>::push_type &sink) {
        int first = 1, second = 1;
        sink(first);
        sink(second);
        for (int i = 0; i < 8; ++i) {
          int third = first + second;
          first = second;
          second = third;
          sink(third);
        }
      });

  for (auto i : source) {
    std::cout << i << std::endl;
  }

  return 0;
}
```

### 99. quiz
#### 1. yield_type和call_type是什么？和push_type还有pull_type的联系是什么？
yield_type 和 call_type 是旧版本 Boost.Coroutine 库中的类型，而 push_type 和 pull_type 是新的 Boost.Coroutine2 库中的类型。
它们在功能和目的上有相似之处，都是用于在协程中暂停执行并返回到调用者，但它们的内部实现和对外使用方式有所不同。
```c++
#include <boost/coroutine/coroutine.hpp>
#include <iostream>

void coroutine_function(boost::coroutines::yield_type &yield) {
  std::cout << "Hello from coroutine!" << std::endl;
  yield();
  std::cout << "Back in coroutine!" << std::endl;
}

int main() {
  boost::coroutines::call_type coroutine(coroutine_function);
  std::cout << "Hello from main!" << std::endl;
  coroutine();
  std::cout << "Back in main!" << std::endl;
  return 0;
}
```

#### 2. 什么是对称协程？什么是非对称协程？
非对称协程：
  * 使用 boost::coroutines2::asymmetric_coroutine 实现。
  * 非对称协程只能从主程序或调度器中启动和恢复，而不能直接相互调用。
  * 非对称协程能知道其调用方，调用一些方法能让出当前的控制回到调用方手上。

对称协程：
  * 使用 boost::coroutines2::coroutine 实现。
  * 对称协程允许协程之间相互切换，而不需要返回到主调度器。
  * 对程协程都是平等的，一个对程协程能把控制让给任意一个协程，因此，当对称协程让出控制的时候，必须指定被让出的协程是哪一个。

对称协程可以当成非对称协程使用。对称协程提供了更灵活的控制流，可以在协程之间相互切换，但也可以像非对称协程一样，从主程序中启动和恢复协程。
具体什么时候建议使用非对称协程欢迎补充。

#### 3. 有栈协程和无栈协程的实现是什么？
协程的实现的关键在于上下文切换。 而上下文切换涉及到三个过程：保存状态、切换上下文、恢复状态。
而有栈协程实现和无栈协程的实现区别就在于状态保存在哪里。
有栈实现：每一个协程有一个独立的栈空间。受到栈空间大小约束，有空间损耗
无栈实现：将协程的状态存储在堆（Heap）空间中，通过状态机的方式去管理。不受栈空间大小约束，没有空间损耗。实现麻烦。

而协程的状态包含以下三个方面
* 程序计数器（PC）：指示当前执行的指令地址。
* 栈指针（SP）：指示当前栈顶的位置。
* 寄存器：保存当前协程的寄存器状态，包括通用寄存器和特殊寄存器。

* boost的是有栈协程
* c++20的是无栈协程

协程的实现涉及到底层的上下文切换和状态保存，这些操作通常需要使用汇编语言来直接操作寄存器和栈指针。高级语言通常不直接提供这些底层接口，因此实现协程通常依赖于库（调用一些其他类似接口去模拟）或语言特性（编译器层面直接操作）。


#### 4. 堆空间和栈空间概念
不同线程：
* 栈空间：每个线程都有自己的栈空间，用于存储该线程的局部变量、函数调用的参数、返回地址等。这意味着栈空间是线程私有的。
* 堆空间：同一进程内的所有线程共享同一个堆空间。这意味着线程之间可以通过指针或引用共享堆上分配的数据。

不同进程：
* 栈空间：每个进程都有自己的虚拟地址空间，其中包括独立的栈空间。进程间的栈空间是完全隔离的。
* 堆空间：每个进程也有自己独立的堆空间。进程间的堆空间不共享，因此进程之间不能直接访问对方的堆数据。

