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


```cpp
#include <sys/socket.h>
// 1. **创建Socket**：使用`socket()`函数创建一个新的Socket。
int sockFd = socket(AF_INET, SOCK_STREAM, 0);

// 2. **绑定Socket到地址**：使用`bind()`函数将Socket绑定到一个特定的地址和端口。
#include <netinet/in.h>
//...
struct sockaddr_in servAddr;
servAddr.sin_family = AF_INET;
servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
servAddr.sin_port = htons(8080);
bind(sockFd, (struct sockaddr*)&servAddr, sizeof(servAddr));

// 3. **监听连接**：使用`listen()`函数让Socket开始监听连接请求。
listen(sockFd, 5);

// 4. **接受连接**：使用`accept()`函数接受一个连接请求。
struct sockaddr_in cliAddr;
socklen_t len = sizeof(cliAddr);
int connFd = accept(sockFd, (struct sockaddr*)&cliAddr, &len);

// 5. **发送数据**：使用`send()`函数发送数据。
const char* message = "Hello, World!";
send(connFd, message, strlen(message), 0);

// 6. **接收数据**：使用`recv()`函数接收数据。
char buffer[1024];
recv(connFd, buffer, sizeof(buffer), 0);

// 7. **关闭Socket**：使用`close()`函数关闭Socket。
close(sockFd);
```


# socket 的阻塞模式和非阻塞模式

对 socket 在阻塞和非阻塞模式下的各个函数的行为差别深入的理解是掌握网络编程的基本要求之一，是重点也是难点。

阻塞和非阻塞模式下，我们常讨论的具有不同行为表现的 socket 函数一般有如下几个，见下表：

- connect
- accept
- send (Linux 平台上对 socket 进行操作时也包括 **write** 函数，下文中对 send 函数的讨论也适用于 **write** 函数)
- recv (Linux 平台上对 socket 进行操作时也包括 **read** 函数，下文中对 recv 函数的讨论也适用于 **read** 函数)

限于文章篇幅，本文只讨论 send 和recv函数，connect 和 accept 函数我们将在该系列的后面文章中讨论。在正式讨论之前，我们先解释一下阻塞模式和非阻塞模式的概念。所谓**阻塞模式**，**就当某个函数“执行成功的条件”当前不能满足时，该函数会阻塞当前执行线程，程序执行流在超时时间到达或“执行成功的条件”满足后恢复继续执行**。而**非阻塞模式**恰恰相反，即使某个函数的“执行成功的条件”不当前不能满足，该函数也不会阻塞当前执行线程，而是立即返回，继续运行执行程序流。如果读者不太明白这两个定义也没关系，后面我们会以具体的示例来讲解这两种模式的区别。

## 如何将 socket 设置成非阻塞模式

无论是 Windows 还是 Linux 平台，默认创建的 socket 都是阻塞模式的。

在 Linux 平台上，我们可以使用 **fcntl() 函数**或 **ioctl() 函数**给创建的 socket 增加 **O_NONBLOCK** 标志来将 socket 设置成非阻塞模式。示例代码如下：

```
int oldSocketFlag = fcntl(sockfd, F_GETFL, 0);
int newSocketFlag = oldSocketFlag | O_NONBLOCK;
fcntl(sockfd, F_SETFL,  newSocketFlag);
```

**ioctl() 函数** 与 **fcntl()** 函数使用方式基本一致，这里就不再给出示例代码了。

当然，Linux 下的 **socket()** 创建函数也可以直接在创建时将 socket 设置为非阻塞模式，**socket()** 函数的签名如下：

```
int socket(int domain, int type, int protocol);
```

给 **type** 参数增加一个 **SOCK_NONBLOCK** 标志即可，例如：

```
int s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
```

不仅如此，Linux 系统下利用 accept() 函数返回的代表与客户端通信的 socket 也提供了一个扩展函数 **accept4()**，直接将 accept 函数返回的 socket 设置成非阻塞的。

```
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); 
int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);
```

只要将 **accept4()** 函数最后一个参数 **flags** 设置成 **SOCK_NONBLOCK** 即可。也就是说以下代码是等价的：

```
socklen_t addrlen = sizeof(clientaddr);
int clientfd = accept4(listenfd, &clientaddr, &addrlen, SOCK_NONBLOCK);
socklen_t addrlen = sizeof(clientaddr);
int clientfd = accept(listenfd, &clientaddr, &addrlen);
if (clientfd != -1)
{
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    fcntl(clientfd, F_SETFL,  newSocketFlag);
}
```

在 Windows 平台上，可以调用 **ioctlsocket() 函数** 将 socket 设置成非阻塞模式，**ioctlsocket()** 签名如下：

```
int ioctlsocket(SOCKET s, long cmd, u_long *argp);
```

将 **cmd** 参数设置为 **FIONBIO**，***argp\*** *设置为 **0** 即可将 socket 设置成阻塞模式，而将* **argp** 设置成非 **0** 即可设置成非阻塞模式。示例如下：

```
//将 socket 设置成非阻塞模式
u_long argp = 1;
ioctlsocket(s, FIONBIO, &argp);

//将 socket 设置成阻塞模式
u_long argp = 0;
ioctlsocket(s, FIONBIO, &argp);
```

Windows 平台需要注意一个地方，如果对一个 socket 调用了 **WSAAsyncSelect()** 或 **WSAEventSelect()** 函数后，再调用 **ioctlsocket()** 函数将该 socket 设置为非阻塞模式会失败，你必须先调用 **WSAAsyncSelect()** 通过将 **lEvent** 参数为 **0** 或调用 **WSAEventSelect()** 通过设置 **lNetworkEvents** 参数为 **0** 来清除已经设置的 socket 相关标志位，再次调用 **ioctlsocket()** 将该 socket 设置成阻塞模式才会成功。因为调用 **WSAAsyncSelect()** 或**WSAEventSelect()** 函数会自动将 socket 设置成非阻塞模式。MSDN 上原文（https://docs.microsoft.com/en-us/windows/desktop/api/winsock/nf-winsock-ioctlsocket）如下：

