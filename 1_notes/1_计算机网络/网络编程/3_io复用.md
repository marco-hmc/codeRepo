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

IO过程包括两个阶段:(1)内核从IO设备读写数据和(2)进程从内核复制数据

#### 1.3 linux下如何实现io复用？

在Linux系统中，实现IO复用主要有以下几种方式：

select：select是最早的IO复用解决方案，它可以同时监控多个文件描述符（例如socket）。当其中任何一个文件描述符准备好读、写或异常时，select就会返回。select的主要缺点是它支持的文件描述符数量有限（通常最多1024个），并且效率随着文件描述符数量的增加而降低。

poll：poll和select类似，但它没有最大文件描述符数量的限制。然而，poll的效率仍然随着文件描述符数量的增加而降低。

epoll：epoll是Linux特有的IO复用解决方案，它没有最大文件描述符数量的限制，而且效率不会随着文件描述符数量的增加而降低。epoll使用一种称为事件驱动的方式，只关注活跃的文件描述符，因此比select和poll更高效。


### 2. io复用技术

`select`、`poll`和`epoll`是Linux系统中用于IO多路复用的三种机制。它们允许程序监视多个文件描述符（FD），以便知道哪个或哪些文件描述符可以进行非阻塞IO操作。以下是它们的主要区别：
#### 2.1 select

- **工作方式**：`select`允许应用程序监视一组文件描述符，以了解是否有数据可读、可写或是否有异常条件待处理。
- **限制**：`select`有一个固定的大小限制（通常由FD_SETSIZE宏定义，标准值为1024），这意味着它一次只能监视1024个文件描述符。
- **性能**：当文件描述符集合较小时，性能尚可。但随着监视的文件描述符数量增加，其性能会线性下降，因为`select`需要在用户空间和内核空间之间复制整个文件描述符集。

#### 2.2 poll
- **工作方式**：`poll`与`select`类似，也是监视一组文件描述符的状态变化。但它没有`select`的数量限制，因为它使用动态分配的结构体数组而不是固定大小的位图。
- **限制**：尽管`poll`没有文件描述符数量的硬性限制，但随着监视的文件描述符数量增加，其性能也会受到影响，因为它需要遍历整个文件描述符列表来检查状态。
- **性能**：`poll`的性能优于`select`，尤其是在处理大量文件描述符时。

#### 2.3 epoll
- **工作方式**：`epoll`是Linux特有的，相比于`select`和`poll`，`epoll`提供了更高的性能和更大的可扩展性。它使用一种事件通知机制，只返回活跃的文件描述符，避免了遍历整个文件描述符集。
- **限制**：`epoll`的接口和行为与`select`和`poll`有所不同，需要更改代码来使用。它在早期的Linux内核版本中不可用。
- **性能**：`epoll`的性能不会随着监视的文件描述符数量增加而显著下降。它特别适用于高并发、大量连接的场景。
 

### 3. select/poll/epoll

​	IO复用模型中又可进一步分为select、poll和epoll方法。前面出于排版的原因，反正这下面来进一步讲解

#### 3.1 select

- ***代码***

  ```cpp
  int select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
  ```

  ​	`select`函数监视的文件描述符分3类，分别是`writefds`、`readfds`、和`exceptfds`。调用后`select`函数会阻塞，直到有描述副就绪（有数据 可读、可写、或者有`except`），或者超时（`timeout`指定等待时间，如果立即返回设为`null`即可），函数返回。当`select`函数返回后，可以 通过遍历`fd_set`，来找到就绪的描述符。

- ***特点***

  ​	`select`目前几乎在所有的平台上支持，其良好跨平台支持也是它的一个优点。select的一个缺点在于单个进程能够监视的文件描述符的数量存在最大限制，在`Linux`上一般为1024，可以通过修改宏定义甚至重新编译内核的方式提升这一限制，但 是这样也会造成效率的降低。

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

  ​	`poll`和`select`类似，但是没有最大链接数的限制，fds是一个指向struct pollfd类型数组的首地址。这个数组的大小是由调用者决定的，不受静态限制。

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

* LT模式，EPOLLIN触发条件
  * 处于可读状态：
    * 1. socket内核接收缓冲区中字节数大于或等于其低水位标记SO_RCVLOWAT；
    * 2. 监听socket上有新的连接请求；
    * 3. 通信对方关闭连接，读操作返回0；
    * 4. socket异常/错误未处理
  * 从不可读状态变为可读状态
* LT模式，EPOLLOUT触发条件
  * 处于可写状态：
    * 1. socket内核发送缓冲区中字节数大于等于其低水位标记SO_SNDLOWAT；
    * 2. socket写操作被关闭，写操作触发SIGPIPE；
    * 3. socket上有未处理错误；
    * 4. socket使用非阻塞connect连接成功或失败之后
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

