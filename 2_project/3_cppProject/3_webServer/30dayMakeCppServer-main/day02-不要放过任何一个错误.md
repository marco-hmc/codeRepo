# day02-不要放过任何一个错误

通常来讲，当一个系统调用返回-1，说明有error发生。我们来看看socket编程最常见的错误处理模版：
### 1. 错误码
```cpp
// 为了处理一个错误，需要至少占用五行代码，这使编程十分繁琐，程序也不好看，异常处理所占篇幅比程序本身都多。
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd == -1)
{
    print("socket create error");
    exit(-1);
}
```

### 2. 封装
```cpp
// 为了方便编码以及代码的可读性，可以封装一个错误处理函数：
void errif(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
errif(sockfd == -1, "socket create error");
```

### 3. 其他
```cpp
// 对于所有的函数，我们都使用这种方式处理错误：
errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");
errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");
int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
errif(clnt_sockfd == -1, "socket accept error");
errif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket connect error");
// 到现在最简单的错误处理函数已经封装好了，但这仅仅用于本教程的开发，在真实的服务器开发中，错误绝不是一个如此简单的话题。
```

### 4. xxx
当我们建立一个socket连接后，就可以使用`<unistd.h>`头文件中`read`和`write`来进行网络接口的数据读写操作了。
> 这两个函数用于TCP连接。如果是UDP，需要使用`sendto`和`recvfrom`，这些函数的详细用法可以参考游双《Linux高性能服务器编程》第五章第八节。

接下来的教程用注释的形式写在代码中，先来看服务器代码：
```cpp
while (true) {
    char buf[1024];     //定义缓冲区
    bzero(&buf, sizeof(buf));       //清空缓冲区
    ssize_t read_bytes = read(clnt_sockfd, buf, sizeof(buf)); //从客户端socket读到缓冲区，返回已读数据大小
    if(read_bytes > 0){
        printf("message from client fd %d: %s\n", clnt_sockfd, buf);  
        write(clnt_sockfd, buf, sizeof(buf));           //将相同的数据写回到客户端
    } else if(read_bytes == 0){             //read返回0，表示EOF
        printf("client fd %d disconnected\n", clnt_sockfd);
        close(clnt_sockfd);
        break;
    } else if(read_bytes == -1){        //read返回-1，表示发生错误，按照上文方法进行错误处理
        close(clnt_sockfd);
        errif(true, "socket read error");
    }
}
```
客户端代码逻辑是一样的：
```cpp
while(true){
    char buf[1024];     //定义缓冲区
    bzero(&buf, sizeof(buf));       //清空缓冲区
    scanf("%s", buf);             //从键盘输入要传到服务器的数据
    ssize_t write_bytes = write(sockfd, buf, sizeof(buf));      //发送缓冲区中的数据到服务器socket，返回已发送数据大小
    if(write_bytes == -1){          //write返回-1，表示发生错误
        printf("socket already disconnected, can't write any more!\n");
        break;
    }
    bzero(&buf, sizeof(buf));       //清空缓冲区 
    ssize_t read_bytes = read(sockfd, buf, sizeof(buf));    //从服务器socket读到缓冲区，返回已读数据大小
    if(read_bytes > 0){
        printf("message from server: %s\n", buf);
    }else if(read_bytes == 0){      //read返回0，表示EOF，通常是服务器断开链接，等会儿进行测试
        printf("server socket disconnected!\n");
        break;
    }else if(read_bytes == -1){     //read返回-1，表示发生错误，按照上文方法进行错误处理
        close(sockfd);
        errif(true, "socket read error");
    }
}
```