```
The WSAAsyncSelect and WSAEventSelect functions automatically set a socket to nonblocking mode. If WSAAsyncSelect or WSAEventSelect has been issued on a socket, then any attempt to use ioctlsocket to set the socket back to blocking mode will fail with WSAEINVAL.

To set the socket back to blocking mode, an application must first disable WSAAsyncSelect by calling WSAAsyncSelect with the lEvent parameter equal to zero, or disable WSAEventSelect by calling WSAEventSelect with the lNetworkEvents parameter equal to zero.
```

关于 **WSAAsyncSelect()** 和 **WSAEventSelect()** 这两个函数，后文中会详细讲解。

> 注意事项：无论是 Linux 的 fcntl 函数，还是 Windows 的 ioctlsocket，建议读者在实际编码中判断一下函数返回值以确定是否调用成功。

**send 和 recv 函数在阻塞和非阻塞模式下的行为**

send 和 recv 函数其实名不符实。

send 函数本质上并不是往网络上发送数据，而是将应用层发送缓冲区的数据拷贝到内核缓冲区（下文为了叙述方便，我们以“网卡缓冲区”代指）中去，至于什么时候数据会从网卡缓冲区中真正地发到网络中去要根据 TCP/IP 协议栈的行为来确定，这种行为涉及到一个叫 nagel 算法和 TCP_NODELAY 的 socket 选项，我们将在《**nagle算法与 TCP_NODELAY**》章节详细介绍。

recv 函数本质上也并不是从网络上收取数据，而只是将内核缓冲区中的数据拷贝到应用程序的缓冲区中，当然拷贝完成以后会将内核缓冲区中该部分数据移除。

可以用下面一张图来描述上述事实：

![](../imgs/socketmode1.webp)

通过上图我们知道，不同的程序进行网络通信时，发送的一方会将内核缓冲区的数据通过网络传输给接收方的内核缓冲区。在应用程序 A 与 应用程序 B 建立了 TCP 连接之后，假设应用程序 A 不断调用 send 函数，这样数据会不断拷贝至对应的内核缓冲区中，如果 B 那一端一直不调用 recv 函数，那么 B 的内核缓冲区被填满以后，A 的内核缓冲区也会被填满，此时 A 继续调用 send 函数会是什么结果呢？ 具体的结果取决于该 socket 是否是阻塞模式。我们这里先给出结论：

- 当 socket 是阻塞模式的，继续调用 send/recv 函数会导致程序阻塞在 send/recv 调用处。
- 当 socket 是非阻塞模式，继续调用 send/recv 函数，send/recv 函数不会阻塞程序执行流，而是会立即出错返回，我们会得到一个相关的错误码，Linux 平台上该错误码为 EWOULDBLOCK 或 EAGAIN（这两个错误码值相同），Windows 平台上错误码为 WSAEWOULDBLOCK。

我们实际来编写一下代码来验证一下以上说的两种情况。

## socket 阻塞模式下的 send 行为

服务端代码（blocking_server.cpp）如下：

```
/**
 * 验证阻塞模式下send函数的行为，server端
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
    //1.创建一个侦听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    //2.初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        close(listenfd);
        return -1;
    }

    //3.启动侦听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        close(listenfd);
        return -1;
    }

    while (true)
    {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        //4. 接受客户端连接
        int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if (clientfd != -1)
        {             
            //只接受连接，不调用recv收取任何数据
            std:: cout << "accept a client connection." << std::endl;
        }
    }

    //7.关闭侦听socket
    close(listenfd);

    return 0;
}
```

客户端代码（blocking_client.cpp）如下：

```
/**
 * 验证阻塞模式下send函数的行为，client端
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        return -1;
    }

    //3. 不断向服务器发送数据，或者出错退出
    int count = 0;
    while (true)
    {
        int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
        if (ret != strlen(SEND_DATA))
        {
            std::cout << "send data error." << std::endl;
            break;
        } 
        else
        {
            count ++;
            std::cout << "send data successfully, count = " << count << std::endl;
        }
    }

    //5. 关闭socket
    close(clientfd);

    return 0;
}
```

在 shell 中分别编译这两个 cpp 文件得到两个可执行程序 **blocking_server** 和 **blocking_client**：

```
g++ -g -o blocking_server blocking_server.cpp
g++ -g -o blocking_client blocking_client.cpp
```

我们先启动 **blocking_server**，然后用 gdb 启动 **blocking_client**，输入 **run** 命令让 **blocking_client**跑起来，**blocking_client** 会不断地向 **blocking_server** 发送"**helloworld**"字符串，每次 send 成功后，会将计数器 **count** 的值打印出来，计数器会不断增加，程序运行一段时间后，计数器 **count** 值不再增加且程序不再有输出。操作过程及输出结果如下：

**blocking_server** 端：

```
[root@localhost testsocket]# ./blocking_server 
accept a client connection.
[root@localhost testsocket]# gdb blocking_client
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-100.el7_4.1
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /root/testsocket/blocking_client...done.
(gdb) run
//输出结果太多，省略部分...
send data successfully, count = 355384
send data successfully, count = 355385
send data successfully, count = 355386
send data successfully, count = 355387
send data successfully, count = 355388
send data successfully, count = 355389
send data successfully, count = 355390
```

此时程序不再有输出，说明我们的程序应该“卡在”某个地方，继续按 **Ctrl + C** 让 gdb 中断下来，输入 **bt** 命令查看此时的调用堆栈，我们发现我们的程序确实阻塞在 **send** 函数调用处：

