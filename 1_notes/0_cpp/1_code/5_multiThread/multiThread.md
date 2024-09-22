## 多线程概念和关系

c++关于多线程开发的关键字可以有以下分类：
* 创建和管理线程或异步任务。
  * thread
    * 需要直接控制线程的生命周期：当你需要精细控制线程的创建、启动、暂停、恢复和终止时，使用std::thread是合适的选择。
    * 需要共享资源的复杂同步：当多个线程需要访问共享资源，并且需要复杂的同步机制（如互斥锁、条件变量）时，std::thread提供了更大的灵活性。
    * 需要高性能：在某些高性能计算场景中，直接使用std::thread可以避免一些抽象层带来的开销。
  * async
    * 简单的异步任务：当你需要启动一个简单的异步任务，并且不需要显式管理线程时，使用std::async是最方便的选择。
    * 任务的启动策略：当你希望任务可以根据需要立即执行或延迟执行时，std::async提供了灵活的启动策略
      （如std::launch::async和std::launch::deferred）。
    * 需要返回值的异步任务：当你需要启动一个异步任务并获取其返回值时，std::async会返回一个std::future对象，方便获取结果。
  * packaged_task
    * 需要更高的灵活性：当你需要将任务与线程分离，并在不同的时间和上下文中启动任务时，使用std::packaged_task是合适的选择。
    * 复杂的任务管理：当你需要显式管理任务的生命周期，并且可能需要将任务传递给其他线程或存储在容器中时，std::packaged_task提供了更高的灵活性。
    * 需要返回值的任务：与std::async类似，std::packaged_task也会返回一个std::future对象，用于获取任务的结果。

**使用thread**：当你需要直接控制线程的生命周期和同步机制时。
**使用async**：当你需要启动简单的异步任务，并且希望任务的启动策略灵活时。
**使用packaged_task**：当你需要更高的灵活性来管理任务的生命周期，并且可能需要将任务传递或存储时。

* 用于线程间的同步和通信，确保线程安全。
  * promise-future/shared-future
    * 线程之间的值传递
  * atomic
    * 原子操作
  * mutex
    * 互斥锁
  * condition_variable
    * 信号量


## 线程安全

### 1. 线程安全
* 线程安全的概念
  * 多个线程访问同一个对象时，如果不用考虑这些线程在运行时环境下的调度和交替执行，也不需要进行额外的同步，或者在调用方进行任何其他操作，调用这个对象的行为都可以获得正确的结果，那么这个对象就是线程安全的
  * 或者说：**一个类或者程序所提供的接口对于线程来说是原子操作或者多个线程之间的切换不会导致该接口的执行结果存在二义性，也就是说我们不用考虑同步的问题**
  * **线程安全问题大多是由全局变量及静态变量引起的，局部变量逃逸也可能导致线程安全问题**
  * 若每个线程中对全局变量、静态变量只有读操作，而无写操作，一般来说，这个全局变量是线程安全的；若有多个线程同时执行写操作，一般都需要考虑线程同步，否则的话就可能影响线程安全
  * 类要成为线程安全的，**首先必须在单线程环境中有正确的行为**。如果一个类实现正确(这是说它符合规格说明的另一种方式)，那么没有一种对这个类的对象的操作序列(读或者写公共字段以及调用公共方法)可以让对象处于无效状态，观察到对象处于无效状态、或者违反类的任何不可变量、前置条件或者后置条件的情况
  * 此外，一个类要成为线程安全的，在被多个线程访问时，不管运行时环境执行这些线程有什么样的时序安排或者交错，它必须仍然有如上所述的正确行为，并且在调用的代码中没有任何额外的同步。其效果就是，在所有线程看来，对于线程安全对象的操作是以固定的、全局一致的顺序发生的
  * 正确性与线程安全性之间的关系非常类似于在描述 ACID(原子性、一致性、独立性和持久性)事务时使用的一致性与独立性之间的关系：从特定线程的角度看，由不同线程所执行的对象操作是先后(虽然顺序不定)而不是并行执行的
  * 简单理解，确保在多线程访问的时候，我们的程序还能按照我们预期的行为去执行，那么就是线程安全

* 并发编程中的三大性质

  * 原子性：即一个操作或者多个操作，要么全部执行并且执行的过程不会被任何因素打断，要么就都不执行。原子性就像数据库里面的事务一样，他们是一个团队，同生共死
  * 可见性：指当多个线程访问同一个变量时，一个线程修改了这个变量的值，其他线程能够立即看得到修改的值。**volatile可以保证可见性**，当一个变量被volatile修饰后，表示着线程本地内存无效，当一个线程修改共享变量后他会立即被更新到主内存中，当其他线程读取共享变量时，它会直接从主内存中读取。**volatile也可以保证线程可见性且提供了一定的有序性，但是无法保证原子性**
  * 有序性：即程序执行的顺序**按照代码的先后顺序执行**。为了效率，C++或Java允许编译器和处理器对指令进行重排序，当然重排序它不会影响单线程的运行结果，但是对多线程会有影响。volatile可以保证一定的有序性

* 非阻塞同步（乐观锁）

  * 随着硬件指令集的发展，出现了基于冲突检测的乐观并发策略，通俗地说，**就是先进行操作，如果没有其他线程争用共享数据，那操作就成功了**；**如果共享数据有争用，产生了冲突，那就再采用其他的补偿措施。（最常见的补偿错误就是不断地重试，直到成功为止）**，这种乐观的并发策略的许多实现都不需要把线程挂起，因此这种同步操作称为**非阻塞同步**
  * **非阻塞的实现CAS（Compare-and-Swap）**
    * CAS指令需要有3个操作数，分别是内存地址（在java中理解为变量的内存地址，用V表示）、旧的预期值（用A表示）和新值（用B表示）。CAS指令执行时，当且仅当V处的值符合旧预期值A时，处理器用B更新V处的值，否则它就不执行更新，但是无论是否更新了V处的值，都会返回V的旧值，上述的CAS指令是一个原子操作
  * **CAS的ABA问题**
    * 因为CAS需要在操作值的时候检查下值有没有发生变化，如果没有发生变化则更新，但是一个值原来是A，变成了B，又变成了A，那么使用CAS进行检查时会发现它的值没有发生变化，但是实际上却变化了。CAS只关注了比较前后的值是否改变，而无法清楚在此过程中变量的变更明细，这就是所谓的ABA漏洞
    * ABA问题的解决思路就是使用版本号(如MySQL的MVCC)。在变量前面追加版本号，每次变量更新的时候把版本号加一，那么A-B-A就变成了1A-2B-3C

