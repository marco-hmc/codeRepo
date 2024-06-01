## io复用

### 1. 基本概念

#### 1.1 什么是io复用
IO复用（Input/Output Multiplexing，也做io多路复用）是一种可以让单个线程处理多个IO操作的技术。在IO复用模型中，线程可以同时等待多个IO操作（例如，多个socket连接），当任何一个IO操作完成时，线程就可以处理这个操作。

IO复用的主要优点是可以提高线程的利用率，因为线程不需要为每个IO操作单独等待，而是可以在等待一个IO操作的同时，处理其他的IO操作。这对于需要处理大量并发连接的网络服务器来说，是非常重要的。

在Linux中，常见的IO复用技术有select、poll和epoll。在Windows中，常见的IO复用技术有select和IOCP（Input/Output Completion Port）。在Java中，NIO（Non-blocking IO）库提供了IO复用的支持。

#### 1.2 io操作是什么？
IO操作，全称为输入/输出操作，是计算机系统中数据在内部（如CPU、内存）和外部设备（如硬盘、网络接口、打印机）之间传输的过程。

linux一个突出的设计理念在于，将一切外部设备看成一个文件来操作。任何东西都挂在文件系统之上，即使它们不是文件，也以文件的形式来呈现。这些一切外部设部都享有与内部文件一样的接口。

所以`串口`，`内存`，`usb`，`进程信息`，`网卡`，`网络通讯socket`等等一切外部设备的数据输入输入就是io的过程。

一般来说，在网络编程的语境下，io多路复用是指单个线程中同时处理多个socket连接的技术。这种技术可以提高线程的利用率，因为线程在等待一个IO操作完成的同时，可以处理其他的IO操作。

#### 1.3 linux下如何实现io复用？

在Linux系统中，实现IO复用主要有以下几种方式：

select：select是最早的IO复用解决方案，它可以同时监控多个文件描述符（例如socket）。当其中任何一个文件描述符准备好读、写或异常时，select就会返回。select的主要缺点是它支持的文件描述符数量有限（通常最多1024个），并且效率随着文件描述符数量的增加而降低。

poll：poll和select类似，但它没有最大文件描述符数量的限制。然而，poll的效率仍然随着文件描述符数量的增加而降低。

epoll：epoll是Linux特有的IO复用解决方案，它没有最大文件描述符数量的限制，而且效率不会随着文件描述符数量的增加而降低。epoll使用一种称为事件驱动的方式，只关注活跃的文件描述符，因此比select和poll更高效。

#### 1.4 linux下的五种IO模型
？？？
IO模型是描述输入/输出操作如何进行的一种模型。在网络编程中，常见的IO模型有以下四种：

阻塞IO模型：在这种模型中，IO操作会阻塞调用线程，直到操作完成。例如，当线程执行一个读操作时，它会被阻塞，直到数据可用并已读入内存。

非阻塞IO模型：在这种模型中，IO操作不会阻塞调用线程。如果数据不可用，操作会立即返回一个错误。

IO复用模型：在这种模型中，线程可以同时等待多个IO操作。当任何一个IO操作完成时，线程就可以处理这个操作。这种模型可以让线程在等待一个IO操作的同时，处理其他的IO操作。

信号驱动IO模型：在这种模型中，线程可以请求在IO操作完成时接收一个信号。当收到这个信号时，线程就可以处理IO操作。

异步IO模型：在这种模型中，线程启动一个IO操作，然后继续执行其他任务。当IO操作完成时，线程会收到一个通知。


### 2. io复用技术

#### 2.1 select

#### 2.2 poll

#### 2.3 epoll



#### 2.1 阻塞I/O - BIO