```
^C
Program received signal SIGINT, Interrupt.
0x00007ffff72f130d in send () from /lib64/libc.so.6
(gdb) bt
#0  0x00007ffff72f130d in send () from /lib64/libc.so.6
#1  0x0000000000400b46 in main (argc=1, argv=0x7fffffffe598) at blocking_client.cpp:41
(gdb) 
```

上面的示例验证了如果一端一直发数据，而对端应用层一直不取数据（或收取数据的速度慢于发送速度），则很快两端的内核缓冲区很快就会被填满，导致发送端调用 send 函数被阻塞。这里说的“**内核缓冲区**” 其实有个专门的名字，即 TCP 窗口。也就是说 socket 阻塞模式下， send 函数在 TCP 窗口太小时的行为是阻塞当前程序执行流（即阻塞 send 函数所在的线程的执行）。

说点题外话，上面的例子，我们每次发送一个“**helloworld**”（10个字节），一共发了 355390 次（每次测试的结果略有不同），我们可以粗略地算出 TCP 窗口的大小大约等于 1.7 M左右 （10 * 355390 / 2）。

让我们再深入一点，我们利用 Linux tcpdump 工具来动态看一下这种情形下 TCP 窗口大小的动态变化。需要注意的是，Linux 下使用 tcpdump 这个命令需要有 root 权限。

我们开启三个 shell 窗口，在第一个窗口先启动 **blocking_server** 进程，在第二个窗口用 tcpdump 抓经过 TCP 端口 3000 上的数据包：

```
[root@localhost testsocket]# tcpdump -i any -nn -S 'tcp port 3000'    
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on any, link-type LINUX_SLL (Linux cooked), capture size 262144 bytes
```

接着在第三个 shell 窗口，启动 **blocking_client**。当 **blocking_client** 进程不再输出时，我们抓包的结果如下：

```
[root@localhost testsocket]# tcpdump -i any -nn -S 'tcp port 3000' 
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on any, link-type LINUX_SLL (Linux cooked), capture size 262144 bytes
11:52:35.907381 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [S], seq 1394135076, win 43690, options [mss 65495,sackOK,TS val 78907688 ecr 0,nop,wscale 7], length 0
20:32:21.261484 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [S.], seq 1233000591, ack 1394135077, win 43690, options [mss 65495,sackOK,TS val 78907688 ecr 78907688,nop,wscale 7], length 0
11:52:35.907441 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 0
11:52:35.907615 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1394135077:1394135087, ack 1233000592, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 10
11:52:35.907626 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1394135087, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 0
11:52:35.907785 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1394135087:1394135097, ack 1233000592, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 10
11:52:35.907793 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1394135097, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 0
11:52:35.907809 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1394135097:1394135107, ack 1233000592, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 10
11:52:35.907814 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1394135107, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 0
...内容太长， 部分省略...
11:52:40.075794 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395013717, win 374, options [nop,nop,TS val 78911856 ecr 78911816], length 0
11:52:40.075829 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1395013717:1395030517, ack 1233000592, win 342, options [nop,nop,TS val 78911856 ecr 78911856], length 16800
11:52:40.115847 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395030517, win 305, options [nop,nop,TS val 78911896 ecr 78911856], length 0
11:52:40.115866 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1395030517:1395047317, ack 1233000592, win 342, options [nop,nop,TS val 78911896 ecr 78911896], length 16800
11:52:40.155703 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395047317, win 174, options [nop,nop,TS val 78911936 ecr 78911896], length 0
11:52:40.155752 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1395047317:1395064117, ack 1233000592, win 342, options [nop,nop,TS val 78911936 ecr 78911936], length 16800
11:52:40.195132 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395064117, win 43, options [nop,nop,TS val 78911976 ecr 78911936], length 0
11:52:40.435748 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [P.], seq 1395064117:1395069621, ack 1233000592, win 342, options [nop,nop,TS val 78912216 ecr 78911976], length 5504
11:52:40.435782 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78912216 ecr 78912216], length 0
11:52:40.670661 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78912451 ecr 78912216], length 0
11:52:40.670674 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78912451 ecr 78912216], length 0
11:52:41.141703 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78912922 ecr 78912451], length 0
11:52:42.083643 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78913864 ecr 78912451], length 0
11:52:42.083655 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78913864 ecr 78912216], length 0
11:52:43.967506 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78915748 ecr 78913864], length 0
11:52:43.967532 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78915748 ecr 78912216], length 0
11:52:47.739259 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78919520 ecr 78915748], length 0
11:52:47.739274 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78919520 ecr 78912216], length 0
11:52:55.275863 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78927056 ecr 78919520], length 0
11:52:55.275931 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [.], ack 1395069621, win 0, options [nop,nop,TS val 78927056 ecr 78912216], length 0
```

抓取到的前三个数据包是 **blocking_client** 与 **blocking_server** 建立三次握手的过程。

```
11:52:35.907381 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [S], seq 1394135076, win 43690, options [mss 65495,sackOK,TS val 78907688 ecr 0,nop,wscale 7], length 0
20:32:21.261484 IP 127.0.0.1.3000 > 127.0.0.1.40846: Flags [S.], seq 1233000591, ack 1394135077, win 43690, options [mss 65495,sackOK,TS val 78907688 ecr 78907688,nop,wscale 7], length 0
11:52:35.907441 IP 127.0.0.1.40846 > 127.0.0.1.3000: Flags [.], ack 1233000592, win 342, options [nop,nop,TS val 78907688 ecr 78907688], length 0
```

示意图如下：

![](../imgs/socketmode2.webp)