## 可重入函数

* 重入即表示重复进入，首先它意味着**这个函数可以被中断**，其次意味着它**除了使用自己栈上的变量以外不依赖于任何环境**（包括static ），这样的函数就是purecode （纯代码）可重入，可以允许有该函数的多个副本在运行，由于它们使用的是分离的栈，所以不会互相干扰
* 信号就像硬件中断一样，会打断正在执行的指令序列。**信号处理函数无法判断捕获到信号的时候，进程在何处运行**。如果信号处理函数中的操作与打断的函数的操作相同，而且这个操作中有**静态数据结构**等，当信号处理函数返回的时候（当然这里讨论的是信号处理函数可以返回），恢复原先的执行序列，可能会**导致信号处理函数中的操作覆盖了之前正常操作中的数据**
* 常见的情况是，程序执行到某个函数foo()时，收到信号，于是暂停目前正在执行的函数，转到信号处理 函数，而这个信号处理函数的执行过程中，又恰恰也会进入到刚刚执行的函数foo()，这样便发生了所谓的重入。此时如果foo()能够正确的运行，而且处理完成后，之前暂停的foo()也能够正确运行，则说明它是可重入的
* 不可重入的后果：不可重入的后果**主要体现在象信号处理函数这样需要重入的情况中**。如果**信号处理函数中使用了不可重入的函数**，则可能**导致程序的错误甚至崩溃**
* 要确保函数可重入，需满足以下几个条件： 
  1. 不在函数内部使用静态或全局数据 
  2. 不返回静态或全局数据，所有数据都由函数的调用者提供
  3. 使用本地数据，或者通过制作全局数据的本地拷贝来保护全局数据
  4. 不调用不可重入函数

* **不可重入的几种情况**：

  * 使用静态数据结构，比如getpwnam，getpwuid：如果信号发生时正在执行getpwnam，信号处理程序中执行getpwnam可能覆盖原来getpwnam获取的旧值

  - **调用malloc或free**：如果信号发生时正在malloc（修改堆上存储空间的链接表），**信号处理程序又调用malloc，会破坏内核的数据结构**
  - 使用标准IO函数，因为**好多标准IO的实现都使用全局数据结构**，比如printf(文件偏移是全局的)
  - 函数中调用longjmp或siglongjmp：信号发生时程序正在修改一个数据结构，处理程序返回到另外一处，导致数据被部分更新

* **可重入是线程安全的一个真子集，如果一个函数是可重入函数，那么它一定是线程安全的，但是如果一个函数是线程安全的，它不一定是可重入函数**

* **异步信号安全(async-signal-safe)函数**

  * **异步信号安全的函数是指当从信号处理器函数调用时，可以保证其实现是安全的，如果某一函数是可重入的，或者信号处理器函数无法将其中断时，就称该函数是异步信号安全的**
  * 但同时指出，仅当信号处理器函数中断了不安全函数的执行，且处理器函数自身也调用了这个不安全函数时，该函数才是不安全的
  * 由于**可能会更新errno，依然会导致信号处理器函数不可重入**，因为它们可能会覆盖之前由主程序调用函数时所设置的errno值。有一种变通方法，即当信号处理器函数使用了标准所列可重入函数时，可在其入口处保存errno值，并在其出口处恢复errno的旧有值


## 原子变量介绍

* 解决多线程下共享变量的问题(i++，指令重排问题)：对于共享变量的访问进行加锁，加锁可以保证对临界区的互斥访问，
* C++11提供了一些原子变量与原子操作解决用户加锁操作麻烦或者容易出错的问题
* C++11标准在标准库atomic头文件提供了模版std::atomic<>来定义原子量，而对于大部分内建类型，C++11提供了一些特化，如，std::atomic_int (std::atomic<int>)等
* 自定义类型变成原子变量的条件是该类型必须为**Trivially Copyable类型**(简单的判断标准就是这个类型可以用std::memcpy按位复制)
* atomic有一个成员函数is_lock_free，这个成员函数可以告诉我们到底这个类型的原子量是使用了原子CPU指令实现了无锁化，还是依然使用的加锁的方式来实现原子操作

