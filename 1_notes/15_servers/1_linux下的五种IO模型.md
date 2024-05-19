## linux下的五种IO模型

[toc]

### 1. 基本概念

- ***什么是IO？***

  ​	IO最本质来说，指的就是文件的输入和输出。而这里的文件不是指`word`文件、`txt`文件。请接着往下看。

- ***什么是文件***

  ​	linux一个突出的设计理念在于，将一切外部设备看成一个文件来操作。任何东西都挂在文件系统之上，即使它们不是文件，也以文件的形式来呈现。这些一切外部设部都享有与内部文件一样的接口。

  ​	总结一下就是，linux这种设计理念是一种类似于面向对象的设计思想，而上文的文件包括但不限于`串口`，`内存`，`usb`，`进程信息`，`网卡`，`网络通讯socket`等等一切外部设备。把他们都当做文件，又便于我们统一写代码。

- ***为什么要区分这么多IO模型呢？或者说IO模型难点在哪里？***

  ​	首先因为IO读写是非直接的，因为程序无法直接访问硬件资源，具体原因可以看[这里](https://marco-hmc.github.io/2022/02/15/linux%E4%B8%8B%E7%94%A8%E6%88%B7%E6%80%81%E5%92%8C%E7%B3%BB%E7%BB%9F%E6%80%81%E7%9A%84%E5%9F%BA%E7%A1%80%E8%AE%A4%E8%AF%86/)，数据是先从内核空间得到，然后复制到我们操作的用户空间的。

  ​	其次因为IO读写速度慢，因为从硬盘大批量读写数据是可以明显感知得很慢的，把一个文件从C盘拖到到D盘就可以感受出来了;除此之外，还有网络IO等，这个IO读写速度就更慢了。因此在程序设计中，我们需要根据场景判断这个IO完成读写没有，或者说提交读写请求后，就去处理其他事情，等他完成了再回来。专业一点就是常说的阻塞和非阻塞等。

- ***一次IO的读写过程示例***

  ![~replace~/assets/images/io-model/ioflow.png](https://s2.loli.net/2022/02/18/rDRSXe5QnTOCUxd.png)

  ```c++
  // pseudo-code
  fileStream in = new fileStream("toBeRead.txt");
  fileStream out = new fileStream("toBeWrtie.txt");
      
  data = in.read();
  out.write(data);
  ```

  

### 2. IO五大模型

​	综上讨论，我们对IO是什么，做什么有了粗略的认识，我们现在就可以针对具体的五大模型展开讨论。

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