当每次 **blocking_client** 给 **blocking_server** 发数据以后，**blocking_server** 会应答 **blocking_server**，在每次应答的数据包中会带上自己的当前可用 TCP 窗口大小（看上文中结果从 **127.0.0.1.3000 > 127.0.0.1.40846**方向的数据包的 **win** 字段大小变化），由于 TCP 流量控制和拥赛控制机制的存在，**blocking_server** 端的 TCP 窗口大小短期内会慢慢增加，后面随着接收缓冲区中数据积压越来越多， TCP 窗口会慢慢变小，最终变为 0。

另外，细心的读者如果实际去做一下这个实验会发现一个现象，即当 tcpdump 已经显示对端的 TCP 窗口是 0 时， **blocking_client** 仍然可以继续发送一段时间的数据，此时的数据已经不是在发往对端，而是逐渐填满到本端的内核发送缓冲区中去了，这也验证了 send 函数实际上是往内核缓冲区中拷贝数据这一行为。

## socket 非阻塞模式下的 send 行为

我们再来验证一下非阻塞 socket 的 send 行为，**server** 端的代码不变，我们将 **blocking_client.cpp** 中 socket 设置成非阻塞的，修改后的代码如下：

```
/**
 * 验证非阻塞模式下send函数的行为，client端，nonblocking_client.cpp
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    //连接成功以后，我们再将 clientfd 设置成非阻塞模式，
    //不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL,  newSocketFlag) == -1)
    {
        close(clientfd);
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    //3. 不断向服务器发送数据，或者出错退出
    int count = 0;
    while (true)
    {
        int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
        if (ret == -1) 
        {
            //非阻塞模式下send函数由于TCP窗口太小发不出去数据，错误码是EWOULDBLOCK
            if (errno == EWOULDBLOCK)
            {
                std::cout << "send data error as TCP Window size is too small." << std::endl;
                continue;
            } 
            else if (errno == EINTR)
            {
                //如果被信号中断，我们继续重试
                std::cout << "sending data interrupted by signal." << std::endl;
                continue;
            } 
            else 
            {
                std::cout << "send data error." << std::endl;
                break;
            }
        }
        if (ret == 0)
        {
            //对端关闭了连接，我们也关闭
            std::cout << "send data error." << std::endl;
            close(clientfd);
            break;
        } 
        else
        {
            count ++;
            std::cout << "send data successfully, count = " << count << std::endl;
        }
    }

    //5. 关闭socket
    close(clientfd);

    return 0;
}
```

编译 **nonblocking_client.cpp** 得到可执行程序 **nonblocking_client**：

```
 g++ -g -o nonblocking_client nonblocking_client.cpp 
```

运行 **nonblocking_client**，运行一段时间后，由于对端和本端的 TCP 窗口已满，数据发不出去了，但是 send 函数不会阻塞，而是立即返回，返回值是 **-1**（Windows 系统上 返回 SOCKET_ERROR，这个宏的值也是 **-1**），此时得到错误码是 **EWOULDBLOCK**。执行结果如下：

![](../imgs/socketmode3.webp)

## socket 阻塞模式下的 recv 行为 

在了解了 send 函数的行为，我们再来看一下阻塞模式下的 recv 函数行为。服务器端代码不需要修改，我们修改一下客户端代码，如果服务器端不给客户端发数据，此时客户端调用 recv 函数执行流会阻塞在 recv 函数调用处。继续修改一下客户端代码：

```
/**
 * 验证阻塞模式下recv函数的行为，client端，blocking_client_recv.cpp
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    //直接调用recv函数，程序会阻塞在recv函数调用处
    char recvbuf[32] = {0};
    int ret = recv(clientfd, recvbuf, 32, 0);
    if (ret > 0) 
    {
        std::cout << "recv successfully." << std::endl;
    } 
    else 
    {
        std::cout << "recv data error." << std::endl;
    }

    //5. 关闭socket
    close(clientfd);

    return 0;
}
```

编译 **blocking_client_recv.cpp** 并使用启动，我们发现程序既没有打印 recv 调用成功的信息也没有调用失败的信息，将程序中断下来，使用 **bt** 命令查看此时的调用堆栈，发现程序确实阻塞在 recv 函数调用处。

```
[root@localhost testsocket]# g++ -g -o blocking_client_recv blocking_client_recv.cpp 
[root@localhost testsocket]# gdb blocking_client_recv
Reading symbols from /root/testsocket/blocking_client_recv...done.
(gdb) r
Starting program: /root/testsocket/blocking_client_recv 
^C
Program received signal SIGINT, Interrupt.
0x00007ffff72f119d in recv () from /lib64/libc.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7_4.2.x86_64 libgcc-4.8.5-16.el7_4.2.x86_64 libstdc++-4.8.5-16.el7_4.2.x86_64
(gdb) bt
#0  0x00007ffff72f119d in recv () from /lib64/libc.so.6
#1  0x0000000000400b18 in main (argc=1, argv=0x7fffffffe588) at blocking_client_recv.cpp:40
```

## socket 非阻塞模式下的 recv 行为

非阻塞模式下如果当前无数据可读，recv 函数将立即返回，返回值为 **-1**，错误码为 **EWOULDBLOCK**。将客户端代码修成一下：

