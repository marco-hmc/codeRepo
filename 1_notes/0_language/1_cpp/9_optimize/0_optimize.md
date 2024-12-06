## c++编程范式

### 2. soa和aos
好的，让我们通过一个具体的例子来解释 SOA（Structure of Arrays）和 AOS（Array of Structures）。

假设我们有一个粒子系统，每个粒子都有位置（x，y，z）和速度（vx，vy，vz）。

在 AOS（Array of Structures）方式中，我们会创建一个粒子结构，然后创建这个结构的数组：

```cpp
struct Particle
{
    float x, y, z; // 位置
    float vx, vy, vz; // 速度
};

std::array<Particle, 1000> particles;
```

在这种情况下，如果我们想更新所有粒子的位置，我们需要遍历整个数组，这可能会导致缓存未命中，因为位置和速度数据在内存中是交错的。

在 SOA（Structure of Arrays）方式中，我们将每个属性存储在一个单独的数组中：

```cpp
struct Particles
{
    std::array<float, 1000> x, y, z; // 位置
    std::array<float, 1000> vx, vy, vz; // 速度
};

Particles particles;
```

在这种情况下，如果我们想更新所有粒子的位置，我们可以连续地访问 x、y 和 z 数组，这有助于提高缓存命中率，因为这些数据在内存中是连续的。

总的来说，SOA 和 AOS 是两种不同的数据组织方式，选择哪种方式取决于你的具体需求和访问模式。

### 3. CRTP
CRTP，全称 Curiously Recurring Template Pattern（奇异递归模板模式），是一种在 C++ 中使用的编程技巧。这种模式涉及到一个类模板，它以自己的派生类作为模板参数。

CRTP 可以用于实现编译时的多态性，也就是说，它可以在编译时决定调用哪个函数，而不是在运行时。这可以提高性能，因为它避免了虚函数调用的开销。

以下是一个 CRTP 的例子：

```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // 实现具体的功能
    }
};
```

在这个例子中，`Base` 是一个模板类，它有一个 `interface` 方法，这个方法调用 `implementation` 方法。`Derived` 类继承自 `Base`，并提供 `implementation` 方法的实现。

当我们调用 `interface` 方法时，实际上调用的是 `Derived` 类的 `implementation` 方法。这是在编译时决定的，所以没有运行时的虚函数调用开销。

### 4. CAS
CAS，全称 Compare-and-Swap（比较并交换），是一种用于实现并发算法的原子操作。这种操作可以在多线程环境中安全地读取和更新共享数据，而无需使用锁。

CAS 操作接受三个参数：一个内存位置、一个预期的旧值和一个新值。如果内存位置的当前值与预期的旧值匹配，那么 CAS 操作就会将新值写入内存位置。否则，操作不会进行任何更改。无论哪种情况，CAS 操作都会返回内存位置的原始值。

CAS 操作的一个关键特性是它是原子的，也就是说，它不会被其他线程的操作中断。这使得它在实现无锁数据结构和其他并发算法时非常有用。

以下是一个简单的 CAS 操作的伪代码示例：

```cpp
int compare_and_swap(int* ptr, int old_val, int new_val) {
    int original_val = *ptr;
    if (original_val == old_val) {
        *ptr = new_val;
    }
    return original_val;
}
```

在实际使用中，CAS 操作通常由硬件直接支持，并通过特殊的机器指令实现。在 C++ 中，你可以使用 `<atomic>` 头文件中的 `std::atomic` 类来进行 CAS 操作。

### 5. CAS-copay and swap

* 什么是CAS(copy and swap)?有什么用?
  在C++编程中,"copy-and-swap"(CAS)是一种常用的技术,用于实现赋值操作符(operator=).CAS的基本思想是先创建一个副本,然后交换副本和原对象.