- ***流程图：***

  ![在这里插入图片描述](https://s2.loli.net/2022/05/09/q8FhicmZMf4oCBT.png)

  > PS: `read()`一般是指本地读取数据，通过硬盘文件；`recvfrom()`一般是指从`socket`接收数据，通过网络中的`socket`文件；

- ***文字说明***

  1. `application`向`kernel`发起`system call`的`read()/recvfrom()`请求
  2. `kernel`如果准备好了，就从`kernel space`拷贝数据到`user space`
  3. 拷贝完成时，则返回ok。
  4. 此时`application`继续。

- ***适用情况***

  - 简单易用，是本地IO的首选

- ***不足***

  - 如果是网络IO的话，要么就是空等，要么就是每一个线程开一个`socket()`。前者耗费时间，后者耗费资源



#### 2.2 非阻塞I/O - NIO

- ***流程图***

  ![~replace~/assets/images/io-model/nio.png](https://s2.loli.net/2022/02/18/YJpWBrs53A4vFuS.gif)

- ***文字说明***

  1. `application`向`kernel`发起`system call`的`read()/recvfrom()`请求
  2. `kernel`如果没有准备好，就返回`EWOULDBLOCK`这个错误码。
  3. 继续回到`application`，该干嘛干嘛，然后再次发起`read()/recvfrom()`请求
  4. `kernel`如果准备好了，就从`kernel space`拷贝数据到`user space`
  5. 拷贝完成时，则返回ok
  6. 此时`application`继续。

- ***适用情况***

  - 网络IO情况。通过反复发起`system call`，如果没准备好，我就继续该干嘛干嘛，但是在数据拷贝的过程中，进程还是阻塞的。

- ***不足***

  - `system call`是比较耗费`cpu`的操作，如果频繁地发起`system call`也不是一个明智之举。

  

#### 2.3 I/O复用 - (select/poll/epoll)

- ***流程图***

  ![~replace~/assets/images/io-model/io_select.png](https://s2.loli.net/2022/02/18/14kRnPlX5HEU9dr.gif)

- ***文字说明***

  1. `application`向`kernel`发起`system call`的`select()`请求，向`kernel`传入若干个`file descriptor`和操作目的(read, write)，这些一般被打包为`fd_set`数据。
  2. `kernel`同时检测若干个文件，当其中一个或多个`file descriptor`就绪，返回可执行的。
  3. `application`收到准备就绪的`file descriptor`后，对他们发起发起`system call`的`read()/recvfrom()`请求
  4. `kernel`这时候准备好了，就从`kernel space`拷贝数据到`user space`
  5. 拷贝完成时，则返回ok
  6. 此时`application`继续。

- ***适用情况***

  - 优化了非阻塞IO大量发起`system call`的问题，其核心思想在于通过一次发起大量IO请求，优先处理已经准备好的。
  - IO复用还是阻塞的

- ***不足***

  - `fd_set`受限于系统设定的`FD_SETSIZE`大小
  - 如果`fd_set`数目很大，需要轮询所有fd找出就绪的fd,这里的性能也很大。

#### 2.4 异步I/O - (AIO)

- ***流程图***

![~replace~/assets/images/io-model/aio.png](https://s2.loli.net/2022/02/18/E6dwWuM3Sljhiga.gif)

- ***文字说明***
  1. `application`向`kernel`发起`system call`的`aio_read()`请求，`kernel`立马返回。
  2. `application`继续运行，而`kernel`则会一直等待数据准备。
  3. `kernel`准备好数据时，`kernel`不需要让`application`再次发次请求，直接将数据从`kernel space`拷贝到`user space`
  4. 当拷贝完成时，`kernel`向`application`发送完成信号。
- ***适用情况***
  - 理论上，性能比之前的都要好。`application`可以完全不用
- ***不足***
  - 太复杂了，比如网络框架`netty 5.0`被废弃的原因就在于引入AIO提高效率，但变得非常复杂，而性能没有得到太明显优化。

#### 2.5 信号驱动I/O - SIGIO

- ***流程图***

![~replace~/assets/images/io-model/sio.png](https://s2.loli.net/2022/02/18/1v8xMSHKazQGfTi.gif)

- ***特别说明***

  ​	这种IO模型相对复杂，一般不使用，相关的资料也比较少。如果有感兴趣的可以点击这里查看[Signal-Driven I/O for Sockets](http://www.masterraghu.com/subjects/np/introduction/unix_network_programming_v1.3/ch25lev1sec2.html#ch25lev1sec2)

  

#### 2.6 总结

![image-20220218222819682](https://s2.loli.net/2022/02/18/xYu6VHtAJRP2QNl.png)

- ***阻塞与非阻塞的区分***

  ​	两者区别在于，非阻塞IO会不断发生system call。

- ***同步和异步的区分***

  ​	两者区别在于，从`kernel space`拷贝到`user space`时，进程是否还在执行。哪怕是NIO，知道数据就绪后，也是等待数据拷贝完成后，再执行下一步；而AIO则是不管`kernel space`拷贝完成没都继续进行，`kernel space`拷贝完成才告诉`application`

- ***IO复用也可以设置为非阻塞模式的***

### 3. select/poll/epoll

​	IO复用模型中又可进一步分为select、poll和epoll方法。前面出于排版的原因，反正这下面来进一步讲解

#### 3.1 select

- ***代码***

  ```cpp
  int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
  ```

  ​	`select`函数监视的文件描述符分3类，分别是`writefds`、`readfds`、和`exceptfds`。调用后`select`函数会阻塞，直到有描述副就绪（有数据 可读、可写、或者有`except`），或者超时（`timeout`指定等待时间，如果立即返回设为`null`即可），函数返回。当`select`函数返回后，可以 通过遍历`fd_set`，来找到就绪的描述符。

- ***特点***

  ​	`select`目前几乎在所有的平台上支持，其良好跨平台支持也是它的一个优点。select的一 个缺点在于单个进程能够监视的文件描述符的数量存在最大限制，在`Linux`上一般为1024，可以通过修改宏定义甚至重新编译内核的方式提升这一限制，但 是这样也会造成效率的降低。

- ***不足***
  - 每次调用`select`，都需要把`fd`集合从用户态拷贝到内核态，这个开销在fd很多时会很大
  - 同时每次调用`select`都需要在内核遍历传递进来的所有`fd`，这个开销在fd很多时也很大
  - `select`支持的文件描述符数量太小了，默认是1024

#### 3.2 poll

- ***代码***

  ```cpp
  int poll (struct pollfd *fds, unsigned int nfds, int timeout);
  ```

  ```cpp
  struct pollfd {
      int fd; /* file descriptor */
      short events; /* requested events to watch */
      short revents; /* returned events witnessed */
  };
  ```

  ​	不同于`select`使用三个`fd_set`，`poll`使用一个`pollfd`的指针实现。而`pollfd`结构包含了要监视的`event`和发生的`event`，不再使用`select`“参数-值”传递的方式。同时，pollfd并没有最大数量限制。

- ***特点***

  ​	`poll`和`select`类似，但是没有最大链接数的限制，因为是基于==链表存储==的。

- ***不足***

  - `poll`没有本质上改变`select`的方法，只是没有`fd_maxsize`的限制。`select`和`epoll`的不足之处还是类似的

#### 3.3 epoll

- ***代码***

  ```c++
  int epoll_create(int size)；//创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大
  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)；
  int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
  ```

  ```cpp
  struct epoll_event {
    __uint32_t events;  /* Epoll events */
    epoll_data_t data;  /* User data variable */
  };
  
  /*
  	events可以是以下几个宏的集合：
  	EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
  	EPOLLOUT：表示对应的文件描述符可以写；
  	EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
  	EPOLLERR：表示对应的文件描述符发生错误；
  	EPOLLHUP：表示对应的文件描述符被挂断；
  	EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
  	EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
  */
  ```

- ***特点***

  ​	`epoll`较`select/poll`，主要改进两个缺点。一个是性能开销，一个是文件描述符少。

  - 性能优化
    - `epoll`从`select/poll`中的主动轮询变为变动通知，当有事件发生的时候，被动接收通知。所以`epoll`模型注册套接字后，主程序可以继续执行。
    - `epoll`通过内核和用户空间共享一块内存来实现。
  - 监视的描述符不受限制
    - 采用红黑树存储文件描述符集合

- ***不足***
  - 代码比较复杂
  - 如果没有大量的idle -connection或者dead-connection，epoll的效率并不会比select/poll高很多，但是当遇到大量的idle- connection，就会发现epoll的效率大大高于select/poll。

#### 3.4 总结

![image-20220219001249601](https://s2.loli.net/2022/02/19/ApTbgqxUoIzhOPv.png)

> 图片来自[这里](https://juejin.cn/post/6931543528971436046)

### 参考

[一文搞懂select、poll和epoll区别](https://zhuanlan.zhihu.com/p/272891398)

[Linux IO模式及 select、poll、epoll详解](https://segmentfault.com/a/1190000003063859)

[select/poll/epoll的区别](https://www.cnblogs.com/aspirant/p/9166944.html)

### 
# IO多路复用

* `select`什么时候返回0？
  * `select`成功时返回就绪fd的总数；如果在超时时间内没有任何fd就绪，返回0；失败返回-1，并设置errno；如果在`select`等待期间，程序接收到信号，则返回-1，并设置errno为EINTR

## select，poll和epoll的区别及应用场景

* 对于select和poll来说，所有文件描述符都是在用户态被加入其文件描述符集合的，每次调用都需要将整个集合拷贝到内核态；epoll则将整个文件描述符集合维护在内核态，**每次添加文件描述符的时候都需要执行一个系统调用**。系统调用的开销是很大的，而且在有**很多短期活跃连接**的情况下，epoll可能会慢于select和poll由于这些大量的系统调用开销
* `select`使用线性表描述文件描述符集合，文件描述符有上限；`poll`使用链表来描述；`epoll`底层通过红黑树来描述，并且维护一个ready list，将事件表中已经就绪的事件添加到这里，在使用`epoll_wait`调用时，仅观察这个list中有没有数据即可。
* `select`和`poll`的**最大开销来自内核判断是否有文件描述符就绪这一过程：每次执行select或poll调用时，它们会采用遍历的方式，遍历整个文件描述符集合去判断各个文件描述符是否有活动**；epoll则不需要去以这种方式检查，当有活动产生时，会自动触发epoll回调函数通知epoll文件描述符，然后内核将这些就绪的文件描述符放到之前提到的ready list中等待`epoll_wait`调用后被处理
* `select`和`poll`都只能工作在相对低效的LT模式下，而`epoll`同时支持LT和ET模式
* **综上，当监测的fd数量较小，且各个fd都很活跃的情况下，建议使用`select`和`poll`；当监听的fd数量较多，且单位时间仅部分fd活跃的情况下，使用epoll会明显提升性能。要求实时性的场景也可以使用`select`，因为`select`的`timeout`参数精度是微妙级，而其他两个是毫秒**
* **需要监控的描述符状态变化多，而且都是非常短暂的，也没有必要使用 `epoll`**。因为 `epoll` 中的所有描述符都存储在内核中，造成每次需要对描述符的状态改变都需要通过 `epoll_ctl`进行系统调用，**频繁系统调用降低效率**。并且 `epoll` 的描述符存储在内核，不容易调试

## LT（电平触发）和ET（边缘触发）的差别

* LT（电平触发）：类似`select`，LT会去遍历在epoll事件表中每个文件描述符，来观察是否有我们感兴趣的事件发生，如果有（触发了该文件描述符上的回调函数），`epoll_wait`就会以非阻塞的方式返回。**若该epoll事件没有被处理完**（没有返回`EWOULDBLOCK`），该事件还会被后续的`epoll_wait`再次触发
* ET（边缘触发）：ET在发现有我们感兴趣的事件发生后，立即返回，并且`sleep`这一事件的`epoll_wait`，不管该事件有没有结束
* **在使用ET模式时，必须要保证该文件描述符是非阻塞的**（确保在没有数据可读时，该文件描述符不会一直阻塞，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死）；**并且每次调用`read`和`write`的时候都必须等到它们返回`EWOULDBLOCK`**（**确保所有数据都已读完或写完，因为若没有新事件到来，将不再通知**）

## epoll读写事件触发的条件

* LT模式，EPOLLIN触发条件
  * 处于可读状态：1. socket内核接收缓冲区中字节数大于或等于其低水位标记SO_RCVLOWAT；2. 监听socket上有新的连接请求；3. 通信对方关闭连接，读操作返回0；4. socket异常/错误未处理
  * 从不可读状态变为可读状态
* LT模式，EPOLLOUT触发条件
  * 处于可写状态：1. socket内核发送缓冲区中字节数大于等于其低水位标记SO_SNDLOWAT；2. socket写操作被关闭，写操作触发SIGPIPE；3. socket上有未处理错误；4. socket使用非阻塞connect连接成功或失败之后
  * 从不可写状态变为可写状态
* ET模式，EPOLLIN触发条件
  * 从不可读状态变为可读状态
  * 内核接收到新发来的数据
* ET模式，EPOLLOUT触发条件
  * 从不可写状态变为可写状态
  * 只要同时注册了EPOLLIN和EPOLLOUT事件，当对端发数据来的时候，如果此时是可写状态，epoll会同时触发EPOLLIN和EPOLLOUT事件
  * 接受连接后，只要注册了EPOLLOUT事件，那么就会马上触发EPOLLOUT事件

## epoll重要事件类型说明

* **EPOLLPRI：带外数据**

* **EPOLLRDHUP**
  * 发生场景
    * 对端发送 FIN (对端调用close 或者 shutdown(SHUT_WR))
    * 本端调用 shutdown(SHUT_RD)。 当然，关闭 SHUT_RD 的场景很少
  * 可以作为一种**读关闭**的标志，注意**不能读的意思内核不能再往内核缓冲区中增加新的内容。已经在内核缓冲区中的内容，用户态依然能够读取到**
  
* **EPOLLHUP** 

  * 发生场景

    * 本端调用shutdown(SHUT_RDWR)。 不能是close，**close 之后，文件描述符已经失效**

    * 本端调用 shutdown(SHUT_WR)，对端调用 shutdown(SHUT_WR)

    * 对端发送 RST。发送 RST 的常见场景：

      1. 系统崩溃重启(进程崩溃，只要内核是正常工作都还能兜底，发送的是FIN，不是这里讨论的RST)，四元组消失。此时收到任何数据，都会响应 RST
      2. 设置 linger 参数，l_onoff 为 1 开启，但是 l_linger = 0 超时参数为0。此时close() 将直接发送 RST
      3. 接收缓冲区中还有数据，直接 close()， 接收缓冲区中的内容丢弃，直接发送 RST
      4. 已经调用 close ，close 会立马发送一个 FIN。注意：仅仅从 FIN 数据包上，无法断定对端是 close 还是仅仅 shutdown(SHUT_WR) 半关闭。**此时如果往对端发送数据，若对端已经 close()，对端会回复 RST**
* **表示读写都关闭**

## LT、ET深入

* 使用Linux epoll模型的LT水平触发模式，当socket可写时，会不停的触发socket可写的事件，如何处理？
  * 普通做法：

    当需要向socket写数据时，将该socket加入到epoll等待可写事件。接收到socket可写事件后，调用write()或send()发送数据，当数据全部写完后， 将socket描述符移出epoll列表，这种做法需要反复添加和删除。

  * 改进做法:

    向socket写数据时直接调用send()发送，当send()返回错误码EAGAIN，才将socket加入到epoll，等待可写事件后再发送数据，全部数据发送完毕，再移出epoll模型，改进的做法相当于认为socket在大部分时候是可写的，不能写了再让epoll帮忙监控。

* 上面两种做法是对LT模式下write事件频繁通知的修复，本质上ET模式就可以直接搞定，并不需要用户层程序的补丁操作

* ET模式的线程饥饿问题如果某个socket源源不断地收到非常多的数据，在试图读取完所有数据的过程中，有可能会造成其他的socket得不到处理，从而造成饥饿问题

* socket饥饿解决办法：为每个**已经准备好的描述符维护一个队列**，这样程序就可以知道哪些描述符已经准备好了但是并没有被读取完，然后程序**定时或定量的读取，如果读完则移除，直到队列为空**，这样就保证了每个fd都被读到并且不会丢失数据



### 1. i/o模型

### 2. 

## [I/O模型](https://github.com/CyC2018/CS-Notes/blob/master/notes/Socket.md)

* Unix 有五种 I/O 模型：

  - 阻塞式 I/O
  - 非阻塞式 I/O
  - I/O 复用（select 和 poll）
  - 信号驱动式 I/O（SIGIO）
  - 异步 I/O（AIO）

* 五大 I/O 模型比较

  - 同步 I/O：将数据从内核缓冲区复制到应用进程缓冲区的阶段（第二阶段），应用进程会阻塞
  - 异步 I/O：第二阶段应用进程不会阻塞

  同步 I/O 包括阻塞式 I/O、非阻塞式 I/O、I/O 复用和信号驱动 I/O ，它们的主要区别在第一个阶段。非阻塞式 I/O 、信号驱动 I/O 和异步 I/O 在第一阶段不会阻塞


## 线程池

* 线程池，开多大，为什么运用线程池？

  * 多线程应用并非线程越多越好。需要根据系统运行的硬件环境以及应用本身的特点决定线程池的大小。一般来说，如果代码结构合理，线程数与cpu数量相适合即可。如果线程运行时可能出现阻塞现象，可相应增加池的大小、如果有必要可采用自适应算法来动态调整线程池的大小，以提高cpu的有效利用率和系统的整体性能
    * 线程池大小简单估算公式，设N为CPU个数
      - 对于CPU密集型的应用，线程池的大小设置为N+1
      - 对于I/O密集型的应用，线程池的大小设置为2N+1
    * 最佳线程数量 = （（线程等待时间 + 线程CPU时间）／ 线程CPU时间 ）* CPU个数
  * CPU密集型任务
    * 尽量使用较小的线程池，一般为CPU核心数+1。 因为CPU密集型任务使得CPU使用率很高，若开过多的线程数，会造成**CPU过度切换**
  * IO密集型任务
    * 可以使用稍大的线程池，一般为2*CPU核心数。 IO密集型任务CPU使用率并不高，因此可以**让CPU在等待IO的时候有其他线程去处理别的任务**，充分利用CPU时间
  * 混合型任务
    * 可以将任务分成IO密集型和CPU密集型任务，然后分别用不同的线程池去处理。 只要分完之后两个任务的执行时间相差不大，那么就会比串行执行来的高效
    * 因为如果划分之后两个任务执行时间有数据级的差距，那么拆分没有意义
    * 因为先执行完的任务就要等后执行完的任务，最终的时间仍然取决于后执行完的任务，而且还要加上任务拆分与合并的开销，得不偿失
  * 使用线程池目的：**提高服务器性能，以空间换时间。减少在创建和销毁线程上所花的时间以及申请系统资源的开销，分配系统资源的系统调用是很耗时的。程序运行时预先创建一个线程的集合，当用户请求到来时，可以直接从线程池取得一个执行实体，而无需动态调用pthread_create等函数来创建线程。执行实体用完后可以放回线程池，以供循环使用**

* **C++11简单线程池实现代码**

  ```c++
  #include <queue>
  #include <thread>
  #include <mutex>
  #include <condition_variable>
  #include <functional>
  #include <memory>
  #include <cstddef>
  #inclued <stdexcept>
  
  class ThreadPool {
  public:
      ThreadPool(size_t threadNum = 8): mPool(std::make_share<Pool>()){
          assert(threadNum>0);
          try{
              for(size_t i = 0; i < threadNum; i++) {
                  std::thread(
                      [pool=mPool]{
                          std::unique_lock<std::mutex> locker(pool->mtx);
                          locker.unlock();
                          while(!pool->close) {
                              locker.lock();   // 获得锁才能往下执行
                              if(!pool->tasks.empty()){
                                  auto task = pool->tasks.top(); 	// 从任务队列取任务执行
                                  pool->tasks.pop();		
                                  locker.unlock();	// 取完解锁，让池接收新任务，或者让其他线程处理其他任务
                                  task();			// 执行任务
                              }
                              else {
                              	pool->cond.wait(locker);  // 无任务，等待，通过竞争锁被唤醒   
                              }
                          }1
                      }
                  ).detach();   
          	}
          }
          catch(...){
                  {
                      std::lock_guard<std::mutex> locker(mPool->mtx);  
                      mPool->close = true;         // closed = true，关闭所有线程
                  }
                  mPool->cond.notify_all();    // 唤醒所有线程，执行关闭
                  throw std::runtime_error("ThreadPool Init Failed!");
          }
      }
      
      // 往线程池任务队列添加任务
      template<typename Func>
      void addTask(Func && task){
          {
              std::lock_guard<std::mutex> lg(mPool->mtx);
              mPool->tasks.emplace(std::forward<Func>(task));  // forward完美转发右值引用
          }
          mPool->cond.notify_one();
      }
      
      ~ThreadPool(){
          if(mPool != nullptr){
              {
                  std::lock_guard<std::mutex> lg(mPool->mtx);
          		mPool->close = true;
              }
              mPool->cond.notify_all();
          }
          
      }
      
      ThreadPool(const ThreadPool&) = delete;
      ThreadPool& operator = (const ThreadPool&) = delete;
  private:
    struct Pool{
  		std::queue<std::function(void())> tasks;  // 任务队列
          std::mutex mtx;
      	std::condition_variable cond;
          bool close = false;
      };
      std::share_ptr<Pool> mPool;
  };
  ```


#### (1) 建立TCP服务器的各个系统调用
建立TCP服务器连接的过程中主要通过以下系统调用序列来获取某些函数,这些系统调用主要包括:socket(),bind(),listen(),accept(),send()和recv().
详见:[建立TCP 服务器的系统调用](https://blog.csdn.net/qq_37964547/article/details/81429627)

#### (2) 继上一题,说明socket网络编程有哪些系统调用?其中close是一次就能直接关闭的吗,半关闭状态是怎么产生的?

    socket()    创建套接字   
    bind()      绑定本机端口    
    connect()   建立连接     (TCP三次握手在调用这个函数时进行)
    listen()    监听端口
    accept()    接受连接
    recv(), read(), recvfrom()  数据接收
    send(), write(), sendto()   数据发送
    close(), shutdown() 关闭套接字

使用close()时,只有当套接字的引用计数为0的时候才会终止连接,而用shutdown()就可以直接关闭连接

详见:[网络编程Socket之TCP之close/shutdown详解](https://blog.csdn.net/junjun150013652/article/details/37994907)

TCP连接与断开详解: https://www.cnblogs.com/felixzh/p/8359066.html

### 附录
#### 1. socket的c++ api
Socket API是一组函数，用于创建和管理网络通信。以下是一些常用的Socket API的使用方法：

```cpp
#include <sys/socket.h>
// 1. **创建Socket**：使用`socket()`函数创建一个新的Socket。
int sockfd = socket(AF_INET, SOCK_STREAM, 0);

// 2. **绑定Socket到地址**：使用`bind()`函数将Socket绑定到一个特定的地址和端口。
#include <netinet/in.h>
//...
struct sockaddr_in servaddr;
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(8080);
bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

// 3. **监听连接**：使用`listen()`函数让Socket开始监听连接请求。
listen(sockfd, 5);

// 4. **接受连接**：使用`accept()`函数接受一个连接请求。
struct sockaddr_in cliaddr;
socklen_t len = sizeof(cliaddr);
int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);

// 5. **发送数据**：使用`send()`函数发送数据。
const char* message = "Hello, World!";
send(connfd, message, strlen(message), 0);

// 6. **接收数据**：使用`recv()`函数接收数据。
char buffer[1024];
recv(connfd, buffer, sizeof(buffer), 0);

// 7. **关闭Socket**：使用`close()`函数关闭Socket。
close(sockfd);
```


#### (1) Linux的I/O模型介绍以及同步异步阻塞非阻塞的区别(超级重要)
https://blog.csdn.net/sqsltr/article/details/92762279

https://www.cnblogs.com/euphie/p/6376508.html


(IO过程包括两个阶段:(1)内核从IO设备读写数据和(2)进程从内核复制数据)

* 阻塞:调用IO操作的时候,如果缓冲区空或者满了,调用的进程或者线程就会处于阻塞状态直到IO可用并完成数据拷贝.
* 非阻塞:调用IO操作的时候,内核会马上返回结果,如果IO不可用,会返回错误,这种方式下进程需要不断轮询直到IO可用为止,但是当进程从内核拷贝数据时是阻塞的.
* IO多路复用就是同时监听多个描述符,一旦某个描述符IO就绪(读就绪或者写就绪),就能够通知进程进行相应的IO操作,否则就将进程阻塞在select或者epoll语句上.


* 同步IO:同步IO模型包括阻塞IO,非阻塞IO和IO多路复用.特点就是当进程从内核复制数据的时候都是阻塞的.
* 异步IO:在检测IO是否可用和进程拷贝数据的两个阶段都是不阻塞的,进程可以做其他事情,当IO完成后内核会给进程发送一个信号.


#### (3) EPOLL的介绍和了解
https://zhuanlan.zhihu.com/p/56486633 

https://www.jianshu.com/p/397449cadc9a

https://blog.csdn.net/davidsguo008/article/details/73556811


Epoll是Linux进行IO多路复用的一种方式,用于在一个线程里监听多个IO源,在IO源可用的时候返回并进行操作.它的特点是基于事件驱动,性能很高.

epoll将文件描述符拷贝到内核空间后使用红黑树进行维护,同时向内核注册每个文件描述符的回调函数,当某个文件描述符可读可写的时候,将这个文件描述符加入到就绪链表里,并唤起进程,返回就绪链表到用户空间,由用户程序进行处理.

Epoll有三个系统调用:epoll_create(),epoll_ctl()和epoll_wait().

* eoll_create()函数在内核中初始化一个eventpoll对象,同时初始化红黑树和就绪链表.

* epoll_ctl()用来对监听的文件描述符进行管理.将文件描述符插入红黑树,或者从红黑树中删除,这个过程的时间复杂度是log(N).同时向内核注册文件描述符的回调函数.

* epoll_wait()会将进程放到eventpoll的等待队列中,将进程阻塞,当某个文件描述符IO可用时,内核通过回调函数将该文件描述符放到就绪链表里,epoll_wait()会将就绪链表里的文件描述符返回到用户空间.
#### (4) IO复用的三种方法(select,poll,epoll)深入理解,包括三者区别,内部原理实现?
(1)select的方法介绍:select把所有监听的文件描述符拷贝到内核中,挂起进程.当某个文件描述符可读或可写的时候,中断程序唤起进程,select将监听的文件描述符再次拷贝到用户空间,然select后遍历这些文件描述符找到IO可用的文件.下次监控的时候需要再次拷贝这些文件描述符到内核空间.select支持监听的描述符最大数量是1024.
![select](fig/select.png)
(2)poll使用链表保存文件描述符,其他的跟select没有什么不同.

(3)epoll将文件描述符拷贝到内核空间后使用红黑树进行维护,同时向内核注册每个文件描述符的回调函数,当某个文件描述符可读可写的时候,将这个文件描述符加入到就绪链表里,并唤起进程,返回就绪链表到用户空间.
![epoll](fig/epoll.png)
详见 https://www.cnblogs.com/Anker/p/3265058.html
#### (5) Epoll的ET模式和LT模式(ET的非阻塞)
* ET是边缘触发模式,在这种模式下,只有当描述符从未就绪变成就绪时,内核才会通过epoll进行通知.然后直到下一次变成就绪之前,不会再次重复通知.也就是说,如果一次就绪通知之后不对这个描述符进行IO操作导致它变成未就绪,内核也不会再次发送就绪通知.优点就是只通知一次,减少内核资源浪费,效率高.缺点就是不能保证数据的完整,有些数据来不及读可能就会无法取出.
* LT是水平触发模式,在这个模式下,如果文件描述符IO就绪,内核就会进行通知,如果不对它进行IO操作,只要还有未操作的数据,内核都会一直进行通知.优点就是可以确保数据可以完整输出.缺点就是由于内核会一直通知,会不停从内核空间切换到用户空间,资源浪费严重.
#### (6) 查询进程占用CPU的命令(注意要了解到used,buf,代表意义)
详见:https://blog.csdn.net/qq_36357820/article/details/76606113
1. top命令查看linux负载:
2. uptime查看linux负载
3. w查看linux负载:
4. vmstat查看linux负载


#### poll和epoll的区别
epoll是poll的升级版.其实poll和epoll都是用于同时监视多个文件描述符的.poll需要自己管理一组文件描述符的集合,而epoll就使得内核为我们管理这个结构体的数组,通过epoll_create.epoll不是一个函数,他是一组函数的实现.<br>
* poll布置完监视任务就需要取得监视的结果,而epoll就是用epoll_wait函数进行阻塞监视并返回监视结果.
epoll更成熟.<br>
* nginx和apache对比

* 同步/异步/阻塞/非阻塞的理解
* * 同步互斥
* 1/linux IO模型(5种) 记不太清,说了几种,应该没说完.(应该是:同步阻塞/同步非阻塞/多路复用/信号驱动/异步IO)应该还要说细节

* 什么是缓冲区溢出

23/epoll和select的区别?
答:select能支持的文件描述符数是有限的,最大1024个,并且每次调用前都需要将其监听的读集/写集/错误集从用户态向内核态拷贝,返回后又拷贝回去,而且,select返回的时候是将所有的文件描述符返回,也就意味着一旦有个事件触发,只能通过遍历的方式才能找到具体是哪一个事件,效率比较低/开销也比较大,但是也有好处,就是他的超时的单位是微秒级别;
epoll能支持的文件描述符数很大,可以上万,他的高效由3个部分组成:红黑树/双向链表/回调函数,每次将监听事件拷贝到内核后就存放在红黑树种,以EventPoll的结构体存在,如果有相应的事件发生,对应的回调函数就会触发,进而就会将该事件拷贝至双向链表中返回,而且,epoll每次返回的都是有事件发生的事件,不是所有时间,所以比较高效,总的来说epoll适用于连接数较多,活跃数较少的场景/而select适用于连接数不多,但大多都活跃的场景.

24/同一个IP同一个端口可以同时建立tcp和udp的连接吗
答可以,同一个端口虽然udp和tcp的端口数字是一样的,但实质他们是不同的端口,所以是没有影响的,从底层实质分析,对于每一个连接内核维护了一个五元组,包含了源ip,目的ip/源端口目的端口/以及传输协议,在这里尽管前4项都一样,但是传输协议是不一样的,所以内核会认为是2个不同的连接,在ip层就会进行开始分流,tcp的走tcp,udp走udp.
