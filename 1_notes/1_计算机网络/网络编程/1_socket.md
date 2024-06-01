_tags: 计算机网络
_label: 4.3

## Socket

### 1. Socket基础知识
Socket（套接字）是计算机网络中用于实现不同主机之间的通信的一种技术。它提供了一种在网络上发送和接收数据的方式。在TCP/IP网络模型中，Socket是应用层和传输层之间的接口。

Socket的基础知识包括以下几个部分：

1. **Socket类型**：主要有两种类型的Socket，分别是流式Socket（SOCK_STREAM）和数据报Socket（SOCK_DGRAM）。流式Socket基于TCP，提供了一种可靠的、面向连接的通信方式。数据报Socket基于UDP，提供了一种不可靠的、无连接的通信方式。

2. **Socket地址**：每个Socket都有一个相关联的地址，包括IP地址和端口号。IP地址标识了网络上的一个主机，端口号标识了主机上的一个应用程序。

3. **Socket API**：Socket API是一组函数，它们提供了创建Socket、发送和接收数据、关闭Socket等操作。常见的Socket API包括socket()、bind()、listen()、accept()、connect()、send()、receive()等。

4. **Socket的状态**：Socket在其生命周期中会经历多种状态，如CLOSED、LISTEN、SYN_SENT、SYN_RECEIVED、ESTABLISHED等。了解这些状态对于理解网络通信的过程非常重要。

#### 1.1 socket类型有哪些
Socket主要有两种类型：

1. **流式Socket（Stream Sockets）**：也被称为SOCK_STREAM，它基于TCP（Transmission Control Protocol，传输控制协议）。这种类型的Socket提供了一种可靠的、双向的、基于连接的字节流。如果数据在传输过程中丢失或损坏，TCP会自动进行错误检查和恢复。

2. **数据报Socket（Datagram Sockets）**：也被称为SOCK_DGRAM，它基于UDP（User Datagram Protocol，用户数据报协议）。这种类型的Socket提供了一种无连接的、不可靠的消息传递服务。数据报可能会丢失或乱序，但UDP协议本身不提供任何错误检查和恢复机制，因此传输速度通常比TCP快。

这两种Socket类型各有用途，选择哪种类型取决于你的应用程序需要什么样的服务。如果需要可靠的数据传输，通常选择流式Socket；如果需要快速的数据传输，而且不介意数据的丢失或乱序，通常选择数据报Socket。

#### 1.2 socket地址是什么？
Socket地址是用于标识网络上的一个端点的。在Internet协议（IP）网络中，一个Socket地址由一个IP地址和一个端口号组成。

1. **IP地址**：IP地址是网络上的一个主机的唯一标识。它是一个32位（IPv4）或128位（IPv6）的数字，通常以点分十进制或冒号分十六进制的形式表示。

2. **端口号**：端口号是主机上的一个应用程序的唯一标识。它是一个16位的数字，范围从0到65535。其中，0到1023的端口号被保留用于知名的服务，如HTTP（端口80）、FTP（端口21）等。

例如，一个完整的Socket地址可能是`192.168.1.1:8080`，其中`192.168.1.1`是IP地址，`8080`是端口号。这个地址标识了网络上的一个主机（IP地址为`192.168.1.1`）上的一个应用程序（端口号为`8080`）。

#### 1.3 socket的C++ api怎么用？
放在附录

#### 1.4 socket相关的状态位有哪些？

* 客户端调用connect发送SYN包，客户端协议栈收到 ACK 之后，使得应用程序从 connect 调用返回，表示客户端到服务器端的单
  向连接建立成功
  
* `accept`发生在什么阶段
  * 三次握手之后，tcp连接会加入到accept队列。accept()会从队列中取一个连接返回，若队列为空，则阻塞
  