* 在什么场景下使用?
  实现赋值操作符:CAS是实现赋值操作符(operator=)的一种常见方法.它可以简化代码,并提供强异常安全性.

  提供强异常安全性:如果你的代码需要在异常发生时保持一致性(即,不会因为异常而处于无效状态),那么CAS可能是一个好的选择.在CAS中,如果复制操作抛出异常,原对象不会被修改.

  避免自我赋值问题:在传统的赋值操作符实现中,你需要检查自我赋值(即,a = a).但是在CAS中,由于赋值操作符接受的是一个副本,所以不需要检查自我赋值.

  然而,CAS并不适用于所有情况.CAS的一个主要缺点是它需要进行复制操作,这可能会导致性能问题.如果你的对象很大,或者复制操作很昂贵,那么你可能需要使用其他方法来实现赋值操作符.

### 6. COW

1. **什么是COW(copy on write)?有什么用?**

   COW，即 Copy On Write，是一种优化策略。在这种策略下，当对象被复制时，并不立即进行复制，而是等到对象被修改时才进行复制。这种策略可以避免不必要的复制操作，从而提高程序的性能。

2. **在什么场景下使用?**

   COW 技术通常在需要复制大量数据，但又不经常修改数据的场景中使用。例如，在字符串操作中，如果一个字符串被复制多次，但只有少数几次会修改字符串，那么使用 COW 技术可以大大提高性能。

3. **怎么实现?**

   COW 技术的实现通常依赖于引用计数。每个对象都有一个引用计数，表示有多少个引用指向这个对象。当对象被复制时，不复制对象本身，而是增加引用计数。当对象被修改时，检查引用计数，如果引用计数大于1，那么就复制对象，然后修改复制后的对象，同时减少原对象的引用计数。如果引用计数等于1，那么直接修改对象。


### 6. RVO
```c++
#include <iostream>

class MyObject {
public:
    MyObject() {
        std::cout << "Constructor called" << std::endl;
    }

    MyObject(const MyObject& other) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

MyObject createObject() {
    MyObject obj;
    return obj;
}

int main() {
    MyObject newObj = createObject();
    return 0;
}
```
1. 什么是RVO？

   RVO，全称Return Value Optimization（返回值优化），是C++编译器的一种优化技术。当函数返回一个局部对象时，RVO允许编译器省略额外的拷贝或移动构造函数的调用，直接在调用位置构造返回对象。

2. RVO有什么好处？

   RVO的主要好处是提高性能。通过省略额外的拷贝或移动构造函数的调用，RVO可以减少不必要的临时对象的创建，从而减少内存使用和提高运行速度。对于大型对象或者拷贝操作开销大的对象，RVO的性能优势更为明显。

3. 怎么用RVO？

   你不需要做任何特殊的操作来使用RVO，它是由编译器自动进行的。只要你的函数返回一个局部对象，编译器就可能会应用RVO。但是，你应该注意的是，RVO并不是在所有情况下都会发生，它取决于编译器的实现和你的代码结构。在你的代码中，`createObject`函数返回一个`MyObject`对象，这个对象立即被赋值给`newObj`，这是RVO可能会发生的一个场景。



#### **17. 考虑使用延迟计算**

一个延迟计算的例子：

    class String{....}
    String s1 = "Hello";
    String s2 = s1;  //在正常的情况下，这一句需要调用new操作符分配堆内存，然后调用strcpy将s1内的数据拷贝到s2里面。但是我们此时s2并没有被使用，所以我们不需要s2，这个时候如果让s2和s1共享一个值，就可以减小这些开销

使用延迟计算进行读操作和写操作：

    String s = "Homer's Iliad";
    cout << s[3];
    s[3] = 'x';
首先调用operator[] 用来读取string的部分值，但是第二次调用该函数式为了完成写操作。读取效率较高，写入因为需要拷贝，所以效率较低，这个时候可以推迟作出是读操作还是写操作的决定。