```
/**
 * 验证阻塞模式下recv函数的行为，client端，blocking_client_recv.cpp
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    //连接成功以后，我们再将 clientfd 设置成非阻塞模式，
    //不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL,  newSocketFlag) == -1)
    {
        close(clientfd);
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    //直接调用recv函数，程序会阻塞在recv函数调用处
    while (true)
    {
        char recvbuf[32] = {0};
        int ret = recv(clientfd, recvbuf, 32, 0);
        if (ret > 0) 
        {
            //收到了数据
            std::cout << "recv successfully." << std::endl;
        } 
        else if (ret == 0)
        {
            //对端关闭了连接
            std::cout << "peer close the socket." << std::endl; 
            break;
        } 
        else if (ret == -1) 
        {
            if (errno == EWOULDBLOCK)
            {
                std::cout << "There is no data available now." << std::endl;
            } 
            else if (errno == EINTR) 
            {
                //如果被信号中断了，则继续重试recv函数
                std::cout << "recv data interrupted by signal." << std::endl;               
            } else
            {
                //真的出错了
                break;
            }
        }
    }

    //5. 关闭socket
    close(clientfd);

    return 0;
}
```

执行结果与我们预期的一模一样， recv 函数在无数据可读的情况下并不会阻塞情绪，所以程序会一直有“**There is no data available now.**”相关的输出。

![](../imgs/socketmode4.webp)


# bind 函数重难点解析

## bind 函数如何选择绑定地址

bind 函数的基本用法如下：

```
struct sockaddr_in bindaddr;
bindaddr.sin_family = AF_INET;
bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
bindaddr.sin_port = htons(3000);
if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
{
    std::cout << "bind listen socket error." << std::endl;
    return -1;
}
```

其中 bind 的地址我们使用了一个宏叫 **INADDR_ANY** ，关于这个宏的解释如下：

```
If an application does not care what local address is assigned, 
specify the constant value INADDR_ANY for an IPv4 local address
or the constant value in6addr_any for an IPv6 local address 
in the sa_data member of the name parameter. This allows the 
underlying service provider to use any appropriate network address,
potentially simplifying application programming in the presence of 
multihomed hosts (that is, hosts that have more than one network 
interface and address).
```

意译一下：

```
如果应用程序不关心bind绑定的ip地址，可以使用INADDR_ANY(如果是IPv6，
则对应in6addr_any)，这样底层的（协议栈）服务会自动选择一个合适的ip地址，
这样使在一个有多个网卡机器上选择ip地址问题变得简单。
```

也就是说 **INADDR_ANY** 相当于地址 **0.0.0.0**。可能读者还是不太明白我想表达什么。这里我举个例子，假设我们在一台机器上开发一个服务器程序，使用 bind 函数时，我们有多个ip 地址可以选择。首先，这台机器对外访问的ip地址是**120.55.94.78**，这台机器在当前局域网的地址是**192.168.1.104**；同时这台机器有本地回环地址**127.0.0.1**。

如果你指向本机上可以访问，那么你 bind 函数中的地址就可以使用**127.0.0.1**; 如果你的服务只想被局域网内部机器访问，bind 函数的地址可以使用**192.168.1.104**；如果 希望这个服务可以被公网访问，你就可以使用地址**0.0.0.0**或 **INADDR_ANY**。

## bind 函数端口号问题

网络通信程序的基本逻辑是客户端连接服务器，即从客户端的**地址:端口**连接到服务器**地址:端口**上，以 4.2 小节中的示例程序为例，服务器端的端口号使用 3000，那客户端连接时的端口号是多少呢？TCP 通信双方中一般服务器端端口号是固定的，而客户端端口号是连接发起时由操作系统随机分配的（不会分配已经被占用的端口）。端口号是一个 C short 类型的值，其范围是0～65535，知道这点很重要，所以我们在编写压力测试程序时，由于端口数量的限制，在某台机器上网卡地址不变的情况下压力测试程序理论上最多只能发起六万五千多个连接。注意我说的是理论上，在实际情况下，由于当时的操作系统很多端口可能已经被占用，实际可以使用的端口比这个更少，例如，一般规定端口号在1024以下的端口是保留端口，不建议用户程序使用。而对于 Windows 系统，MSDN 甚至明确地说：

> On Windows Vista and later, the dynamic client port range is a value between 49152 and 65535. This is a change from Windows Server 2003 and earlier where the dynamic client port range was a value between 1025 and 5000.
> Vista 及以后的Windows，可用的动态端口范围是49152～65535，而 Windows Server及更早的系统，可以的动态端口范围是1025~5000。（你可以通过修改注册表来改变这一设置，参考网址：https://docs.microsoft.com/en-us/windows/desktop/api/winsock/nf-winsock-bind）

如果将 bind 函数中的端口号设置成0，那么操作系统会随机给程序分配一个可用的侦听端口，当然服务器程序一般不会这么做，因为服务器程序是要对外服务的，必须让客户端知道确切的ip地址和端口号。

很多人觉得只有服务器程序可以调用 bind 函数绑定一个端口号，其实不然，在一些特殊的应用中，我们需要客户端程序以指定的端口号去连接服务器，此时我们就可以在客户端程序中调用 bind 函数绑定一个具体的端口。

我们用代码来实际验证一下上路所说的，为了能看到连接状态，我们将客户端和服务器关闭socket的代码注释掉，这样连接会保持一段时间。

- **情形一：客户端代码不绑定端口**

修改后的服务器代码如下：

```
/**
 * TCP服务器通信基本流程
 * zhangyl 2018.12.13
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>

int main(int argc, char* argv[])
{
    //1.创建一个侦听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    //2.初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        return -1;
    }

    //3.启动侦听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    //记录所有客户端连接的容器
    std::vector<int> clientfds;
    while (true)
    {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        //4. 接受客户端连接
        int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if (clientfd != -1)
        {             
            char recvBuf[32] = {0};
            //5. 从客户端接受数据
            int ret = recv(clientfd, recvBuf, 32, 0);
            if (ret > 0) 
            {
                std::cout << "recv data from client, data: " << recvBuf << std::endl;
                //6. 将收到的数据原封不动地发给客户端
                ret = send(clientfd, recvBuf, strlen(recvBuf), 0);
                if (ret != strlen(recvBuf))
                    std::cout << "send data error." << std::endl;

                std::cout << "send data to client successfully, data: " << recvBuf << std::endl;
            } 
            else 
            {
                std::cout << "recv data error." << std::endl;
            }

            //close(clientfd);
            clientfds.push_back(clientfd);
        }
    }

    //7.关闭侦听socket
    close(listenfd);

    return 0;
}
```