* send/recv(read/write)返回值大于0、等于0、小于0的区别
  * recv
    * 阻塞与非阻塞recv返回值没有区分，都是 <0：出错，=0：连接关闭，>0接收到数据大小
    * 特别：非阻塞模式下返回 值 <0时并且(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况 下认为连接是正常的，继续接收。
    * 只是阻塞模式下recv会阻塞着接收数据，非阻塞模式下如果没有数据会返回，不会阻塞着读，因此需要 循环读取
  * write：
    * 阻塞与非阻塞write返回值没有区分，都是 <0出错，=0连接关闭，>0发送数据大小
    * 特别：非阻塞模式下返回值 <0时并且 (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况下认为连接是正常的， 继续发送
    * 只是阻塞模式下write会阻塞着发送数据，非阻塞模式下如果暂时无法发送数据会返回，不会阻塞着 write，因此需要循环发送。
  * read：
    * 阻塞与非阻塞read返回值没有区分，都是 <0：出错，=0：连接关闭，>0接收到数据大小
    * 特别：非阻塞模式下返回 值 <0时并且(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况 下认为连接是正常的，继续接收。
    * 只是阻塞模式下read会阻塞着接收数据，非阻塞模式下如果没有数据会返回，不会阻塞着读，因此需要 循环读取
  * send：
    * 阻塞与非阻塞send返回值没有区分，都是 <0：出错，**=0：连接关闭**，>0发送数据大小。 还没发出去，连接就断开了，有可能返回0
    * 特别：非阻塞模式下返回值 <0时并且 (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况下认为连接是正常的， 继续发送
    * 只是阻塞模式下send会阻塞着发送数据，非阻塞模式下如果暂时无法发送数据会返回，不会阻塞着 send，因此需要循环发送
  
* **Socket的四元组、五元组、七元组**
  * 四元组：源IP地址、目的IP地址、源端口、目的端口
  * 五元组：源IP地址、目的IP地址、**协议号**、源端口、目的端口
  * 七元组：源IP地址、目的IP地址、**协议号**、源端口、目的端口，**服务类型以及接口索引**
  
* 信号SIGPIPE与EPIPE错误码
  * 在linux下写socket的程序的时候，**如果服务器尝试send到一个disconnected socket上，就会让底层抛出一个SIGPIPE信号**。 这个信号的缺省处理方法是退出进程，大多数时候这都不是我们期望的。也就是说，**当服务器繁忙，没有及时处理客户端断开连接的事件，就有可能出现在连接断开之后继续发送数据的情况，如果对方断开而本地继续写入的话，就会造成服务器进程意外退出**
  * 根据信号的默认处理规则SIGPIPE信号的默认执行动作是terminate(终止、退出)，所以client会退出。若不想客户端退出可以把 SIGPIPE设为SIG_IGN 如：signal(SIGPIPE, SIG_IGN); 这时SIGPIPE交给了系统处理。 服务器采用了fork的话，要收集垃圾进程，防止僵尸进程的产生，可以这样处理： signal(SIGCHLD,SIG_IGN); 交给系统init去回收。 这里子进程就不会产生僵尸进程了
  
* **如何检测对端已经关闭socket**
  
  * 根据errno和recv结果进行判断
    * 在UNIX/LINUX下，**非阻塞模式SOCKET可以采用recv+MSG_PEEK的方式进行判断**，其中MSG_PEEK保证了仅仅进行状态判断，而不影响数据接收
    * 对于主动关闭的SOCKET, recv返回-1，而且errno被置为9（#define EBADF  9  // Bad file number ）或104 (#define ECONNRESET 104 // Connection reset by peer)
    * 对于被动关闭的SOCKET，recv返回0，而且errno被置为11（#define EWOULDBLOCK EAGAIN // Operation would block ）**对正常的SOCKET, 如果有接收数据，则返回>0, 否则返回-1，而且errno被置为11**（#define EWOULDBLOCK EAGAIN // Operation would block ）因此对于简单的状态判断(不过多考虑异常情况)：recv返回>0，  正常
  
* udp调用connect有什么作用？
  * 因为UDP可以是一对一，多对一，一对多，或者多对多的通信，所以每次调用sendto()/recvfrom()时都必须指定目标IP和端口号。通过调用connect()建立一个端到端的连接，就可以和TCP一样使用send()/recv()传递数据，而不需要每次都指定目标IP和端口号。但是它和TCP不同的是它没有三次握手的过程
  * 可以通过在已建立连接的UDP套接字上，调用connect()实现指定新的IP地址和端口号以及断开连接
  
* **处理非阻塞connect的步骤**（重点）：

  1. 创建socket，返回套接口描述符；
  2. 调用fcntl 把套接口描述符设置成非阻塞；
  3. 调用connect 开始建立连接；
  4. 判断连接是否成功建立

     1. 如果connect 返回0，表示连接成功（服务器和客户端在同一台机器上时就有可能发生这种情况）
     2. 否则，需要通过io多路复用(select/poll/epoll)来监听该socket的可写事件来判断连接是否建立成功：当select/poll/epoll检测出该socket可写，还需要通过调用getsockopt来得到套接口上待处理的错误（SO_ERROR）。**如果连接建立成功，这个错误值将是0**；**如果建立连接时遇到错误，则这个值是连接错误所对应的errno值**（比如：ECONNREFUSED，ETIMEDOUT等）


* accept返回EMFILE的处理方法

  <img src="imgs/socket/emfile.png" alt="emfile" style="zoom: 50%;" />

* SO_ERROR选项

  ```c
  #include <sys/socket.h>
   
  int getsockopt(int sockfd, int level, int option, void *optval, socklen_t optlen);
  ```

  * 当一个socket发生错误的时候，将使用一个名为SO_ERROR的变量记录对应的错误代码，这又叫做pending error，SO_ERROR为0时表示没有错误发生。一般来说，有2种方式通知进程有socket错误发生：
    1. 进程阻塞在select中，有错误发生时，select将返回，并将发生错误的socket标记为可读写
    2. 如果进程使用信号驱动的I/O，将会有一个SIGIO产生并发往对应进程

  * 此时，进程可以通过SO_ERROR取得具体的错误代码。getsockopt返回后，*optval指向的区域将存储错误代码，而so_error被设置为0

  * 当SO_ERROR不为0时，如果进程对socket进行read操作，若此时接收缓存中没有数据可读，则read返回-1，且errno设置为SO_ERROR，SO_ERROR置为0，否则将返回缓存中的数据而不是返回错误；如果进行write操作，将返回-1，errno置为SO_ERROR，SO_ERROR清0

  注意，这是一个只可以获取，不可以设置的选项。

