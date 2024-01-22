#### **网络通信部分**
* 网络通信部分,主要有两大块,
1. 第一个是程序启动时,与服务端的交互;
2. 第二个就是文件下载与分享的 P2P 网络.
Prerequisites:
1. 具体的就是 Socket 的各种 API 函数,以及基于这些 API 逻辑的组合
2. 当然可能也会用到操作系统平台所特有的网络 API 函数,如 **WSAAsyncSelect** 网络模型.
Design Points:
1. 网络通信部分如何与 UI 部分进行数据交换:
   是使用队列?
    如果使用队列,多线程之间如何保持资源的一致性和解决资源竞态,使用 Event/CriticalSection/Mutex/Semaphore 等?
   全局变量?
   或者相应的 Windows 操作平台提供的特殊通信技术,如 PostMessage 函数/管道?

* 一款 C++ 软件 = C++ 语法 + 操作系统 API 函数调用

#### 1. grep怎么用?请结合具体例子说明,给出一组命令,能够将某命令输出信息中,若某行存在某一单词,则将该行输出到指定文本文件上

* 显示指定头5行
    -m 5

* lsof
    `lsof` 是一个在 Unix 和类 Unix 系统(如 Linux)上用于列出打开的文件的实用程序.以下是一些常见和有用的 `lsof` 参数:

  - `-u`:按照用户或用户组来筛选文件.例如,`lsof -u username` 会列出所有由用户 `username` 打开的文件.
  - `-c`:按照命令名来筛选文件.例如,`lsof -c ssh` 会列出所有由 `ssh` 命令打开的文件.
  - `-p`:按照进程 ID 来筛选文件.例如,`lsof -p 1234` 会列出所有由进程 ID 为 `1234` 的进程打开的文件.
  - `-i`:按照网络连接来筛选文件.例如,`lsof -i TCP` 会列出所有使用 TCP 协议的网络连接.
  - `-d`:按照文件描述符来筛选文件.例如,`lsof -d 2` 会列出所有使用文件描述符 `2` 的文件.
  - `+D`:列出指定目录下被打开的文件.例如,`lsof +D /path/to/directory` 会列出 `/path/to/directory` 目录下所有被打开的文件.

* grep常用的参数
  `grep` 是一个强大的文本搜索工具,它有许多常用的参数来帮助你定制搜索.以下是一些常用的 `grep` 参数:
    - `-i`:忽略大小写.例如,`grep -i "hello" file.txt` 会在 `file.txt` 中搜索 "hello",不区分大小写.
    - `-v`:反向匹配,即列出不匹配指定模式的行.例如,`grep -v "error" file.txt` 会列出 `file.txt` 中不包含 "error" 的行.
    - `-r` 或 `-R`:递归搜索.例如,`grep -r "hello" dir/` 会在 `dir/` 目录及其所有子目录中搜索 "hello".
    - `-l`:只列出包含匹配行的文件名,而不是匹配行本身.例如,`grep -l "hello" file1.txt file2.txt` 会列出包含 "hello" 的文件名.
    - `-n`:显示匹配行的行号.例如,`grep -n "hello" file.txt` 会在 `file.txt` 中搜索 "hello",并显示匹配行的行号.
    - `-e`:允许使用多个模式进行搜索.例如,`grep -e "hello" -e "world" file.txt` 会在 `file.txt` 中搜索 "hello" 或 "world".
    - `-w`:只匹配整个单词,而不是字符串的一部分.例如,`grep -w "log" file.txt` 会匹配 "log" 这个单词,而不会匹配 "blog" 或 "logs".
    - `-c`:计算匹配行的数量.例如,`grep -c "hello" file.txt` 会计算 `file.txt` 中 "hello" 的数量.
    * your_command | grep -e "要搜索的单词" -n -m 1 -B 1 > 输出文件名
    * (your_command | head -n 1; your_command | grep "你的单词") > 输出文件名 

* telnet命令
`telnet` 是一个网络协议和命令行工具,用于在互联网或局域网中的主机之间创建一个基于文本的交互式通信连接.以下是一些常见的 `telnet` 用法:

    1. 连接到远程主机:最基本的 `telnet` 用法是连接到远程主机.你只需要提供主机名(或 IP 地址)和端口号.例如,`telnet example.com 80` 会尝试连接到 `example.com` 的 80 端口.

    2. 检查端口是否开放:你可以使用 `telnet` 来检查远程主机的特定端口是否开放.如果 `telnet` 能够成功连接,那么端口就是开放的.例如,`telnet example.com 22` 会尝试连接到 `example.com` 的 22 端口(通常用于 SSH).

    3. 发送 HTTP 请求:你可以使用 `telnet` 来手动发送 HTTP 请求.首先,连接到 Web 服务器的 80 端口(或 443 端口用于 HTTPS),然后手动输入 HTTP 请求头.例如:

    ```bash
    telnet example.com 80
    GET / HTTP/1.1
    Host: example.com
    ```

    4. 使用 `telnet` 进行邮件传输协议(SMTP)会话:你可以使用 `telnet` 连接到邮件服务器的 25 端口(SMTP 的默认端口),然后手动输入 SMTP 命令来发送电子邮件.

    请注意,`telnet` 不提供任何加密,所有的通信内容都是明文的.因此,对于需要安全通信的场景,应该使用 SSH 或其他加密的协议,而不是 `telnet`.

* 怎么实现?
#### 3.4 COW
* 什么是COW(copy on swap)?有什么用?
* 在什么场景下使用?
* 怎么实现?

#### 3.5 CAS
* 什么是CAS(copy and swap)?有什么用?
  在C++编程中,"copy-and-swap"(CAS)是一种常用的技术,用于实现赋值操作符(operator=).CAS的基本思想是先创建一个副本,然后交换副本和原对象.
* 在什么场景下使用?
  实现赋值操作符:CAS是实现赋值操作符(operator=)的一种常见方法.它可以简化代码,并提供强异常安全性.

  提供强异常安全性:如果你的代码需要在异常发生时保持一致性(即,不会因为异常而处于无效状态),那么CAS可能是一个好的选择.在CAS中,如果复制操作抛出异常,原对象不会被修改.

  避免自我赋值问题:在传统的赋值操作符实现中,你需要检查自我赋值(即,a = a).但是在CAS中,由于赋值操作符接受的是一个副本,所以不需要检查自我赋值.

  然而,CAS并不适用于所有情况.CAS的一个主要缺点是它需要进行复制操作,这可能会导致性能问题.如果你的对象很大,或者复制操作很昂贵,那么你可能需要使用其他方法来实现赋值操作符.

* 什么时候需要用move
  * 对于callback函数来说
  * 对于将对象插入到容器来说
  * 交换两个对象