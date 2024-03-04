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