修改后的客户端代码如下：

```
/**
 * TCP客户端通信基本流程
 * zhangyl 2018.12.13
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        return -1;
    }

    //3. 向服务器发送数据
    int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
    if (ret != strlen(SEND_DATA))
    {
        std::cout << "send data error." << std::endl;
        return -1;
    }

    std::cout << "send data successfully, data: " << SEND_DATA << std::endl;

    //4. 从客户端收取数据
    char recvBuf[32] = {0};
    ret = recv(clientfd, recvBuf, 32, 0);
    if (ret > 0) 
    {
        std::cout << "recv data successfully, data: " << recvBuf << std::endl;
    } 
    else 
    {
        std::cout << "recv data error, data: " << recvBuf << std::endl;
    }

    //5. 关闭socket
    //close(clientfd);
    //这里仅仅是为了让客户端程序不退出
    while (true) 
    {
        sleep(3);
    }

    return 0;
}
```

将程序编译好后（编译方法和上文一样），我们先启动server，再启动三个客户端。然后通过 **lsof** 命令查看当前机器上的 TCP 连接信息，为了更清楚地显示结果，已经将不相关的连接信息去掉了，结果如下所示：

```
[root@localhost ~]# lsof -i -Pn
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
server   1445 root    3u  IPv4  21568      0t0  TCP *:3000 (LISTEN)
server   1445 root    4u  IPv4  21569      0t0  TCP 127.0.0.1:3000->127.0.0.1:40818 (ESTABLISHED)
server   1445 root    5u  IPv4  21570      0t0  TCP 127.0.0.1:3000->127.0.0.1:40820 (ESTABLISHED)
server   1445 root    6u  IPv4  21038      0t0  TCP 127.0.0.1:3000->127.0.0.1:40822 (ESTABLISHED)
client   1447 root    3u  IPv4  21037      0t0  TCP 127.0.0.1:40818->127.0.0.1:3000 (ESTABLISHED)
client   1448 root    3u  IPv4  21571      0t0  TCP 127.0.0.1:40820->127.0.0.1:3000 (ESTABLISHED)
client   1449 root    3u  IPv4  21572      0t0  TCP 127.0.0.1:40822->127.0.0.1:3000 (ESTABLISHED)
```

上面的结果显示，**server** 进程（进程 ID 是 **1445**）在 **3000** 端口开启侦听，有三个 **client** 进程（进程 ID 分别是**1447**、**1448**、**1449**）分别通过端口号 **40818**、**40820**、**40822** 连到 **server** 进程上的，作为客户端的一方，端口号是系统随机分配的。

- **情形二：客户端绑定端口号 0**

  服务器端代码保持不变，我们修改下客户端代码：

  ```
  /**
   * TCP服务器通信基本流程
   * zhangyl 2018.12.13
   */
  ```

  ```
  #include <sys/types.h> 
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <iostream>
  #include <string.h>
  
  #define SERVER_ADDRESS "127.0.0.1"
  #define SERVER_PORT     3000
  #define SEND_DATA       "helloworld"
  
  int main(int argc, char* argv[])
  {
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }
  
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //将socket绑定到0号端口上去
    bindaddr.sin_port = htons(0);
    if (bind(clientfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind socket error." << std::endl;
        return -1;
    }
  
    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        return -1;
    }
  
    //3. 向服务器发送数据
    int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
    if (ret != strlen(SEND_DATA))
    {
        std::cout << "send data error." << std::endl;
        return -1;
    }
  
    std::cout << "send data successfully, data: " << SEND_DATA << std::endl;
  
    //4. 从客户端收取数据
    char recvBuf[32] = {0};
    ret = recv(clientfd, recvBuf, 32, 0);
    if (ret > 0) 
    {
        std::cout << "recv data successfully, data: " << recvBuf << std::endl;
    } 
    else 
    {
        std::cout << "recv data error, data: " << recvBuf << std::endl;
    }
  
    //5. 关闭socket
    //close(clientfd);
    //这里仅仅是为了让客户端程序不退出
    while (true) 
    {
        sleep(3);
    }
  
    return 0;
  }
  ```

  我们再次编译客户端程序，并启动三个 **client** 进程，然后用 **lsof** 命令查看机器上的 TCP 连接情况，结果如下所示：

  ```
  [root@localhost ~]# lsof -i -Pn
  COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
  server   1593 root    3u  IPv4  21807      0t0  TCP *:3000 (LISTEN)
  server   1593 root    4u  IPv4  21808      0t0  TCP 127.0.0.1:3000->127.0.0.1:44220 (ESTABLISHED)
  server   1593 root    5u  IPv4  19311      0t0  TCP 127.0.0.1:3000->127.0.0.1:38990 (ESTABLISHED)
  server   1593 root    6u  IPv4  21234      0t0  TCP 127.0.0.1:3000->127.0.0.1:42365 (ESTABLISHED)
  client   1595 root    3u  IPv4  22626      0t0  TCP 127.0.0.1:44220->127.0.0.1:3000 (ESTABLISHED)
  client   1611 root    3u  IPv4  21835      0t0  TCP 127.0.0.1:38990->127.0.0.1:3000 (ESTABLISHED)
  client   1627 root    3u  IPv4  21239      0t0  TCP 127.0.0.1:42365->127.0.0.1:3000 (ESTABLISHED)
  ```

  通过上面的结果，我们发现三个 **client** 进程使用的端口号仍然是系统随机分配的，也就是说绑定 **0** 号端口和没有绑定效果是一样的。