延迟策略进行数据库操作：有点类似之前写web 的时候，把数据放在内存和数据库两份，更新的时候只更新内存，然后隔一段时间（或者等到使用的时候）去更新数据库。
在effective c++里面，则是更加专业的将这个操作封装成了一个类，然后把是否更新数据库弄成一个flag。以及使用了mutable关键字，来修改数据

延迟表达式：
    
    Matrix<int> m1(1000, 1000), m2(1000, 1000);
    m3 = m1 + m2;
    因为矩阵的加法计算量太大（1000*1000）次计算，所以可以先用表达式表示m3是m1和m2的和，然后真正需要计算出值的时候再真的进行计算（甚至计算的时候也只计算m3[3][2]这样某一个位置的值）





#### 零拷贝技术

* 概念

  * **零拷贝（ zero-copy ）**技术可以有效地改善数据传输的性能，在内核驱动程序（比如网络堆栈或者磁盘存储驱动程序）处理 I/O 数据的时候，零拷贝技术可以在某种程度上减少甚至完全避免不必要 CPU 数据拷贝操作。
  * **零拷贝就是一种避免 CPU 将数据从一块存储拷贝到另外一块存储的技术**。**针对操作系统中的设备驱动程序、文件系统以及网络协议堆栈而出现的各种零拷贝技术极大地提升了特定应用程序的性能，并且使得这些应用程序可以更加有效地利用系统资源**。这种性能的提升就是**通过在数据拷贝进行的同时，允许 CPU 执行其他的任务来实现的**
  * 概括如下
    * **避免数据拷贝**
      * **避免操作系统内核缓冲区之间进行数据拷贝操作**
      * **避免操作系统内核和用户应用程序地址空间这两者之间进行数据拷贝操作**
      * **用户应用程序可以避开操作系统直接访问硬件存储**
      * **数据传输尽量让 DMA 来做**
    * **综合目标**
      * **避免不必要的系统调用和上下文切换**
      * 需要拷贝的数据可以先被缓存起来
      * 对数据进行处理尽量让硬件来做

* 零拷贝使用场景

  * 在写一个服务端程序时（Web Server或者文件服务器），文件下载是一个基本功能。这时候服务端的任务是：将服务端主机磁盘中的文件不做修改地从已连接的socket发出去，我们通常用下面的代码完成：

    ```c++
    while((n = read(diskfd, buf, BUF_SIZE)) > 0)
       write(sockfd, buf , n);
    ```

  * 基本操作就是循环的从磁盘读入文件内容到缓冲区，再将缓冲区的内容发送到socket。但是由于Linux的I/O操作默认是缓冲I/O。这里面主要使用的也就是read和write两个系统调用，我们并不知道操作系统在其中做了什么。实际上在以上I/O操作中，发生了多次的数据拷贝。

  * 当应用程序访问某块数据时，操作系统首先会检查，是不是最近访问过此文件，文件内容是否缓存在内核缓冲区，如果是，操作系统则直接根据read系统调用提供的buf地址，将内核缓冲区的内容拷贝到buf所指定的用户空间缓冲区中去。如果不是，**操作系统则首先将磁盘上的数据拷贝的内核缓冲区，这一步目前主要依靠DMA来传输**，然后再把内核缓冲区上的内容拷贝到用户缓冲区中。接下来，write系统调用再把用户缓冲区的内容拷贝到网络堆栈相关的内核缓冲区中，最后socket再把内核缓冲区的内容发送到网卡上

    <img src="imgs/os/multi_copy.png" alt="multi_copy" style="zoom:80%;" />

  * 从上图中可以看出，共产生了**两次系统调用，四次数据拷贝**，即使使用了DMA来处理了与硬件的通讯，CPU仍然需要处理两次数据拷贝，与此同时，在用户态与内核态也发生了多次上下文切换，无疑也加重了CPU负担。在此过程中，我们没有对文件内容做任何修改，那么在内核空间和用户空间来回拷贝数据无疑就是一种浪费，而零拷贝主要就是为了解决这种低效性

  * 零拷贝主要的任务就是避免CPU将数据从一块存储拷贝到另外一块存储，主要就是利用各种零拷贝技术，避免让CPU做大量的数据拷贝任务，减少不必要的拷贝，或者让别的组件来做这一类简单的数据传输任务，让CPU解脱出来专注于别的任务。这样就可以让系统资源的利用更加有效

