to readingRepo
the lazy fox jumps over brown dog

## 怎么开始阅读一个大项目？

### 
1. 知道意图，看文档，问人
2. 断点调试
3. 修改
4. 重构（减少重复代码，函数提取）
5. 添加测试



#### CPU、内存占用过高问题定位

* https://blog.csdn.net/GR9527/article/details/108456151
* http://www.cxyzjd.com/article/qq_32273965/106749858
* 步骤：
  * 使用`top`定位到占用CPU高的进程PID   然后按`shift+p`按照CPU排序
  * 再用`ps -mp pid -o THREAD,tid,time`查询进程中,那个线程的cpu占用率高记住TID

* 如何读取一个10G文件，cat一个10g文件会发生什么

  - 强行 cat 一个大文件会造成内存溢出，通常将**cat**命令和**split**命令混合使用。
  - 比如内存是250M， 那么将10G的文件切分成若干个250M的文件，然后文本查找


在你提供的代码示例中，线程的状态转换如下：

```cpp
int main() {
  std::thread consumer_thread(consume, 10);

  for (int i = 0; i < 10; ++i) {
    while (shipment_available()) {
      std::this_thread::yield();
    }
    mtx.lock();
    cargo = i + 1;
    cv.notify_one();
    mtx.unlock();
  }

  consumer_thread.join();

  return 0;
}
```

1. **新建**：线程被创建。
2. **就绪**：线程进入就绪状态，等待被调度执行。
3. **运行**：函数。
4. **等待**：调用时进入等待状态，等待条件变量通知。
5. **就绪**：主线程在循环中调用后， 线程被唤醒，进入就绪状态。
6. **运行**：线程重新获得 CPU 时间片，继续执行。
7. **终止**：线程执行完成，进入终止状态。

通过这些状态转换，线程和进程能够有效地共享 CPU 资源，实现并发执行。

#### 1. 具体例子

- 等待状态：当线程调用 `cv.wait()` 时，它会进入等待状态，直到被条件变量唤醒。线程在等待期间不会占用 CPU 资源。
- 就绪：当线程调用 `yield()` 时，它会主动让出 CPU 使用权，进入就绪状态，等待被调度执行。线程不会继续占用 CPU 资源，直到操作系统再次分配时间片。
- 运行（忙等待）：`while(!ready)`：忙等待是指线程在等待某个条件满足时，不断地检查该条件，而不让出 CPU 使用权。线程在等待期间仍然占用 CPU 资源，直到时间片耗尽或条件满足。

#### 解释

1. **等待线程**：

   - `second`和`third`函数中的线程使用`cv.wait(lock, [this]() { return k == 1; });`和`cv.wait(lock, [this]() { return k == 2; });`来等待条件变量。
   - 这些等待操作都在一个循环中进行，以确保即使发生虚假唤醒，线程也会继续等待，直到条件满足。

2. **通知线程**：
   - `first`函数在完成任务后，调用`cv.notify_all()`通知所有等待的线程。
   - `second`函数在完成任务后，调用`cv.notify_one()`通知一个等待的线程。

通过这种方式，可以确保线程在条件满足之前不会继续执行，从而正确处理虚假唤醒。



### 2. 怎么应对虚假唤醒？

为了正确处理虚假唤醒，通常在等待条件变量时使用一个循环来反复检查条件是否满足。这样可以确保线程在条件满足之前不会继续执行。

#### 示例代码

以下是一个示例，展示了如何使用条件变量和处理虚假唤醒：

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

void printFirst() {
  for (int i = 0; i < 5; i++) {
    std::cout << "first" << '\n';
  }
}

void printSecond() {
  for (int i = 0; i < 5; i++) {
    std::cout << "second" << '\n';
  }
}

void printThird() {
  for (int i = 0; i < 5; i++) {
    std::cout << "third" << '\n';
  }
}

class Foo {
public:
  void first(std::function<void()> printFirst) {
    printFirst();
    {
      std::lock_guard<std::mutex> lock(mtx);
      k = 1;
    }
    cv.notify_all();
  }

  void second(std::function<void()> printSecond) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return k == 1; });
    printSecond();
    {
      std::lock_guard<std::mutex> lock(mtx);
      k = 2;
    }
    cv.notify_one();
  }

  void third(std::function<void()> printThird) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return k == 2; });
    printThird();
  }

private:
  std::condition_variable cv;
  std::mutex mtx;
  int k = 0;
};

int main() {
  Foo f;
  std::thread t1(&Foo::first, &f, printFirst);
  std::thread t2(&Foo::second, &f, printSecond);
  std::thread t3(&Foo::third, &f, printThird);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
```

```c++
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
std::condition_variable_any cv;

int cargo = 0;

void consumer() {
  mtx.lock();
  while (cargo == 0) {
    cv.wait(mtx);
  }

  std::cout << cargo << '\n';
  cargo = 0;
  mtx.unlock();
}

void producer(int id) {
  mtx.lock();
  cargo = id;
  cv.notify_one();
  mtx.unlock();
}

int main() {
  std::vector<std::thread> consumers;
  consumers.reserve(10);
  std::vector<std::thread> producers;
  consumers.reserve(10);

  for (int i = 0; i < 10; ++i) {
    consumers[i] = std::thread(consumer);
    producers[i] = std::thread(producer, i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    producers[i].join();
    consumers[i].join();
  }

  return 0;
}

```

中断函数为什么不可以上锁？
* 如果锁已经被持有了，有可能会出现中断丢失；
* 如果锁已经被持有了，中断函数如果是高优先级的，时间片可能一直分过来处理这个，导致死锁

后台进程和守护进程的区别是什么

终端，终端进程和终端设备文件的联系是什么
如果开了多个终端，有多少个终端进程？多少个终端设备文件？

终端设备文件和shell的关系

shell是怎么执行命令的

shell是独立一个进程吗？也就是开了一个终端的时候，会有一个终端仿真器，一个终端设备文件，一个shell进程。终端设备文件主要意义在于处理输入输出，而shell进程负责去解析命令输入，根据解析结果调用相应命令，是吗

有哪些信号

操作系统和程序的交互方式有哪些？

操作系统是怎样的存在？尤其是体现在和程序交互时。

可以理解为操作系统就是一个内核和多个系统进程吗？
其中内核管理着系统资源（cpu/内存/io设备等等硬件）；
那比如说cpu任务调度队列，和中断信号处理等等其他功能，是如何同时运行的呢？

对于异步任务，当future已经实现的时候，那么这个异步线程就会结束了，那么在调用.get()方法之前，这个返回值存储在哪里？