- **情形三：客户端绑定一个固定端口**

  我们这里使用 **20000** 端口，当然读者可以根据自己的喜好选择，只要保证所选择的端口号当前没有被其他程序占用即可，服务器代码保持不变，客户端绑定代码中的端口号从 **0** 改成 **20000**。这里为了节省篇幅，只贴出修改处的代码：

  ```
  struct sockaddr_in bindaddr;
  bindaddr.sin_family = AF_INET;
  bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //将socket绑定到20000号端口上去
  bindaddr.sin_port = htons(20000);
  if (bind(clientfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
  {
      std::cout << "bind socket error." << std::endl;
      return -1;
  }
  ```

  再次重新编译程序，先启动一个客户端后，我们看到此时的 TCP 连接状态：

  ```
  [root@localhost testsocket]# lsof -i -Pn
  COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
  server   1676 root    3u  IPv4  21933      0t0  TCP *:3000 (LISTEN)
  server   1676 root    4u  IPv4  21934      0t0  TCP 127.0.0.1:3000->127.0.0.1:20000 (ESTABLISHED)
  client   1678 root    3u  IPv4  21336      0t0  TCP 127.0.0.1:20000->127.0.0.1:3000 (ESTABLISHED)
  ```

  通过上面的结果，我们发现 **client** 进程确实使用 **20000** 号端口连接到 **server** 进程上去了。这个时候如果我们再开启一个 **client** 进程，我们猜想由于端口号 **20000** 已经被占用，新启动的 **client** 会由于调用 **bind** 函数出错而退出，我们实际验证一下：

  ```
  [root@localhost testsocket]# ./client 
  bind socket error.
  [root@localhost testsocket]# 
  ```

  结果确实和我们预想的一样。

在技术面试的时候，有时候面试官会问 TCP 网络通信的客户端程序中的 socket 是否可以调用 bind 函数，相信读到这里，聪明的读者已经有答案了。

另外，Linux 的 **nc** 命令有个 **-p** 选项（字母 **p** 是小写），这个选项的作用就是 **nc** 在模拟客户端程序时，可以使用指定端口号连接到服务器程序上去，实现原理相信读者也明白了。我们还是以上面的服务器程序为例，这个我们不用我们的 **client** 程序，改用 **nc** 命令来模拟客户端。在 **shell** 终端输入：

```
[root@localhost testsocket]# nc -v -p 9999 127.0.0.1 3000
Ncat: Version 6.40 ( http://nmap.org/ncat )
Ncat: Connected to 127.0.0.1:3000.
My name is zhangxf
My name is zhangxf
```

**-v** 选项表示输出 **nc** 命令连接的详细信息，这里连接成功以后，会输出“**Ncat: Connected to 127.0.0.1:3000.**” 提示已经连接到服务器的 **3000** 端口上去了。

**-p** 选项的参数值是 **9999** 表示，我们要求 **nc** 命令本地以端口号 **9999** 连接服务器，注意不要与端口号 **3000** 混淆，**3000** 是服务器的侦听端口号，也就是我们的连接的目标端口号，**9999** 是我们客户端使用的端口号。我们用 **lsof** 命令来验证一下我们的 **nc** 命令是否确实以 **9999** 端口号连接到 **server** 进程上去了。

```
[root@localhost testsocket]# lsof -i -Pn
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
server   1676 root    3u  IPv4  21933      0t0  TCP *:3000 (LISTEN)
server   1676 root    7u  IPv4  22405      0t0  TCP 127.0.0.1:3000->127.0.0.1:9999 (ESTABLISHED)
nc       2005 root    3u  IPv4  22408      0t0  TCP 127.0.0.1:9999->127.0.0.1:3000 (ESTABLISHED)
```

结果确实如我们期望的一致。

当然，我们用 **nc** 命令连接上 **server** 进程以后，我们还给服务器发了一条消息"**My name is zhangxf**"，**server** 程序收到消息后把这条消息原封不动地返还给我们，以下是 **server** 端运行结果：

```
[root@localhost testsocket]# ./server   
recv data from client, data: My name is zhangxf

send data to client successfully, data: My name is zhangxf
```

关于 **lsof** 和 **nc** 命令我们会在后面的系列文章中详细讲解。


## connect 函数在阻塞和非阻塞模式下的行为

在 socket 是阻塞模式下 connect 函数会一直到有明确的结果才会返回（或连接成功或连接失败），如果服务器地址“较远”，连接速度比较慢，connect 函数在连接过程中可能会导致程序阻塞在 connect 函数处好一会儿（如两三秒之久），虽然这一般也不会对依赖于网络通信的程序造成什么影响，但在实际项目中，我们一般倾向使用所谓的**异步的 connect** 技术，或者叫**非阻塞的 connect**。这个流程一般有如下步骤：

```
1. 创建socket，并将 socket 设置成非阻塞模式；
2. 调用 connect 函数，此时无论 connect 函数是否连接成功会立即返回；如果返回-1并不表示连接出错，如果此时错误码是EINPROGRESS
3. 接着调用 select 函数，在指定的时间内判断该 socket 是否可写，如果可写说明连接成功，反之则认为连接失败。
```

按上述流程编写代码如下：