## [内存序]
(https://www.cnblogs.com/FateTHarlaown/p/8919235.html)

关于内存序（Memory Order），以下是一些需要了解的关键点：

### 1. 内存序的基本概念

- **内存序**：指的是多线程程序中，内存操作的顺序和可见性。内存序定义了不同线程之间的内存操作如何排序和可见。

### 2. C++ 中的内存序类型

C++11 标准引入了内存序模型，并在 `<atomic>` 头文件中定义了几种内存序类型：

- **`memory_order_relaxed`**：最弱的内存序，不提供任何同步或顺序保证。适用于不需要跨线程同步的场景。
- **`memory_order_consume`**：比 `memory_order_acquire` 更弱，主要用于消费依赖关系。C++20 中已被弃用。
- **`memory_order_acquire`**：保证在此操作之前的所有读写操作不会被重排序到此操作之后。适用于获取锁等场景。
- **`memory_order_release`**：保证在此操作之后的所有读写操作不会被重排序到此操作之前。适用于释放锁等场景。
- **`memory_order_acq_rel`**：结合了 `memory_order_acquire` 和 `memory_order_release` 的效果。适用于读-修改-写操作。
- **`memory_order_seq_cst`**：最强的内存序，提供全局的顺序一致性。所有操作都按照程序中的顺序执行。

### 3. 内存序的使用场景

- **`memory_order_relaxed`**：适用于计数器等不需要同步的场景。
- **`memory_order_acquire` 和 `memory_order_release`**：适用于锁的获取和释放。
- **`memory_order_acq_rel`**：适用于需要同时进行获取和释放的操作，如读-修改-写。
- **`memory_order_seq_cst`**：适用于需要严格顺序一致性的场景。

### 4. 内存序的示例代码

以下是一些示例代码，展示了不同内存序的使用：

```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> data(0);
std::atomic<bool> ready(false);

void producer() {
    data.store(42, std::memory_order_relaxed); // 使用 relaxed 内存序
    ready.store(true, std::memory_order_release); // 使用 release 内存序
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) { // 使用 acquire 内存序
        // 等待生产者准备好数据
    }
    std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl; // 使用 relaxed 内存序
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
```

### 5. 内存序的选择

- **性能考虑**：较弱的内存序（如 `memory_order_relaxed`）通常性能更好，但需要确保正确性。
- **正确性考虑**：较强的内存序（如 `memory_order_seq_cst`）提供更强的保证，但可能会影响性能。

### 6. 内存序的常见问题

- **指令重排**：编译器和 CPU 可能会对指令进行重排，内存序可以控制这种重排行为。
- **可见性**：不同线程对共享变量的修改是否能及时被其他线程看到，内存序可以影响这种可见性。

### 7. 内存序是谁在改变的？
你的理解基本正确，但可以稍微调整和补充一些细节：

### 1. 编译器层面

- **指令重排**：编译器为了优化性能，可能会对代码中的指令进行重排。内存序通过内存屏障（Memory Barrier）指令来限制编译器的重排行为，确保特定的内存操作顺序。

### 2. CPU 层面

- **指令乱序执行**：CPU 为了提高性能，可能会对指令进行乱序执行。内存序通过插入内存屏障指令来限制 CPU 的乱序执行行为，确保特定的内存操作顺序。
- **缓存一致性协议**：如 MESI 协议，用于确保多个 CPU 核心对共享内存的访问是一致的。内存序通过这些协议来实现跨核心的内存操作顺序保证。

### 3. 内存和硬件层面

- **内存模型**：不同的硬件架构有不同的内存模型，定义了内存操作的可见性和顺序性。内存序通过适配不同的内存模型来实现跨平台的一致性。
- **内存屏障指令**：硬件层面的内存屏障指令（如 x86 架构的 `mfence`、`lfence`、`sfence`）用于确保特定的内存操作顺序。这些指令会阻止特定类型的内存操作重排。

### 总结

- **编译器**：通过内存屏障限制指令重排。
- **CPU**：通过内存屏障和缓存一致性协议（如 MESI）限制指令乱序执行。
- **内存和硬件**：通过内存模型和内存屏障指令确保内存操作的顺序和可见性。

三个层面上都有可能改变指令的顺序，内存序通过不同的机制在这些层面上确保内存操作的正确性和一致性。

了解和正确使用内存序是编写高效且正确的多线程程序的关键。选择合适的内存序可以在保证程序正确性的同时，提升程序的性能。

4. 内存序类型的实现
**memory_order_relaxed**：不插入任何内存屏障，允许最大程度的优化和重排。
**memory_order_acquire**：在加载操作前插入内存屏障，确保之前的所有读写操作不会被重排到此操作之后。
**memory_order_release**：在存储操作后插入内存屏障，确保之后的所有读写操作不会被重排到此操作之前。
**memory_order_acq_rel**：结合了 memory_order_acquire 和 memory_order_release 的效果，确保加载和存储操作的顺序。
**memory_order_seq_cst**：插入全局的内存屏障，确保所有操作按照程序中的顺序执行。

### 99. quiz
容器线程安全
7/原子操作如何实现(锁/cas***作)

8/如何实现一个互斥锁,互斥锁的实现原理

18/如何使用信号量制作出一个互斥锁

2/红黑树是线程安全的吗
3/有哪些同步手段
6/计数如何保证线程安全?(cas***作/***作系统底层指令支持)


#### 1. 线程之间私有和共享的资源有哪些?
线程之间的私有和共享资源主要包括以下几种：

**私有资源**：

1. **栈内存**：每个线程都有自己的栈内存，用于存储局部变量和函数调用的上下文信息。其他线程无法访问一个线程的栈内存。

2. **寄存器**：每个线程都有自己的寄存器集，包括程序计数器和其他寄存器。这些寄存器的值在线程切换时会被保存和恢复。

3. **线程局部存储（Thread Local Storage，TLS）**：这是一种特殊的机制，允许每个线程拥有自己的全局变量或静态变量的副本。

**共享资源**：

1. **堆内存**：所有线程共享同一块堆内存，线程可以创建对象并将其地址传递给其他线程。

2. **全局变量和静态变量**：全局变量和静态变量存储在所有线程共享的内存中，任何线程都可以访问它们。

3. **文件和网络资源**：如果一个程序打开了一个文件或网络连接，所有的线程都可以使用这些资源。

请注意，虽然线程可以共享许多资源，但在访问这些资源时需要小心，因为这可能会导致竞态条件和其他并发问题。为了避免这些问题，通常需要使用互斥锁、信号量等同步机制来保护共享资源。


#### 2. C++11的thread_local是什么？

`thread_local`是C++11引入的一个关键字，用于声明线程局部存储（Thread Local Storage，TLS）。

当一个变量被声明为`thread_local`时，每个线程都会有这个变量的一个副本，每个线程对其副本的修改都不会影响其他线程的副本。

这对于多线程编程非常有用，因为它可以让每个线程拥有自己的全局变量或静态变量的副本，避免了多线程之间的数据竞争。

以下是一个简单的例子：

```cpp
#include <thread>

thread_local int tls_var = 0;

void worker() {
    tls_var++;
    // 对tls_var的修改不会影响其他线程的tls_var
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    return 0;
}
```

在这个例子中，每个线程都有自己的`tls_var`副本，它们对`tls_var`的修改不会相互影响。


**37. 从各个方面使得std::threads unjoinable**

每一个std::thread类型的对象都处于两种状态：joinable和unjoinable

+ joinable：对应底层已运行、可运行或者运行结束的出于阻塞或者等待调度的线程
+ unjoinable： 默认构造的std::thread, 已move的std::thread, 已join的std::thread, 已经分离的std::thread
+ 如果某一个std::thread是joinable的，然后他被销毁了，会造成很严重的后果，（比如会造成隐式join（会造成难以调试的性能异常）和隐式detach（会造成难以调试的未定义行为）），所以我们要保证thread在所有路径上都是unjoinable的：
  
    class ThreadRAII{
    public:
        enum class DtorAction{join, detach};
        ThreadRAII(std::thread&& t, DtorAction a):action(a), t(std::move(t)){} //把线程交给ThreadRAII处理
        ~THreadRAII(){
            if(t.joinable()){
                if(action == DtorAction::join){
                    t.join();
                }
                else{
                    t.detach();                  //保证所有路径出去都是不可连接的
                }
            }
        }
    private:
        DtorAction action;
        std::thread t;    //成员变量最后声明thread
    }

**38. 知道不同线程句柄析构行为**

     _____           ___返回值___  std::promise _______
    |调用方|<--------|被调用方结果|<------------|被调用方|

因为被调用函数的返回值有可能在调用方执行get前就执行完毕了，所以被调用线程的返回值会保存在一个地方，所以会存在一个"共享状态"

所以在异步状态下启动的线程的共享状态的最后一个返回值是会保持阻塞的，知道该任务结束，返回值的析构函数在常规情况下，只会析构返回值的成员变量


#### 考虑对于单次事件通信使用

这段文本讨论了在多线程编程中，如何有效地进行单次事件通信。具体来说，它比较了使用标志位、线程锁和`std::promise`三种不同的方法来实现线程间的同步和通信。

1. **使用标志位(flag)**:
   - 代码示例中没有直接展示，但提到了一种常见的做法，即在一个线程中使用`while(!flag){}`循环等待另一个线程改变`flag`的值。这种方法简单，但它会导致忙等待（busy-waiting），浪费CPU资源，因为等待的线程会持续检查`flag`而不做任何有用的工作。

2. **使用线程锁**:
   - 文本提到可以使用线程锁来代替标志位，以避免忙等待。示例代码中，`std::lock_guard<std::mutex>`用于自动管理互斥锁，但示例似乎有误，因为它没有展示如何正确使用互斥锁来等待某个条件。正确的做法通常涉及到`std::condition_variable`，它可以与互斥锁一起使用，让线程在条件不满足时休眠，直到条件被另一个线程改变并通知。

3. **使用`std::promise`**:
   - 最后，文本推荐使用`std::promise`来进行单次事件通信。`std::promise`是一种同步机制，可以在一个线程中存储一个值或异常，然后在另一个线程中通过与之对应的`std::future`对象来检索这个值或异常。示例中，`detect`函数创建了一个线程`t`，这个线程会等待`std::promise`对象`p`的状态被设置。当`detect`函数调用`p.set_value()`时，`p`的状态被设置，`t`中的等待操作完成，`react`函数随后被执行。这种方法避免了忙等待，且只适用于一次性通信，但需要注意的是，它可能涉及到堆内存的使用。

总的来说，这段文本强调了在设计多线程程序时，应该避免使用忙等待策略，而应该考虑使用更高级的同步机制，如`std::promise`，来高效地进行线程间的单次事件通信。

## threads

- 作者以[NonRecurisiveMutest.cc](https://github.com/chenshuo/recipes/tree/master/thread/test)这个为例子,如果mutex是递归的话,push_back()可能(但不总是)导致迭代器失效,程序偶尔会crash,这种错误不好debug.
- 而这种偶发的crash,发生在调用函数和被调用函数都以为自己拿到了锁,如果恰好都在修改一个对象的时候,这时候就容易crash.
- 而如果使用非递归锁,这种错误就会提前暴露出来,死锁比偶发的crash总归是好debug.

- 线程同步的四项原则,尽量用高层同步方法(线程池/队列/倒计时等),mutex和cv都是非常底层的同步原语,在开发中往往都用更高级的工具.但是使用mutex和cv有一个好处就是,分析工具更便于分析;
- 种种优化方法在没有数据支持的情况下,是靠不住的.很多人误认为用锁会让程序变慢,但实际上影响性能的不是锁,而是锁争用.要学会在程序的复杂度和性能之间取得平衡,并考虑机器扩容的可能.
- 多机的可扩展能力比单机的性能优化更重要,更值得投入精力.
- 
对比过很多资料,最后的多线程入门资料还是在[leetcode](https://leetcode-cn.com/problems/print-in-order/solution/c-hu-chi-suo-tiao-jian-bian-liang-xin-hao-liang-yi/)



- ***什么是析构竞态?***

  ​	与其他面向对象语言不同,C++ 要求程序员自己管理对象的生命期,这在多线程环境下显得尤为困难.当一个对象能被多个线程同时看到,那么对象的销毁时机就会变得模糊不清,可能出现多种竞态条件:

  - 在即将析构一个对象时,从何而知是否有另外的线程正在执行该对象的成员函数?
  - 如何保证在执行成员函数期间,对象不会在另一个线程被析构?
  - 在调用某个对象的成员函数之前,如何得知这个对象还活着?它的析构函数会不会刚执行到一半?

  ​	解决这些 race condition 是 C++ 多线程编程面临的基本问题.本文试图以 shared_ptr 一劳永逸地解决这些问题,减轻 C++ 多线程编程的精神负担.

- ***什么是线程安全?***

  ​	依据<Java 并发编程实践>/<Java Concurrency in Practice>一书,一个线程安全的 class 应当满足三个条件:

  - 从多个线程访问时,其表现出正确的行为
  - 无论操作系统如何调度这些线程,无论这些线程的执行顺序如何交织
  - 调用端代码无需额外的同步或其他协调动作

  ​	依据这个定义,C++ 标准库里的大多数类都不是线程安全的,无论 std::string 还是 std::vector 或 std::map,因为这些类通常需要在外部加锁.

### 2. 实战篇

- ***如何从构造函数,实现线程安全?***

  对象构造要做到线程安全,惟一的要求是在构造期间不要泄露 this 指针,即

  - 不要在构造函数中注册任何回调
  - 也不要在构造函数中把 this 传给跨线程的对象
  - 即便在构造函数的最后一行也不行

  之所以这样规定,是因为在构造函数执行期间对象还没有完成初始化,如果 this 被泄露 (escape) 给了其他对象(其自身创建的子对象除外),那么别的线程有可能访问这个半成品对象,这会造成难以预料的后果.

- ***为什么线程安全的,析构函数这么麻烦?***

  ​	因为一般线程安全方法都是依赖于互斥锁的,而析构函数会在析构的过程中把锁给销毁.

  确保所有线程都已经停止使用对象:在销毁对象之前,你需要确保没有任何线程还在使用或者可能会使用这个对象.这可能需要使用一些同步机制,例如条件变量或者future,来等待所有线程完成.

  使用智能指针管理资源:在C++中,你可以使用智能指针(例如std::unique_ptr或std::shared_ptr)来管理对象.当没有任何指针指向对象时,对象会被自动销毁.这可以避免手动管理内存和资源的复杂性.

### 1. thread

#### 1.1 join和detach
* join和detach
* join:
    当你调用 join 时,它会等待被调用线程执行完毕,然后再继续执行主线程.换句话说,join 使得主线程等待被调用线程的完成.
    使用 join 可以确保在主线程继续执行之前,被调用线程的任务已经完成.这对于需要等待线程执行结果的情况很有用

* detach:
    当你调用 detach 时,它使得被调用线程成为后台线程,与主线程分离.主线程不再等待被调用线程的完成.
    使用 detach 可以使得主线程在后台线程运行的同时继续执行,而不必等待后台线程完成.这对于一些异步任务或长时间运行的任务很有用.

* 不使用join也不使用detach:
    在主线程退出时,可能会导致一些未定义行为,因为线程对象将被销毁,但线程本身可能仍在运行.
    以下是可能发生的情况:
    1. 程序可能终止,但线程可能仍在运行:
        如果主线程退出,而被创建的线程仍在运行,可能导致程序终止,但线程继续执行.这可能导致线程无法正确完成其任务,因为主线程已经退出.
        程序可能崩溃:

    2. 程序可能会崩溃:
        这是由于线程对象的销毁可能涉及到一些资源的释放,而线程本身仍在访问这些资源,导致未定义行为.
    3. 资源泄漏:
        如果线程分配了一些资源(例如内存),但在线程执行完毕前这些资源没有被释放,可能会导致资源泄漏.

#### 1.2 threadID

#### 1.3 joinable

### 2. mutex
mutex

Critical Section(临界区)是指一段代码或一段程序,其中包含对共享资源的访问或修改.在多线程或并发编程中,由于多个线程同时访问共享数据,为了防止竞争条件(Race Condition)和确保数据的一致性,需要通过同步机制将临界区保护起来.


#### 2.1 args
#### 2.2 lock_guard 2.3 unique_lock
是的,你的理解是正确的.

`std::lock_guard`和`std::unique_lock`都是RAII(Resource Acquisition Is Initialization)风格的互斥锁包装器,它们在构造时自动锁定互斥锁,在析构时自动解锁互斥锁.这种设计可以确保在函数退出(正常或异常)时自动释放锁,从而避免了因忘记解锁而导致的死锁.

`std::lock_guard`和`std::unique_lock`的主要区别在于,`std::unique_lock`提供了更多的灵活性:

1. **延迟锁定**:`std::unique_lock`可以在创建时不立即锁定互斥锁,然后在需要的时候再锁定.`std::lock_guard`则在创建时必须立即锁定互斥锁.

2. **所有权传递**:`std::unique_lock`是可移动的,这意味着你可以将锁的所有权从一个`std::unique_lock`对象转移到另一个.`std::lock_guard`则不可移动.

3. **手动锁定和解锁**:`std::unique_lock`提供了`lock`和`unlock`方法,允许你在任何时候手动锁定和解锁互斥锁.`std::lock_guard`则不提供这些方法.

因此,如果你需要更多的控制,例如延迟锁定/所有权传递或手动锁定和解锁,那么应该使用`std::unique_lock`.如果你只需要简单地锁定和解锁互斥锁,那么`std::lock_guard`可能是更好的选择,因为它更简单,且开销更小.

`std::adopt_lock`/`std::defer_lock` 和 `std::try_to_lock` 都是 `std::unique_lock` 的构造函数可以接受的锁策略参数,它们的含义和使用场景如下:

1. **std::adopt_lock**:这个策略表示互斥锁在构造锁对象时已经被锁定.当你已经手动锁定了一个互斥锁,然后想要将它的管理权交给 `std::unique_lock` 时,可以使用 `std::adopt_lock`.这样,`std::unique_lock` 在构造时就不会再次尝试锁定互斥锁,而是直接接管已经被锁定的互斥锁.

2. **std::defer_lock**:这个策略表示在构造 `std::unique_lock` 时不锁定互斥锁.你可以稍后手动调用 `std::unique_lock::lock` 方法来锁定互斥锁.这个策略在你需要延迟锁定互斥锁的情况下很有用.

3. **std::try_to_lock**:这个策略表示在构造 `std::unique_lock` 时尝试锁定互斥锁,如果互斥锁已经被锁定,则立即返回,不会阻塞.你可以检查 `std::unique_lock::owns_lock` 方法的返回值,来判断是否成功锁定了互斥锁.

在你给出的代码中,`std::lock(foo, bar)` 会同时锁定 `foo` 和 `bar` 互斥锁,然后使用 `std::adopt_lock` 策略创建 `std::unique_lock` 对象,接管已经被锁定的互斥锁.在 `task_b` 函数中,使用 `std::defer_lock` 策略创建 `std::unique_lock` 对象,然后使用 `std::lock(lck1, lck2)` 同时锁定两个 `std::unique_lock` 对象管理的互斥锁.这样可以避免因为锁定顺序的问题导致死锁.



`std::unique_lock` 和 `std::lock_guard` 都是 C++ 中用于管理互斥锁的类,但它们之间存在一些重要的区别:

1. **灵活性**:`std::unique_lock` 比 `std::lock_guard` 更灵活.`std::unique_lock` 允许你延迟锁定,手动锁定和解锁,以及尝试锁定.而 `std::lock_guard` 在构造时自动锁定互斥锁,在析构时自动解锁,不支持手动控制.

2. **所有权转移**:`std::unique_lock` 支持所有权的转移,这意味着你可以将一个 `std::unique_lock` 对象移动到另一个 `std::unique_lock` 对象.而 `std::lock_guard` 不支持所有权的转移.

3. **条件变量支持**:`std::unique_lock` 可以与 `std::condition_variable` 一起使用,以实现线程间的同步和通信.而 `std::lock_guard` 不支持与 `std::condition_variable` 一起使用.

4. **性能开销**:由于 `std::unique_lock` 提供了更多的功能,所以它的性能开销可能会比 `std::lock_guard` 稍大一些.

总的来说,如果你需要更多的控制和灵活性,或者需要使用条件变量,那么 `std::unique_lock` 是一个好的选择.如果你只需要简单地锁定和解锁互斥锁,那么 `std::lock_guard` 可能是一个更好的选择,因为它更简单,性能开销也可能更小.

是的,C++中确实有`std::shared_lock`.这是一个类模板,用于管理`std::shared_mutex`或`std::shared_timed_mutex`类型的互斥锁.

`std::shared_lock`的主要特性是它支持共享所有权语义.这意味着多个`std::shared_lock`可以同时拥有同一个互斥锁的共享所有权.当一个`std::shared_lock`拥有互斥锁的共享所有权时,其他线程可以获取互斥锁的共享所有权,但不能获取互斥锁的独占所有权.这在某些需要多个读者和单个写者的情况下非常有用.

`std::shared_lock`的使用方式与`std::unique_lock`类似.你可以在创建`std::shared_lock`时锁定互斥锁,也可以稍后手动调用`std::shared_lock::lock`或`std::shared_lock::lock_shared`方法来锁定互斥锁.当`std::shared_lock`被销毁时,它会自动释放互斥锁.

需要注意的是,`std::shared_lock`只能用于支持共享所有权语义的互斥锁,如`std::shared_mutex`和`std::shared_timed_mutex`.对于不支持共享所有权语义的互斥锁,如`std::mutex`,你应该使用`std::unique_lock`或`std::lock_guard`.


### 3. condition variable
`std::condition_variable`是C++中的一种同步原语,它可以用来在多线程环境中实现复杂的同步模式.以下是一些常见的用法:

1. **等待通知**:一个线程可以使用`std::condition_variable::wait`或`wait_for`/`wait_until`方法来等待另一个线程的通知.当`wait`被调用时,当前线程将被阻塞,直到另一个线程调用`std::condition_variable::notify_one`或`notify_all`方法.

2. **条件等待**:`std::condition_variable::wait`方法还可以接受一个谓词(返回`bool`的函数或函数对象).只有当这个谓词返回`true`时,`wait`才会返回.这可以用来实现条件等待:线程等待某个条件成立.


3. **唤醒一个或多个线程**:可以使用`std::condition_variable::notify_one`方法唤醒一个等待的线程,或者使用`std::condition_variable::notify_all`方法唤醒所有等待的线程.

以下是一个简单的例子,展示了如何使用`std::condition_variable`实现生产者-消费者模式:

```cpp
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

std::queue<int> produced_nums;
std::mutex m;
std::condition_variable cond_var;

void producer() {
    for (int i = 0; ; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        std::lock_guard<std::mutex> lock(m);
        produced_nums.push(i);
        cond_var.notify_all();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        cond_var.wait(lock, []{ return !produced_nums.empty(); });
        std::cout << "consuming " << produced_nums.front() << '\n';
        produced_nums.pop();
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
```

在这个例子中,生产者线程生成数字并将其放入队列,然后通知所有等待的消费者线程.消费者线程等待队列非空,然后从队列中取出并消费数字.

### 5. future

future是表示未来能够得到的值,具体什么时候能够得到,依赖于承诺对象的实现;什么是承诺对象?
promise和packaged_task就是承诺对象,但这些承诺对象set_value的时候,就可以执行future.get()

#### 5.1 async的入参解释

std::async 是 C++11 中引入的一个用于启动异步任务的函数.它的原型如下:

```cpp
template <class Fn, class... Args>
std::future<typename std::result_of<Fn(Args...)>::type> 
    async(std::launch policy, Fn&& f, Args&&... args);
```

这里是 std::async 函数的主要参数及其意义:

policy: 异步任务的启动策略,它是一个 std::launch 类型的枚举值.可能的值有:

std::launch::async:异步执行任务,可能会在新的线程中执行.
std::launch::deferred:延迟执行任务,直到调用 std::future 对象的 get 或 wait 函数时执行,可能在当前线程执行.
std::launch::async | std::launch::deferred:由系统自行选择执行方式,可能异步也可能延迟.
f: 要异步执行的函数或可调用对象.

args...: 传递给函数 f 的参数列表.

std::async 返回一个 std::future 对象,通过这个对象可以获取异步任务的结果.std::future 是一个轻量级的异步结果管理器,它提供了对异步任务的状态查询(是否完成/是否有异常等)以及获取最终结果的功能.

使用 std::async 可以方便地在后台执行任务,而调用 get 函数时,如果任务尚未完成,主线程会等待直到任务完成.这有助于充分利用多核系统的性能,将计算密集型任务分配到不同的线程中执行.

注意:在使用 std::async 时,需要小心选择适当的启动策略,以避免不必要的线程创建和上下文切换.

#### 5.2 promise && packaged_task

关于future,promise,packaged_task,async的理解,以下表述对吗?
promise和packaged_task都是还没有给出具体值的承诺对象,当给出具体数值的时候,就表示承诺实现,可以用于计算.
而async是表示会开一个异步线程进行计算,返回的是一个future的值,如果future的值计算好之后,就可以通过future.get()得到.

所以说,在一个异步计算中,promise和packaged_task是输入端的,async是输出端的.

#### 5.3 shared_future
`std::future`对象的设计是唯一所有权的,也就是说,一旦你从一个`std::future`对象中获取了值,这个`std::future`对象就不能再被用来获取值.这是因为`std::future::get`方法会移动(而不是复制)值或异常,这样可以避免不必要的复制,但也意味着你只能从一个`std::future`对象中获取值一次.

因此,如果你需要在多个线程中共享同一个值,你不能直接使用`std::future`,而应该使用`std::shared_future`.`std::shared_future`对象可以被多次拷贝和读取,这意味着你可以在多个线程中共享同一个值.

在你的代码中,你创建了一个`std::shared_future<int> sf`对象,并将它传递给了三个异步操作.这三个异步操作都可以通过`sf.get()`获取到同一个值.如果你试图直接使用`std::future<int> f`来做同样的事情,你会得到一个编译错误,因为`std::future`对象不能被拷贝.

* shared_future可以直接对一个promise变量使用get_future方法吗

不可以.`std::promise`的`get_future`方法只能返回一个`std::future`对象,而不是`std::shared_future`对象.如果你想要一个`std::shared_future`对象,你需要首先从`std::promise`获取一个`std::future`对象,然后调用`std::future`的`share`方法来获取一个`std::shared_future`对象.例如:

```cpp
std::promise<int> p;
std::future<int> f = p.get_future();
std::shared_future<int> sf = f.share();
```

在这段代码中,`sf`是一个`std::shared_future`对象,它与`f`共享同一个状态,也就是说,它们都可以获取到同一个值.


#### 5.4 packaged_task


是的,你的理解是正确的.

在你的代码示例中,`std::async`用于异步执行`is_prime`函数并返回一个`std::future`对象.这个`std::future`对象可以用来获取`is_prime`函数的返回值.在等待`is_prime`函数完成的同时,主线程可以继续执行其他任务.

`std::async`是一个高级工具,它自动处理线程的创建和销毁,使得异步编程变得更简单.如果你只需要在后台运行一个任务并获取其结果,那么`std::async`通常是最好的选择.

相比之下,`std::packaged_task`提供了更多的灵活性,但也需要更多的管理工作.`std::packaged_task`只是将一个任务和一个`std::future`对象关联起来,它并不创建线程.你需要自己创建一个`std::thread`并将`std::packaged_task`对象传递给它.这使得你可以更精细地控制线程的创建和销毁,以及任务的调度.例如,你可以将任务提交给一个线程池,或者在特定的时间点启动线程.

所以,如果你只是在简单的场景中使用异步编程,那么`std::async`通常是最好的选择.如果你需要更精细的控制,或者你正在实现一个线程池,那么`std::packaged_task`可能是更好的选择.


### 6. others
#### 6.1 如果函数返回一个future,对这个future不调用get(),会发生什么
如果你调用`std::async`但不将返回值存储在一个`std::future`对象中,那么一个临时的`std::future`对象会被创建.这个临时对象会在表达式结束时被销毁,销毁时会阻塞等待异步任务完成.

这就是为什么如果你不想阻塞当前线程,你不能简单地忽略`std::async`的返回值.你需要将返回的`std::future`对象存储在某个地方,以便在适当的时候等待任务完成.

如果你创建了一个`std::future`对象,但是没有调用`get()`方法,那么在`std::future`对象被销毁时,如果关联的异步操作(例如`std::async`)还没有完成,那么程序会阻塞,直到异步操作完成.

这是因为`std::future`的析构函数会检查关联的异步操作是否已经完成.如果没有完成,析构函数会阻塞,直到异步操作完成.这是为了确保异步操作能够安全地完成,而不会在还没有完成的情况下被强制停止.

如果你不想在`std::future`对象被销毁时阻塞,你可以调用`std::future::detach()`方法.这将使`std::future`对象与其关联的异步操作分离,这样,即使`std::future`对象被销毁,异步操作也会继续运行.

需要注意的是,如果你没有调用`get()`方法,那么你将无法获取异步操作的结果.此外,`get()`方法只能被调用一次,因为调用`get()`方法后,`std::future`对象会变为无效状态.

函数的返回值哪怕没有用变量接着,其实也是存在的,在外部函数结束的时候会被析构.

而`future`的析构又要确保`get()`方法完成,所以如果不接着,就会产生阻塞.


### 99. quiz
#### 1. new操作是如何保证线程安全的?
new操作的线程安全性是通过内存管理器实现的.内存管理器会使用一种称为锁的机制来保证在同一时刻只有一个线程可以分配或释放内存.当一个线程正在进行new操作时,其他试图进行new操作的线程将会被阻塞,直到第一个线程完成new操作.

需要注意的是,虽然new操作本身是线程安全的,但是如果你在多线程环境中使用new操作创建的对象,你仍然需要确保对这些对象的访问是线程安全的.例如,如果两个线程同时访问和修改同一个对象,可能会导致数据竞争和未定义的行为,除非你使用了适当的同步机制(如互斥锁)来保护这个对象.

在C++中,`new`操作本身是线程安全的.C++标准库保证了在多线程环境中,不同线程可以同时进行`new`操作而不会发生冲突.

`new`操作的线程安全性是通过内存管理器实现的.内存管理器会使用一种称为锁的机制来保证在同一时刻只有一个线程可以分配或释放内存.当一个线程正在进行`new`操作时,其他试图进行`new`操作的线程将会被阻塞,直到第一个线程完成`new`操作.

需要注意的是,虽然`new`操作本身是线程安全的,但是如果你在多线程环境中使用`new`操作创建的对象,你仍然需要确保对这些对象的访问是线程安全的.例如,如果两个线程同时访问和修改同一个对象,可能会导致数据竞争和未定义的行为,除非你使用了适当的同步机制(如互斥锁)来保护这个对象.

#### 2. 为什么一定要用while循环,而不是if判断?

```c++
  muduo::MutextLock mutex;
  muduo::Condition cond(mutex);
  std:deque<int> queue;
  
  //消费者
  int dequeue(){
      // queue pop掉最后一个,并返回
      MutexLockGuard lock(mutex);
      while(queue.emtpy()){ // 不能用if,必须用while,避免虚假唤醒
          cond.wait(); // 这一步会unlock mutex,并进入等待,不会与其他线程产生死锁
      }
      int top = queue.front();
      queue.pop_front();
      return top;
  }
  ```

- 简单来说就是cv有可能会出现[虚假唤醒](https://www.zhihu.com/question/271521213)的情况,用while,不用if的话就可以多次检验.
- 给一个虚假唤醒的场景,一个线程A,一个线程B被notify,但是A还没有获得锁,B线程先获得了锁,并消费了队列中的数据(或者说notify的条件又变成不满足了),线程B结束后,A获得了锁,但这个时候条件已经不满足了.

- 当一个线程在条件变量上调用`.wait()`方法并进入等待状态时,如果后来被另一个线程通过`.notify()`或`.notify_all()`唤醒,那么它会从`.wait()`方法的下一行代码开始执行.

- 但是,需要注意的是,唤醒并不意味着条件已经满足.这就是为什么我们通常在一个`while`循环中调用`.wait()`方法,循环的条件就是我们等待的条件.这样,每次线程被唤醒时,它都会检查条件是否满足,如果条件不满足,它会再次调用`.wait()`方法进入等待状态.
-   - 这就是所谓的"虚假唤醒",即线程被唤醒,但是条件并未满足.使用`while`循环可以避免因虚假唤醒导致的问题.


#### 3. atomic实现原理
- 不同平台原子操作的实现不一样,但多线程导致的数据冲突都是因为多核cpu同时在跑一份数据,本质上都是保证这个数据在不同cpu的时候,有且只有一个在进行操作.下面是cacheline lock的实现方法

- 首先每个cpu核心都有其对应的高速cache

![在这里插入图片描述](https://s2.loli.net/2022/04/14/IxfwdV2vROmhnS8.png)

1. CPU1发出"Read Invalidate"消息,其他CPU将原子变量所在的缓存无效,并从Cache返回数据.CPU1将Cache line置成Exclusive状态.然后将该**cache line标记locked**
2. 然后CPU1读取原子变量,修改,最后写入cache line.
3. 将cache line置位unlocked.

在步骤(1)和(3)之间,如果其他CPU(例如CPU1)尝试执行一个原子递增操作,CPU1会发送一个"Read Invalidate"消息,CPU0收到消息后,检查对应的cache line的状态是locked,暂时不回复消息(CPU1会一直等待CPU0回复Invalidate Acknowledge消息).直到cache line变成unlocked.这样就可以实现原子操作.我们称这种方式为锁cache line.这种实现方式必须要求操作的变量位于一个cache line.

#### 4.多核cpu的缓存以及如何保持缓存一致性
    (https://blog.csdn.net/zhizhengguan/article/details/121275331)
- 如果对多核cpu还存疑,可以继续看这个.


### 99. quiz
### 1. 什么是虚假唤醒？为什么会有虚假唤醒？可以避免虚假唤醒吗？

- 什么是虚假唤醒？
虚假唤醒（spurious wakeup）是指线程在等待条件变量时，即使没有任何线程调用`notify_one`或`notify_all`，也会被唤醒的情况。这种现象在某些操作系统和硬件平台上可能会发生。

- 为什么会有虚假唤醒？
虚假唤醒的原因可能包括：
- **操作系统的调度策略**：操作系统可能会出于各种原因唤醒等待的线程，例如资源重新分配或优先级调整。
- **硬件中断**：硬件中断可能会导致等待的线程被唤醒。
- **其他系统级别的事件**：系统级别的事件（如信号处理）也可能导致线程被唤醒。

- 可以避免虚假唤醒吗？
虚假唤醒是操作系统和硬件层面的现象，无法完全避免。但是，可以通过编写健壮的代码来正确处理虚假唤醒。

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
#### 进程状态
在操作系统中，进程通常有以下几种状态：

1. **新建（New）**：进程正在被创建。
2. **就绪（Ready）**：进程已经创建并等待被分配 CPU 时间片。
3. **运行（Running）**：进程正在执行。
4. **等待（Waiting）或阻塞（Blocked）**：进程正在等待某个事件（如 I/O 操作完成或资源可用）。
5. **终止（Terminated）或完成（Completed）**：进程已经完成执行或被终止。

### 进程状态转换图

以下是一个简单的进程状态转换图：

```
        +-------+       +-------+
        | New   |       | Ready |
        +-------+       +-------+
            |               |
            v               v
        +-----------------------+
        |       Running         |
        +-----------------------+
            |               |
            v               v
        +-------+       +-------+
        | Blocked|       | Terminated|
        +-------+       +-------+
```

### 进程状态转换说明

1. **新建到就绪**：进程创建完成后，进入就绪状态，等待被调度执行。
2. **就绪到运行**：调度器选择一个就绪进程，并将其分配给 CPU 执行。
3. **运行到等待**：进程在执行过程中需要等待某个事件（如 I/O 操作），进入等待状态。
4. **等待到就绪**：等待的事件完成后，进程重新进入就绪状态，等待被调度执行。
5. **运行到就绪**：进程在执行过程中被操作系统中断，放回就绪队列，等待下一个调度周期。
6. **运行到终止**：进程执行完成或被终止，进入终止状态。

### 示例代码中的线程状态

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
* 等待状态：当线程调用 `cv.wait()` 时，它会进入等待状态，直到被条件变量唤醒。线程在等待期间不会占用 CPU 资源。
* 就绪：当线程调用 `yield()` 时，它会主动让出 CPU 使用权，进入就绪状态，等待被调度执行。线程不会继续占用 CPU 资源，直到操作系统再次分配时间片。
* 运行（忙等待）：`while(!ready)`：忙等待是指线程在等待某个条件满足时，不断地检查该条件，而不让出 CPU 使用权。线程在等待期间仍然占用 CPU 资源，直到时间片耗尽或条件满足。

#### 解释

1. **等待线程**：
   - `second`和`third`函数中的线程使用`cv.wait(lock, [this]() { return k == 1; });`和`cv.wait(lock, [this]() { return k == 2; });`来等待条件变量。
   - 这些等待操作都在一个循环中进行，以确保即使发生虚假唤醒，线程也会继续等待，直到条件满足。

2. **通知线程**：
   - `first`函数在完成任务后，调用`cv.notify_all()`通知所有等待的线程。
   - `second`函数在完成任务后，调用`cv.notify_one()`通知一个等待的线程。

通过这种方式，可以确保线程在条件满足之前不会继续执行，从而正确处理虚假唤醒。