![alt text](_imgs/3_io复用_image.png)


### 99. quiz

#### 1. select，poll和epoll的区别及应用场景

* 对于select和poll来说，所有文件描述符都是在用户态被加入其文件描述符集合的，每次调用都需要将整个集合拷贝到内核态；epoll则将整个文件描述符集合维护在内核态，**每次添加文件描述符的时候都需要执行一个系统调用**。系统调用的开销是很大的，而且在有**很多短期活跃连接**的情况下，epoll可能会慢于select和poll由于这些大量的系统调用开销
* `select`和`poll`都只能工作在相对低效的LT模式下，而`epoll`同时支持LT和ET模式
* **综上，当监测的fd数量较小，且各个fd都很活跃的情况下，建议使用`select`和`poll`；当监听的fd数量较多，且单位时间仅部分fd活跃的情况下，使用epoll会明显提升性能。要求实时性的场景也可以使用`select`，因为`select`的`timeout`参数精度是微妙级，而其他两个是毫秒**
* **需要监控的描述符状态变化多，而且都是非常短暂的，也没有必要使用 `epoll`**。因为 `epoll` 中的所有描述符都存储在内核中，造成每次需要对描述符的状态改变都需要通过 `epoll_ctl`进行系统调用，**频繁系统调用降低效率**。并且 `epoll` 的描述符存储在内核，不容易调试

#### 2. LT（电平触发）和ET（边缘触发）的差别

* LT（电平触发）：类似`select`，LT会去遍历在epoll事件表中每个文件描述符，来观察是否有我们感兴趣的事件发生，如果有（触发了该文件描述符上的回调函数），`epoll_wait`就会以非阻塞的方式返回。**若该epoll事件没有被处理完**（没有返回`EWOULDBLOCK`），该事件还会被后续的`epoll_wait`再次触发
* ET（边缘触发）：ET在发现有我们感兴趣的事件发生后，立即返回，并且`sleep`这一事件的`epoll_wait`，不管该事件有没有结束
* **在使用ET模式时，必须要保证该文件描述符是非阻塞的**（确保在没有数据可读时，该文件描述符不会一直阻塞，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死）；**并且每次调用`read`和`write`的时候都必须等到它们返回`EWOULDBLOCK`**（**确保所有数据都已读完或写完，因为若没有新事件到来，将不再通知**）


#### 3. 说明socket网络编程有哪些系统调用?其中close是一次就能直接关闭的吗,半关闭状态是怎么产生的?
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

#### 4. 同一个IP同一个端口可以同时建立tcp和udp的连接吗
可以,同一个端口虽然udp和tcp的端口数字是一样的,但实质他们是不同的端口,所以是没有影响的,从底层实质分析,对于每一个连接内核维护了一个五元组,包含了源ip,目的ip/源端口目的端口/以及传输协议,在这里尽管前4项都一样,但是传输协议是不一样的,所以内核会认为是2个不同的连接,在ip层就会进行开始分流,tcp的走tcp,udp走udp.

#### 5. 什么是缓冲区溢出

### 附录

#### (1) Linux的I/O模型介绍以及同步异步阻塞非阻塞的区别(超级重要)
https://blog.csdn.net/sqsltr/article/details/92762279

https://www.cnblogs.com/euphie/p/6376508.html

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
(3)epoll将文件描述符拷贝到内核空间后使用红黑树进行维护,同时向内核注册每个文件描述符的回调函数,当某个文件描述符可读可写的时候,将这个文件描述符加入到就绪链表里,并唤起进程,返回就绪链表到用户空间.
![epoll](fig/epoll.png)
详见 https://www.cnblogs.com/Anker/p/3265058.html

#### (5) Epoll的ET模式和LT模式(ET的非阻塞)
* ET是边缘触发模式,在这种模式下,只有当描述符从未就绪变成就绪时,内核才会通过epoll进行通知.然后直到下一次变成就绪之前,不会再次重复通知.也就是说,如果一次就绪通知之后不对这个描述符进行IO操作导致它变成未就绪,内核也不会再次发送就绪通知.优点就是只通知一次,减少内核资源浪费,效率高.缺点就是不能保证数据的完整,有些数据来不及读可能就会无法取出.
* LT是水平触发模式,在这个模式下,如果文件描述符IO就绪,内核就会进行通知,如果不对它进行IO操作,只要还有未操作的数据,内核都会一直进行通知.优点就是可以确保数据可以完整输出.缺点就是由于内核会一直通知,会不停从内核空间切换到用户空间,资源浪费严重.


### 参考

[一文搞懂select、poll和epoll区别](https://zhuanlan.zhihu.com/p/272891398)

[Linux IO模式及 select、poll、epoll详解](https://segmentfault.com/a/1190000003063859)

[select/poll/epoll的区别](https://www.cnblogs.com/aspirant/p/9166944.html)