```
/**
 * 异步的connect写法，nonblocking_connect.cpp
 * zhangyl 2018.12.17
 */
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT     3000
#define SEND_DATA       "helloworld"

int main(int argc, char* argv[])
{
    //1.创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //连接成功以后，我们再将 clientfd 设置成非阻塞模式，
    //不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL,  newSocketFlag) == -1)
    {
        close(clientfd);
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    for (;;)
    {
        int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (ret == 0)
        {
            std::cout << "connect to server successfully." << std::endl;
            close(clientfd);
            return 0;
        } 
        else if (ret == -1) 
        {
            if (errno == EINTR)
            {
                //connect 动作被信号中断，重试connect
                std::cout << "connecting interruptted by signal, try again." << std::endl;
                continue;
            } else if (errno == EINPROGRESS)
            {
                //连接正在尝试中
                break;
            } else {
                //真的出错了，
                close(clientfd);
                return -1;
            }
        }
    }

    fd_set writeset;
    FD_ZERO(&writeset);
    FD_SET(clientfd, &writeset);
    //可以利用tv_sec和tv_usec做更小精度的超时控制
    struct timeval tv;
    tv.tv_sec = 3;  
    tv.tv_usec = 0;
    if (select(clientfd + 1, NULL, &writeset, NULL, &tv) == 1)
    {
        std::cout << "[select] connect to server successfully." << std::endl;
    } else {
        std::cout << "[select] connect to server error." << std::endl;
    }

    //5. 关闭socket
    close(clientfd);

    return 0;
}
```

为了区别到底是在调用 connect 函数时判断连接成功还是通过 select 函数判断连接成功，我们在后者的输出内容中加上了“**[select]**”标签以示区别。

我们先用 **nc** 命令启动一个服务器程序：

```
nc -v -l 0.0.0.0 3000
```

然后编译客户端程序并执行：

```
[root@localhost testsocket]# g++ -g -o nonblocking_connect nonblocking_connect.cpp 
[root@localhost testsocket]# ./nonblocking_connect 
[select] connect to server successfully.
```

我们把服务器程序关掉，再重新启动一下客户端，这个时候应该会连接失败，程序输出结果如下：

```
[root@localhost testsocket]# ./nonblocking_connect 
[select] connect to server successfully.
```

奇怪？为什么连接不上也会得出一样的输出结果？难道程序有问题？这是因为：

- 在 Windows 系统上，一个 socket 没有建立连接之前，我们使用 select 函数检测其是否可写，能得到正确的结果（不可写），连接成功后检测，会变为可写。所以，上述介绍的异步 **connect** 写法流程在 Windows 系统上时没有问题的。
- 在 Linux 系统上一个 socket 没有建立连接之前，用 select 函数检测其是否可写，你也会得到可写得结果，所以上述流程并不适用于 Linux 系统。正确的做法是，connect 之后，不仅要用 **select** 检测可写，还要检测此时 socket 是否出错，通过错误码来检测确定是否连接上，错误码为 0 表示连接上，反之为未连接上。完整代码如下：

```
  /**
   * Linux 下正确的异步的connect写法，linux_nonblocking_connect.cpp
   * zhangyl 2018.12.17
   */
  #include <sys/types.h> 
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <iostream>
  #include <string.h>
  #include <stdio.h>
  #include <fcntl.h>
  #include <errno.h>

  #define SERVER_ADDRESS "127.0.0.1"
  #define SERVER_PORT     3000
  #define SEND_DATA       "helloworld"

  int main(int argc, char* argv[])
  {
      //1.创建一个socket
      int clientfd = socket(AF_INET, SOCK_STREAM, 0);
      if (clientfd == -1)
      {
          std::cout << "create client socket error." << std::endl;
          return -1;
      }

      //连接成功以后，我们再将 clientfd 设置成非阻塞模式，
      //不能在创建时就设置，这样会影响到 connect 函数的行为
      int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
      int newSocketFlag = oldSocketFlag | O_NONBLOCK;
      if (fcntl(clientfd, F_SETFL,  newSocketFlag) == -1)
      {
          close(clientfd);
          std::cout << "set socket to nonblock error." << std::endl;
          return -1;
      }

      //2.连接服务器
      struct sockaddr_in serveraddr;
      serveraddr.sin_family = AF_INET;
      serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
      serveraddr.sin_port = htons(SERVER_PORT);
      for (;;)
      {
          int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
          if (ret == 0)
          {
              std::cout << "connect to server successfully." << std::endl;
              close(clientfd);
              return 0;
          } 
          else if (ret == -1) 
          {
              if (errno == EINTR)
              {
                  //connect 动作被信号中断，重试connect
                  std::cout << "connecting interruptted by signal, try again." << std::endl;
                  continue;
              } else if (errno == EINPROGRESS)
              {
                  //连接正在尝试中
                  break;
              } else {
                  //真的出错了，
                  close(clientfd);
                  return -1;
              }
          }
      }

      fd_set writeset;
      FD_ZERO(&writeset);
      FD_SET(clientfd, &writeset);
      //可以利用tv_sec和tv_usec做更小精度的超时控制
      struct timeval tv;
      tv.tv_sec = 3;  
      tv.tv_usec = 0;
      if (select(clientfd + 1, NULL, &writeset, NULL, &tv) != 1)
      {
          std::cout << "[select] connect to server error." << std::endl;
          close(clientfd);
          return -1;
      }

      int err;
      socklen_t len = static_cast<socklen_t>(sizeof err);
      if (::getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
      {
          close(clientfd);
          return -1;
      }

      if (err == 0)
          std::cout << "connect to server successfully." << std::endl;
      else
          std::cout << "connect to server error." << std::endl;

      //5. 关闭socket
      close(clientfd);

      return 0;
  }
```

> 当然，在实际的项目中，第 3 个步骤中 Linux 平台上你也可以使用 **poll** 函数来判断 socket 是否可写；在 Windows 平台上你可以使用 **WSAEventSelect** 或 **WSAAsyncSelect** 函数判断连接是否成功，关于这三个函数我们将在后面的章节中详细讲解，这里暂且仅以 **select** 函数为例。
