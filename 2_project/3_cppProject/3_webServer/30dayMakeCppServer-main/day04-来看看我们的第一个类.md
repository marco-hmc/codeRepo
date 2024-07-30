# day04-来看看我们的第一个类

```cpp
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
errif(sockfd == -1, "socket create error");

struct sockaddr_in serv_addr;
bzero(&serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
serv_addr.sin_port = htons(8888);

errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");

errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

struct sockaddr_in clnt_addr;
bzero(&clnt_addr, sizeof(clnt_addr));
socklen_t clnt_addr_len = sizeof(clnt_addr);

int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
errif(clnt_sockfd == -1, "socket accept error");
```

```cpp
Socket *serv_sock = new Socket();
InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
serv_sock->bind(serv_addr);
serv_sock->listen();   
InetAddress *clnt_addr = new InetAddress();  
Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));    
```

类似的还有epoll，最精简的使用方式为：
```cpp
int epfd = epoll_create1(0);
errif(epfd == -1, "epoll create error");

struct epoll_event events[MAX_EVENTS], ev;
bzero(&events, sizeof(events) * MAX_EVENTS);

bzero(&ev, sizeof(ev));
ev.data.fd = sockfd;
ev.events = EPOLLIN | EPOLLET;

epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

while(true){
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
    errif(nfds == -1, "epoll wait error");
    for(int i = 0; i < nfds; ++i){
        // handle event
    }
}
```
而我们更希望这样来使用：
```cpp
Epoll *ep = new Epoll();
ep->addFd(serv_sock->getFd(), EPOLLIN | EPOLLET);
while(true){
    vector<epoll_event> events = ep->poll();
    for(int i = 0; i < events.size(); ++i){
        // handle event
    }
}
```
同样完全忽略了如错误处理之类的底层细节，大大简化了编程，增加了程序的可读性。

在今天的代码中，程序的功能和昨天一样，仅仅将`Socket`、`InetAddress`和`Epoll`封装成类，这也是面向对象编程的最核心、最基本的思想。现在我们的目录结构为：
```
client.cpp
Epoll.cpp
Epoll.h
InetAddress.cpp
InetAddress.h
Makefile
server.cpp
Socket.cpp
Socket.h
util.cpp
util.h
```

完整源代码：[https://github.com/yuesong-feng/30dayMakeCppServer/tree/main/code/day04](https://github.com/yuesong-feng/30dayMakeCppServer/tree/main/code/day04)
