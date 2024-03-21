## Socket

1.
* sockaddr_in的参数意义是什么
    ```c
    struct sockaddr_in {
        short            sin_family;   // 通常设置为 AF_INET
        unsigned short   sin_port;     // 表示端口号
        struct in_addr   sin_addr;     // 表示 IP 地址
        char             sin_zero[8];  // 通常设置为 0
    };
    ```

    各个字段的含义如下：

    - `sin_family`：这个字段用于指定地址家族，对于 IP 地址，这个字段通常被设置为 `AF_INET`。

    - `sin_port`：这个字段用于指定端口号。注意，这个字段使用的是网络字节序，所以在设置这个字段时，通常需要使用 `htons` 函数将主机字节序转换为网络字节序。

    - `sin_addr`：这个字段用于指定 IP 地址。这个字段是一个 `in_addr` 结构体，包含一个 `s_addr` 字段，这个字段是一个无符号长整型（`unsigned long`），用于存储 IP 地址。注意，这个字段使用的是网络字节序，所以在设置这个字段时，通常需要使用 `inet_addr` 函数将点分十进制的 IP 地址转换为网络字节序。

    - `sin_zero`：这个字段没有实际意义，只是为了让 `sockaddr_in` 结构体的大小与 `sockaddr` 结构体的大小相同，通常被设置为 0。

* bind()参数的意义是什么

* accpet()参数的意义是什么

* socket()参数的意义是什么
    ```c
    int socket(int domain, int type, int protocol);
    ```

    `socket()` 函数的参数有以下含义：

    - `domain`：这个参数用于指定地址家族（Address Family）。对于 Internet 协议（IP），这个参数通常被设置为 `AF_INET`（表示 IPv4）或 `AF_INET6`（表示 IPv6）。地址家族决定了所使用的地址类型和通信协议。

    - `type`：这个参数用于指定套接字的类型（Socket Type）。常见的类型有 `SOCK_STREAM`（表示流式套接字，通常用于 TCP 连接）和 `SOCK_DGRAM`（表示数据报套接字，通常用于 UDP 连接）。

    - `protocol`：这个参数用于指定协议类型。通常情况下，我们会设置这个参数为 0，让系统自动选择合适的协议。例如，如果地址家族是 `AF_INET`，套接字类型是 `SOCK_STREAM`，那么系统会选择 TCP 协议。

    `socket()` 函数的返回值是一个套接字描述符（Socket Descriptor），这是一个整数，用于标识创建的套接字。如果函数调用失败，那么返回值会是 -1。