* 零拷贝技术使用

  * **使用mmap**

    * 减少拷贝次数的一种方法是调用mmap()来代替read调用：

      ```c++
      buf = mmap(diskfd, len);
      write(sockfd, buf, len);
      ```

    * 应用程序调用mmap()，**磁盘上的数据会通过DMA被拷贝的内核缓冲区**，**接着操作系统会把这段内核缓冲区与应用程序共享**，**这样就不需要把内核缓冲区的内容往用户空间拷贝**。应用程序**再调用write()**，**操作系统直接将内核缓冲区的内容拷贝到socket缓冲区中**，这一切都发生在内核态，最后，socket缓冲区再把数据发到网卡去

    <img src="imgs/os/mmap.png" alt="mmap" style="zoom:80%;" />

  * 使用mmap替代read很明显减少了一次拷贝，当拷贝数据量很大时，无疑提升了效率。**但是使用mmap是有代价的。当你使用mmap时，你可能会遇到一些隐藏的陷阱。例如，当你的程序map了一个文件，但是当这个文件被另一个进程截断(truncate)时, write系统调用会因为访问非法地址而被SIGBUS信号终止**。SIGBUS信号默认会杀死你的进程并产生一个coredump,如果你的服务器这样被中止了，那会产生一笔损失。通常可以使用以下解决方案避免这种问题：

    * **为SIGBUS信号建立信号处理程序**

      * 当遇到SIGBUS信号时，信号处理程序简单地返回，write系统调用在被中断之前会返回已经写入的字节数，并且errno会被设置成success，但是这是一种糟糕的处理办法，因为你并没有解决问题的实质核心

    * **使用文件租借锁**

      * 通常我们使用这种方法，在**文件描述符上使用租借锁**，我们为文件向内核申请一个租借锁，当其它进程想要截断这个文件时，内核会向我们发送一个实时的`RT_SIGNAL_LEASE`信号，告诉我们内核正在破坏你加持在文件上的读写锁。这样在程序访问非法内存并且被SIGBUS杀死之前，你的write系统调用会被中断。write会返回已经写入的字节数，并且置errno为success。我们应该在mmap文件之前加锁，并且在操作完文件后解锁：

        ```c++
        if(fcntl(diskfd, F_SETSIG, RT_SIGNAL_LEASE) == -1) {
            perror("kernel lease set signal");
            return -1;
        }
        /* l_type can be F_RDLCK F_WRLCK  加锁*/
        /* l_type can be  F_UNLCK 解锁*/
        if(fcntl(diskfd, F_SETLEASE, l_type)){
            perror("kernel lease set type");
            return -1;
        }
        ```

* 使用sendfile

  * sendfile原型

    ```c++
    #include<sys/sendfile.h>
    
    ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    ```

  * 系统调用`sendfile()`在代表输入文件的描述符`in_fd`和代表输出文件的描述符`out_fd`之间传送文件内容（字节）。描述符`out_fd`**必须指向一个套接字**，而`in_fd`指向的文件必须是可以`mmap`的。这些局限限制了sendfile的使用，使**sendfile只能将数据从文件传递到套接字上**，反之则不行。使用sendfile不仅减少了数据拷贝的次数(1次)，还减少了上下文切换(一次调用，两次切换)，数据传送始终只发生在kernel space

    <img src="imgs/os/sendfile.png" alt="sendfile" style="zoom:80%;" />

  * 在调用sendfile时，如果有其它进程截断了文件会发生什么呢？假设我们没有设置任何信号处理程序，**sendfile调用仅仅返回它在被中断之前已经传输的字节数，errno会被置为success**。如果我们在调用sendfile之前给文件加了锁，sendfile的行为仍然和之前相同，我们还会收RT_SIGNAL_LEASE的信号

  * sendfile仍然存在一次拷贝，就是页缓存到socket缓存的拷贝。现在我们仅仅需要把**缓冲区描述符传到socket缓冲区，再把数据长度传过去，这样DMA控制器直接将页缓存中的数据打包发送到网络中就可以了**

    <img src="imgs/os/zero_sendfile.png" alt="zero_sendfile" style="zoom:80%;" />

    * sendfile系统调用利用DMA引擎将文件内容拷贝到内核缓冲区去，然后将带有文件位置和长度信息的缓冲区描述符添加socket缓冲区去，这一步不会将内核中的数据拷贝到socket缓冲区中，**DMA引擎会将内核缓冲区的数据拷贝到协议引擎中去，避免了最后一次拷贝**

    * 不过这一种收集拷贝功能是需要硬件以及驱动程序支持的。**需要网卡支持 SG-DMA**（*The Scatter-Gather Direct Memory Access*）技术（和普通的 DMA 有所不同）

    * 可以在 Linux 系统通过下面这个命令，查看网卡是否支持 scatter-gather 特性：

      ```shell
      $ ethtool -k eth0 | grep scatter-gather
      scatter-gather: on
      ```

* 使用splice

  * sendfile只适用于将数据**从文件拷贝到套接字**上，限定了它的使用范围。Linux在2.6.17版本引入splice系统调用，用于**在两个文件描述符中移动数据**

  * 原型

    ```c++
      #define _GNU_SOURCE         /* See feature_test_macros(7) */
      #include <fcntl.h>
      ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);
    ```

      * splice调用在**两个文件描述符之间移动数据**，而**不需要数据在内核空间和用户空间来回拷贝**。他从`fd_in`拷贝`len`长度的数据到`fd_out`，**但是有一方必须是管道设备，这也是目前splice的一些局限性**。如果`fd_in`是一个管道文件描述符，那么off_in必须设为NULL；如果不是，那么表示从输入数据流的何处开始读取数据，此时若`fd_in`为NULL，则表示从输入数据流的当前偏移位置读入；不为NULL，则指出具体的偏移位置。``fd_out/off_out`同理使用与于输出流。flags参数有以下几种取值
      * SPLICE_F_MOVE ：尝试去移动数据而不是拷贝数据。这仅仅是对内核的一个小提示：**如果内核不能从pipe移动数据或者pipe的缓存不是一个整页面，仍然需要拷贝数据**。Linux最初的实现有些问题，**所以从2.6.21开始这个选项不起作用**，后面的Linux版本应该会实现
      * SPLICE_F_NONBLOCK ：splice 操作不会被阻塞。然而，如果文件描述符没有被设置为不可被阻塞方式的 I/O ，那么调用 splice 有可能仍然被阻塞
      * SPLICE_F_MORE： 后面的splice调用会有更多的数据。

  * splice调用利用了Linux提出的**管道缓冲区机制**， 所以**至少一个描述符要为管道**。以上几种零拷贝技术都是**减少数据在用户空间和内核空间拷贝技术实现的**，**但是有些时候，数据必须在用户空间和内核空间之间拷贝**。这时候，我们只能**针对数据在用户空间和内核空间拷贝的时机上下功夫了**。**Linux通常利用写时复制(copy on write)来减少系统开销，这个技术又时常称作COW**

* 使用tee

  * tee函数用于**两个管道之间复制数据**，也是零拷贝操作，它不消耗数据，源文件描述符上面的数据仍然可以用于后续读操作

  * 原型

    ```c++
    #include <fcntl.h>
    ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
    ```

  * 上述参数与splice相同，但fd_in和fd_out都必须是管道文件描述符。成功返回两个文件描述符之间复制的数据，返回0表示没任何数据复制，失败返回-1并设置errno

