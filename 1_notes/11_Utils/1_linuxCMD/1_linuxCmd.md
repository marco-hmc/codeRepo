## linuxCmd

### 1. cheat sheat

### 2. basic command

* **基本操作**
  - `cd`
    - 切换当前工作目录。例如，`cd /home/user` 切换到 `/home/user` 目录。  
  - `ls`
    - 列出目录内容。例如，`ls` 列出当前目录的文件和子目录，`ls -l` 列出详细信息。
  - `mv`
    - 移动或重命名文件或目录。例如，`mv oldname.txt newname.txt` 重命名文件，`mv file.txt /path/to/destination/` 移动文件。
  - `cp`
    - 复制文件或目录。例如，`cp source.txt destination.txt` 复制文件，`cp -r /source/directory /destination/directory` 递归复制目录。
  - `mkdir`
    - 创建新目录。例如，`mkdir new_directory` 创建名为 `new_directory` 的目录。
  - `touch`
    - 创建空文件或更新文件的时间戳。例如，`touch newfile.txt` 创建一个名为 `newfile.txt` 的空文件。

* **文件查看**
  - more
  - less
  - cat
  - head
  - tail
  - nl

* **文件列举**
  * lsof
    `lsof` 是一个在 Unix 和类 Unix 系统(如 Linux)上用于列出打开的文件的实用程序.以下是一些常见和有用的 `lsof` 参数:
    - `-u`:按照用户或用户组来筛选文件.例如,`lsof -u username` 会列出所有由用户 `username` 打开的文件.
    - `-c`:按照命令名来筛选文件.例如,`lsof -c ssh` 会列出所有由 `ssh` 命令打开的文件.
    - `-p`:按照进程 ID 来筛选文件.例如,`lsof -p 1234` 会列出所有由进程 ID 为 `1234` 的进程打开的文件.
    - `-i`:按照网络连接来筛选文件.例如,`lsof -i TCP` 会列出所有使用 TCP 协议的网络连接.
    - `-d`:按照文件描述符来筛选文件.例如,`lsof -d 2` 会列出所有使用文件描述符 `2` 的文件.
    - `+D`:列出指定目录下被打开的文件.例如,`lsof +D /path/to/directory` 会列出 `/path/to/directory` 目录下所有被打开的文件.

* **查找文件**
  * find [path] -iname ""
  * find /usr -iname "gdb"

* **文本搜索**
  - egrep

  - grep常用的参数
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


### 3. internet command

#### 3.1 nc

    **nc** 即 netcat 命令,这个工具在排查网络故障时非常有用,功能非常强大,因而被业绩称为网络界的"瑞士军刀",请读者务必掌握.
    **nc** 命令常见的用法是模拟一个服务器程序被其他客户端连接,或者模拟一个客户端连接其他服务器,连接之后就可以进行数据收发.我们来逐一介绍一下:
    * -v: 这是verbose(详细)模式的开关,会显示更多的信息.
    * -l: 这是listen(监听)模式的开关,使得netcat在指定端口监听进来的连接.
    * nc -v -l 127.0.0.1 6000

- **模拟一个服务器程序**

  使用 **-l** 选项(单词 **l**isten 的第一个字母)在某个 ip 地址和端口号上开启一个侦听服务,以便让其他客户端连接.通常为了显示更详细的信息,会带上 **-v** 选项.


  这样就在 **6000** 端口开启了一个侦听服务器,我们可以通过 **127.0.0.1:6000** 去连接上去;如果你的机器可以被外网访问,你可以使用 **0.0.0.0** 这样的侦听地址,示例:

  ```
  [root@iZ238vnojlyZ ~]# nc -v -l 0.0.0.0 6000
  Ncat: Version 6.40 ( http://nmap.org/ncat )
  Ncat: Listening on 0.0.0.0:6000
  ```

- 模拟一个客户端程序

  用 **nc** 命令模拟一个客户端程序时,我们不需要使用 **-l** 选项,直接写上 ip 地址(或域名,**nc** 命令可以自动解析域名)和端口号即可,示例如下:

  ```
  ## 连接百度 web 服务器
  [root@iZ238vnojlyZ ~]# nc -v www.baidu.com 80
  Ncat: Version 6.40 ( http://nmap.org/ncat )
  Ncat: Connected to 115.239.211.112:80.
  ```

  输出提示我们成功连接上百度 Web 服务器.

我们知道客户端连接服务器一般都是操作系统随机分配一个可用的端口号连接到服务器上去,使用 **nc** 命令作为客户端时可以使用 **-p** 选项指定使用哪个端口号连接服务器,例如,我们希望通过本地 5555 端口连接百度的 Web 服务器,可以这么输入:

```
[root@iZ238vnojlyZ ~]# nc -v -p 5555 www.baidu.com 80
Ncat: Version 6.40 ( http://nmap.org/ncat )
Ncat: Connected to 115.239.211.112:80.
```

再开一个 shell 窗口,我们使用上文中介绍的 **lsof** 命令验证一下,是否确实通过 **5555** 端口连接上了百度 Web 服务器.

```
[root@iZ238vnojlyZ ~]# lsof -Pni | grep nc
nc        32610    root    3u  IPv4 113369437      0t0  TCP 120.55.94.78:5555->115.239.211.112:80 (ESTABLISHED)
```

结果确实如我们所期望的.

当然,当使用 **nc** 命令与对端建立连接后,我们可以发送消息.下面通过一个具体的例子来演示一下这个过程

1. 使用 **nc -v -l 0.0.0.0 6000** 模拟一个侦听服务,再新建一个 shell 窗口利用 **nc -v 127.0.0.1 6000** 模拟一个客户端程序连接刚才的服务器.
2. 此时在客户端和服务器就可以相互发消息了.我们可以达到一个简化版的 IM 软件聊天效果:

**客户端效果:**

![](../imgs/nc1.png)

**服务器端效果:**

![](../imgs/nc2.jpeg)


> 果你在使用 nc 命令发消息时不小心输入错误,可以使用 **Ctrl + Backspace** 键删除.

**nc** 命令默认会将 **\n** 作为每条消息的结束标志,如果你指定了 **-C** 选项,将会使用 **\r\n** 作为消息结束标志.

**nc** 命令不仅可以发消息,同时也能发文件.我们也来演示一下:

需要注意的是是**接收文件的一方是服务器端,发送文件的一方是客户端**.

1. 服务器端命令:

   ```
   nc -l ip地址 端口号 > 接收的文件名
   ```

2. 客户端命令:

   ```
   nc ip地址 端口号 < 发送的文件名
   ```

**服务器端效果**:

![img](../imgs/nc3.jpeg)

**客户端效果:**

![img](https://mmbiz.qpic.cn/mmbiz_png/ic8RqseyjxMM4O9PrQeYEZ96kC0aP9fXq02fwwzmOXVibyIyH5Qa4Sc7BMZrOBjibg4wibnWmdFalicBMXpNicR3MOjA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)


> 意:这里客户端发送一个文件叫 **index.html**,服务器端以文件名 **xxx.html** 来保存,也就是说服务器端保存接收的文件名时不一定要使用客户端发送的文件名.

根据上面的介绍,当我们需要调试我们自己的服务器或者客户端程序时,又不想自己开发相应的对端,我们就可以使用 **nc** 命令去模拟.

当然,**nc** 命令非常强大,其功能远非本节介绍的这些,读者如果有兴趣可以去 **nc** 的 man 手册上获取更多的信息.

#### ifstat
#### netstat
#### telnet

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


**tcpdump** 是 Linux 系统提供一个非常强大的抓包工具,熟练使用它,对我们排查网络问题非常有用.如果你的机器上还没有安装,可以使用如下命令安装:

```
yum install tcpdump
```

如果要使用 **tcpdump** 命令必须具有 **sudo** 权限.

**tcpdump** 常用的选项有:

- **-i** 指定要捕获的目标网卡名,网卡名可以使用前面章节中介绍的 **ifconfig** 命令获得;如果要抓所有网卡的上的包,可以使用 **any** 关键字.

  ```
  ## 抓取网卡ens33上的包
  tcpdump -i ens33
  ## 抓取所有网卡上的包
  tcpdump -i any
  ```

- **-X** 以 ASCII 和十六进制的形式输出捕获的数据包内容,减去链路层的包头信息;**-XX** 以 ASCII 和十六进制的形式输出捕获的数据包内容,包括链路层的包头信息.

- **-n** 不要将 ip 地址显示成别名的形式;**-nn** 不要将 ip 地址和端口以别名的形式显示.

- **-S** 以绝对值显示包的 ISN 号(包序列号),默认以上一包的偏移量显示.

- **-vv** 抓包的信息详细地显示;**-vvv** 抓包的信息更详细地显示.

- **-w** 将抓取的包的原始信息(不解析,也不输出)写入文件中,后跟文件名:

  ```
  tcpdump -i any -w filename  
  ```

- **-r** 从利用 **-w** 选项保存的包文件中读取数据包信息.

除了可以使用选项以外,**tcpdump** 还支持各种数据包过滤的表达式,常见的形式如下:

```
## 仅显示经过端口 8888 上的数据包(包括tcp:8888和udp:8888)
tcpdump -i any 'port 8888'

## 仅显示经过端口是 tcp:8888 上的数据包
tcpdump -i any 'tcp port 8888'

## 仅显示从源端口是 tcp:8888 的数据包
tcpdump -i any 'tcp src port 8888'

## 仅显示源端口是 tcp:8888 或目标端口是 udp:9999 的包 
tcpdump -i any 'tcp src port 8888 or udp dst port 9999'

## 仅显示地址是127.0.0.1 且源端口是 tcp:9999 的包 ,以 ASCII 和十六进制显示详细输出,
## 不显示 ip 地址和端口号的别名
tcpdump -i any 'src host 127.0.0.1 and tcp src port 9999' -XX -nn -vv
```

下面我们通过三个具体的操作实例来演示一下使用 **tcpdump** 的抓包过程.

**实例一 :连接一个正常的侦听端口**

假设我的服务器端的地址是 **127.0.0.0.1:12345**,使用 nc 命令在一个 shell 窗口创建一个服务器程序并在这个地址上进行侦听.

```
nc –v -l 127.0.0.0.112345
```

效果如下图所示:

![](../imgs/tcpdump1.webp)

在另外一个 shell 窗口开启 tcpdump 抓包:

```
tcpdump -i any 'port 12345' -XX -nn -vv
```

效果如下:

![](../imgs/tcpdump2.webp)

然后再开一个 shell 窗口,利用 nc 命令创建一个客户端去连接服务器:

```
nc -v 127.0.0.1 12345
```

效果如下:

![](../imgs/tcpdump3.webp)

我们抓到的包如下:

![](../imgs/tcpdump4.webp)

由于我们没有在客户端和服务器之间发送任何消息,其实抓到的包就是 TCP 连接的三次握手数据包,分析如下:

三次握手过程是客户端先给服务器发送一个 **SYN**,然后服务器应答一个 **SYN + ACK**,应答的序列号是递增 **1** 的,表示应答哪个请求,即从 **4004096087** 递增到 **4004096088**,接着客户端再应答一个 **ACK**.这个时候,我们发现发包序列号和应答序列号都变成 **1**了,这是 tcpdump 使用相对序号,我们加上 **-S** 选项后就变成绝对序列号了.

我们按 Ctrl + C 中断 tcpdump 抓包过程,并停止用 nc 开启的客户端和服务器程序,然后在前面的 tcpdump 命令后面加上 **-S** 选项重新开启抓包,使用命令如下:

```
tcpdump -i any 'port 12345' -XX -nn -vv -S
```

然后再按顺序用 nc 命令再次启动下服务器和客户端程序.再次得到抓包结果:

![](../imgs/tcpdump5.webp)

这次得到的包的序号就是绝对序号了.

**实例二:连接一个不存在的侦听端口**

**实例一**演示的是正常的 TCP 连接三次握手过程捕获到的数据包.假如我们连接的**服务器 ip 地址存在**,但**监听端口号不存在**,我们看下 tcpdump 抓包结果.除了在一个 shell 窗口启动一个 tcpdump 抓包监测,在另外一个 shell 窗口用 nc 命令去连接一个不存在的侦听端口即可.

![](../imgs/tcpdump6.webp)

抓包数据如下:

![](../imgs/tcpdump7.webp)

这个时候客户端发送 **SYN**,服务器应答 **ACK+RST**,这个应答包会导致客户端的 connect 连接失败返回.

**实例三:连接一个很遥远的 ip,或者网络繁忙的情形**

实际情形中,还存在一种情况就是客户端访问一个很遥远的 ip,或者网络繁忙,服务器对客户端发送的 TCP 三次握手的网络 SYN 报文没有应答,会出现什么情况呢?

我们通过设置防火墙规则来模拟一下这种情况.使用 **iptables -F** 先将防火墙的已有规则都清理掉,然后给防火墙的 INPUT 链上增加一个规则:丢弃本地网卡 lo(也就是 127.0.0.1 这个回环地址)上的所有 SYN 包.

```
iptables -F
iptables -I INPUT -p tcp --syn -i lo -j DROP
```

![](../imgs/tcpdump8.png)



> 如果读者对 CentOS 的防火墙 iptables 命令有兴趣,可以使用 man iptables 在 man 手册中查看更详细的帮助.

在开启 tcpdump 抓包之后和设置防火墙规则之后,利用 nc 命令去连接 127.0.0.1:12345 这个地址.整个过程操作效果图如下:

![](../imgs/tcpdump9.png)

接着,我们得到 tcpdump 抓到的数据包如下:

![](../imgs/tcpdump10.webp)

通过抓包数据我们可以看到:如果连接不上,一共重试了 **5** 次,重试的时间间隔是 1 秒,2秒,4秒,8秒,16秒,最后返回超时失败.这个重试次数在 **/proc/sys/net/ipv4/tcp_syn_retries** 内核参数中设置,默认为 **6** .

> TCP 四次挥手与三次握手基本上类似,这里就不贴出 tcpdump 抓包的详情了,强烈建议不熟悉这块的读者实际练习一遍.


用简单的话来定义tcpdump,就是:dump the traffic on a network,根据使用者的定义对网络上的数据包进行截获的包分析工具. tcpdump可以将网络中传送的数据包的"头"完全截获下来提供分析.它支持针对网络层/协议/主机/网络或端口的过滤,并提供and/or/not等逻辑语句来帮助你去掉无用的信息.

实用命令实例

将某端口收发的数据包保存到文件<br>
`sudo tcpdump -i any port 端口 -w 文件名.cap`


打印请求到屏幕<br>
`sudo tcpdump -i any port 端口 -Xnlps0`

默认启动<br>
`tcpdump`
普通情况下,直接启动tcpdump将监视第一个网络接口上所有流过的数据包.
监视指定网络接口的数据包<br>
`tcpdump -i eth1`
如果不指定网卡,默认tcpdump只会监视第一个网络接口,一般是eth0,下面的例子都没有指定网络接口.　


* **tcpdump root权限下使用的抓包工具，只能抓取流经本机的数据包**

  ```shell
  tcpdump [-adeflnNOpqStvx][-c<数据包数目>][-dd][-ddd][-F<表达文件>][-i<网络界面>][-r<数据包文件>][-s<数据包大小>][-tt][-T<数据包类型>][-vv][-w<数据包文件>][输出数据栏位]
  -a 尝试将网络和广播地址转换成名称。
  -c <数据包数目> 收到指定的数据包数目后，就停止进行倾倒操作。
  -d 把编译过的数据包编码转换成可阅读的格式，并倾倒到标准输出。
  -dd 把编译过的数据包编码转换成C语言的格式，并倾倒到标准输出。
  -ddd 把编译过的数据包编码转换成十进制数字的格式，并倾倒到标准输出。
  -e 在每列倾倒资料上显示连接层级的文件头。
  -f 用数字显示网际网络地址。
  -F<表达文件> 指定内含表达方式的文件。
  -i<网络界面> 使用指定的网络截面送出数据包。
  -l 使用标准输出列的缓冲区。
  -n 不把主机的网络地址转换成名字。
  -N 不列出域名。
  -O 不将数据包编码最佳化。
  -p 不让网络界面进入混杂模式。
  -q 快速输出，仅列出少数的传输协议信息。
  -r <数据包文件> 从指定的文件读取数据包数据。
  -s<数据包大小> 设置每个数据包的大小。
  -S 用绝对而非相对数值列出TCP关联数。
  -t 在每列倾倒资料上不显示时间戳记。
  -tt 在每列倾倒资料上显示未经格式化的时间戳记。
  -T <数据包类型> 强制将表达方式所指定的数据包转译成设置的数据包类型。
  -v 详细显示指令执行过程。
  -vv 更详细显示指令执行过程。
  -x 用十六进制字码列出数据包资料。
  -w <数据包文件> 把数据包数据写入指定的文件。
  ```

* **netstat 用于显示网络状态**，可以打印本地网卡接口上的全部链接 路由表信息 网卡接口信息等

  ```shell
  -a或--all 显示所有连线中的Socket。
  -A<网络类型>或--<网络类型> 列出该网络类型连线中的相关地址。
  -c或--continuous 持续列出网络状态。
  -C或--cache 显示路由器配置的快取信息。
  -e或--extend 显示网络其他相关信息。
  -F或--fib 显示路由缓存。
  -g或--groups 显示多重广播功能群组组员名单。
  -h或--help 在线帮助。
  -i或--interfaces 显示网络界面信息表单。
  -l或--listening 显示监控中的服务器的Socket。
  -M或--masquerade 显示伪装的网络连线。
  -n或--numeric 直接使用IP地址，而不通过域名服务器。
  -N或--netlink或--symbolic 显示网络硬件外围设备的符号连接名称。
  -o或--timers 显示计时器。
  -p或--programs 显示正在使用Socket的程序识别码和程序名称。
  -r或--route 显示Routing Table。
  -s或--statistics 显示网络工作信息统计表。
  -t或--tcp 显示TCP传输协议的连线状况。
  -u或--udp 显示UDP传输协议的连线状况。
  -v或--verbose 显示指令执行过程。
  -V或--version 显示版本信息。
  -w或--raw 显示RAW传输协议的连线状况。
  -x或--unix 此参数的效果和指定"
  -A unix"参数相同。
  --ip或--inet 此参数的效果和指定"-A inet"参数相同。
  ```

* **ifstat** 简单的网络流量监测工具

  ```shell
  -a 监测系统上的所有网卡接口
  -i 指定要监测的网卡接口
  -t 在每行输出信息前加上时间戳
  ```

* **iptables 对Linux系统中通信的数据包进行一定的检测，达到防火墙的目的**

* iptables 查看端口流量

  * 输入监控

    ```shell
    # 下面示例是监控目标端口是8080的输入流量 --dport(destination port 的缩写)
    iptables -A INPUT -p tcp --dport 8080
    ```

  * 输出监控

    ```shell
    # 下面示例是监控来源端口是8080的输出流量 --sport(source port 的缩写)
    iptables -A OUTPUT -p tcp --sport 8080
    ```

  * **查看统计数据**

    ```
    iptable -L -v -n -x
    
    Chain INPUT (policy ACCEPT 202 packets, 25187 bytes)
      pkts   bytes target   prot opt in   out   source        destination     
       18   2885      tcp -- *   *    0.0.0.0/0      0.0.0.0/0      tcp dpt:8080
    
    Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
      pkts   bytes target   prot opt in   out   source        destination     
    
    Chain OUTPUT (policy ACCEPT 184 packets, 45774 bytes)
      pkts   bytes target   prot opt in   out   source        destination     
       12   8240      tcp -- *   *    0.0.0.0/0      0.0.0.0/0      tcp spt:8080
    
    ```

  * **重置统计数据**

    ```shell
    # 重置所有输入端口
    Iptable -Z INPUT
    # 重置所有输出端口
    Iptable -Z OUTPUT
    ```

  * **移除统计端口**

    ```shell
    # 移除输入端口
    iptables -D INPUT -p tcp --dport 8080
    # 移除输出端口
    iptables -D OUTPUT -p tcp --sport 8080
    ```

* **lsof**查看一个进程打开了哪些文件，文件被哪些进程使用

  ```shell
  -p 18400 （按照进程ID查看）
  -d type (按照FD的类型查看）
  -i 4 (查看进程打开的网络连接，使用IPV4协议）
  -i:80 (查看进程打开的网络连接，端口号为80）
  -i @127.0.0.1 (查看进程打开的网络连接，IP为127.0.0.1）
  lsof file-name：查看文件对应的进程
  ```

### 4. hardware monitor command

mpstat

* **ps**命令用于显示当前进程的状态(cpu利用率， 占用内存，状态，运行时间等)，类似于 windows 的任务管理器

  ```shell
  ps [options] [--help]
  
  -A 列出所有的进程
  -w 显示加宽可以显示较多的资讯
  -au 显示较详细的资讯
  -aux 显示所有包含其他使用者的进程
  -ajx 获得当前所有的进程及父进程和进程组id
  -axjf/-ejH 查看所有进程的层次关系
  -ef 显示所有命令，连带命令行
  ```

  -aux 显示格式`USER PID %CPU %MEM VSZ RSS TTY STAT START TIME COMMAND`

  * USER: 行程拥有者
  * PID: pid
  * %CPU: 占用的 CPU 使用率
  * %MEM: 占用的记忆体使用率
  * VSZ: 占用的虚拟记忆体大小
  * RSS: 占用的记忆体大小
  * TTY: 终端的次要装置号码 (minor device number of tty)
  * STAT: 该行程的状态:
    - D: 无法中断的休眠状态 (通常 IO 的进程)
    - R: 正在执行中
    - S: 静止状态
    - T: 暂停执行
    - Z: 不存在但暂时无法消除（僵尸进程）
    - W: 没有足够的记忆体分页可分配
    - <: 高优先序的行程
    - N: 低优先序的行程
    - L: 有记忆体分页分配并锁在记忆体内 (实时系统或捱A I/O)
  * START: 行程开始时间
  * TIME: 执行的时间
  * COMMAND:所执行的指令

* **vmstat**  可以展现给定时间间隔的服务器的状态值，包括服务器的**CPU使用率，内存使用，虚拟内存交换情况，IO读写情况**

  * 相比top，vmstat可以看到**整个机器**的CPU,内存,IO的使用情况，**而不是**单单看到**各个进程**的CPU使用率和内存使用率

  ```shell
  -a：显示活跃和非活跃内存
  -f：显示从系统启动至今的fork数量 。
  -m：显示slabinfo
  -n：只在开始时显示一次各字段名称。
  -s：显示内存相关统计信息及多种系统活动数量。
  delay：刷新时间间隔。如果不指定，只显示一条结果。
  count：刷新次数。如果不指定刷新次数，但指定了刷新时间间隔，这时刷新次数为无穷。
  -d：显示磁盘相关统计信息。
  -p：显示指定磁盘分区统计信息
  -S：使用指定单位显示。参数有 k 、K 、m 、M ，分别代表1000、1024、1000000、1048576字节（byte）。默认单位为K（1024 bytes）
  -V：显示vmstat版本信息
  ```

* **top** 实时监控系统状态，查看内存，端口 ，io访问量，读写速率

  ```shell
  top [-] [d delay] [q] [c] [S] [s] [i] [n] [b]
  d : 改变显示的更新速度，或是在交谈式指令列( interactive command)按 s
  q : 没有任何延迟的显示速度，如果使用者是有 superuser 的权限，则 top 将会以最高的优先序执行
  c : 切换显示模式，共有两种模式，一是只显示执行档的名称，另一种是显示完整的路径与名称
  S : 累积模式，会将己完成或消失的子行程 ( dead child process ) 的 CPU time 累积起来
  s : 安全模式，将交谈式指令取消, 避免潜在的危机
  i : 不显示任何闲置 (idle) 或无用 (zombie) 的行程
  n : 更新的次数，完成后将会退出 top
  b : 批次档模式，搭配 "n" 参数一起使用，可以用来将 top 的结果输出到档案内
  ```

  * top参数：load average，cpu使用率怎么算
    * 系统负载（System Load）是系统CPU繁忙程度的度量，即有多少进程在等待被CPU调度（**进程等待队列的长度**）
    * load average：1.97,2.14,2.99 来举例：
      - 第一位1.97：表示最近1分钟平均负载
      - 第二位2.14：表示最近5分钟平均负载
      - 第三位2.99：表示最近15分钟平均负载
    * Load < 0.7时：系统很闲，马路上没什么车，要考虑多部署一些服务
    * 0.7 < Load < 1时：系统状态不错，马路可以轻松应对
    * Load == 1时：系统马上要处理不多来了，赶紧找一下原因
    * Load > 1时：马路已经非常繁忙了，进入马路的每辆汽车都要无法很快的运行
    * 通常我们先看15分钟load，如果load很高，再看1分钟和5分钟负载，查看是否有下降趋势
    * 1分钟负载值 > 1，那么我们不用担心，但是如果15分钟负载都超过1，我们要赶紧看看发生了什么事情。所以我们要根据实际情况查看这三个值
    * "load average"一共返回三个平均值：1分钟系统负荷、5分钟系统负荷，15分钟系统负荷；
    * 如果只有1分钟的系统负荷大于1.0，其他两个时间段都小于1.0，这表明只是暂时现象，问题不大
    * 如果15分钟内，平均系统负荷大于1.0（调整CPU核心数之后），表明问题持续存在，不是暂时现象。所以，你应该主要观察"15分钟系统负荷"，将它作为电脑正常运行的指标。
    * 结合具体情况具体分析（单核）：
      - 1分钟Load>1，5分钟Load<1，15分钟Load<1：短期内繁忙，中长期空闲，初步判断是一个“抖动”，或者是“拥塞前兆”
      - 1分钟Load>1，5分钟Load>1，15分钟Load<1：短期内繁忙，中期内紧张，很可能是一个“拥塞的开始”
      - 1分钟Load>1，5分钟Load>1，15分钟Load>1：短、中、长期都繁忙，系统“正在拥塞”
      - 1分钟Load<1，5分钟Load>1，15分钟Load>1：短期内空闲，中、长期繁忙，不用紧张，系统“拥塞正在好转”

* **mpstat** 实时监测多处理器系统上的**每个CPU的使用情况**

* **iostat** 主要用于输出磁盘IO 和 CPU的统计信息

  ```shell
  iostat [选项] [<时间间隔>] [<次数>]
  -c： 显示CPU使用情况
  -d： 显示磁盘使用情况
  -N： 显示磁盘阵列(LVM) 信息
  -n： 显示NFS 使用情况
  -k： 以 KB 为单位显示
  -m： 以 M 为单位显示
  -t： 报告每秒向终端读取和写入的字符数和CPU的信息
  -V： 显示版本信息
  -x： 显示详细信息
  -p：[磁盘] 显示磁盘和分区的情况
  ```

* **free命令用于显示内存状态**，显示内存的使用情况，包括实体内存，虚拟的交换文件内存，共享内存区段，以及系统核心使用的缓冲区等

  ```shell
  free [-bkmotV][-s <间隔秒数>]
  -b 　以Byte为单位显示内存使用情况。
  -k 　以KB为单位显示内存使用情况。
  -m 　以MB为单位显示内存使用情况。
  -h 　以合适的单位显示内存使用情况，最大为三位数，自动计算对应的单位值。单位有B = bytes
       K = kilos
       M = megas
       G = gigas
       T = teras
  -o 　不显示缓冲区调节列。
  -s<间隔秒数> 　持续观察内存使用状况。
  -t 　显示内存总和列。
  -V 　显示版本信息。
  ```


### 5. os info monitor

* jobs

查看当前控制台的后台进程

想要停止后台进程,使用jobs命令查看其进程号(比如为num),然后kill %num即可

* ps

查看后台进程

* top

查看所有进程和资源使用情况,类似Windows中的任务管理器

停止进程:界面是交互式的,在窗口输入k 之后输入PID,会提示输入停止进程模式 有SIGTERM和 SIGKILL 如果留空不输入,就是SIGTERM(优雅停止)

退出top:输入q即可


strace

* **ipcs**：用于报告Linux中进程间通信设施的状态

  ```shell
  ipcs [resource ...] [output-format]ipcs [resource] -i 
  <id>选项：
  -i, --id <id>  打印由 id 标识的资源的详细信息
  -h, --help     显示此帮助并退出
  -V, --version  输出版本信息并退出
  资源选项:
  -m, --shmems      共享内存段
  -q, --queues      消息队列
  -s, --semaphores  信号量
  -a, --all         全部(默认)
  输出格式：
  -t, --time        显示附加、脱离和更改时间
  -p, --pid         显示 PID 的创建者和最后操作
  -c, --creator     显示创建者和拥有者
  -l, --limits      显示资源限制
  -u, --summary     显示状态摘要    
  --human       以易读格式显示大小
  -b, --bytes       以字节数显示大小
  ```

* **ipcrm**：删除一个或更多的消息队列、信号量集或者共享内存标识，同时会将与ipc对象相关链的数据也一起移除

  ```shell
  ipcrm [options]ipcrm <shm|msg|sem> <id> [...]
  -m, --shmem-id <id>        按 id 号移除共享内存段
  -M, --shmem-key <键>       按键值移除共享内存段
  -q, --queue-id <id>        按 id 号移除消息队列
  -Q, --queue-key <键>       按键值移除消息队列
  -s, --semaphore-id <id>    按 id 号移除信号量
  -S, --semaphore-key <键>  按键值移除信号量
  -a, --all[=<shm|msg|sem>]  全部移除
  -v, --verbose              解释正在进行的操作
  -h, --help     显示此帮助并退出
  -V, --version  输出版本信息并退出
  ```

* [**ulimit**](https://blog.csdn.net/FreeApe/article/details/101058393) 

  * shell内建指令，可用来控制shell执行程序的资源

  * 设置项仅在当前shell作用(类似`export`命令，永久生效可以写入相关配置文件)

  * 写入`~/.profile或~/.bashrc`**只对当前用户持久性生效**

  * 写入`/etc/security/limits.conf`可针对性配置，**系统级持久性生效**

    ```shell
    ulimit [-aHS][-c <core文件上限>][-d <数据节区大小>][-f <文件大小>][-m <内存大小>][-n <文件数目>][-p <缓冲区大小>][-s <堆叠大小>][-t <CPU时间>][-u <程序数目>][-v <虚拟内存大小>]
    
    -a 　显示目前资源限制的设定。
    -c <core文件上限> 　设定core文件的最大值，单位为区块。
    -d <数据节区大小> 　程序数据节区的最大值，单位为KB。
    -f <文件大小> 　shell所能建立的最大文件，单位为区块。
    -H 　设定资源的硬性限制，也就是管理员所设下的限制。
    -m <内存大小> 　指定可使用内存的上限，单位为KB。
    -n <文件数目> 　指定同一时间最多可开启的文件数。
    -p <缓冲区大小> 　指定管道缓冲区的大小，单位512字节。
    -s <进程栈大小> 　指定进程栈的上限，单位为KB。
    -S 　设定资源的弹性限制。
    -t <CPU时间> 　指定CPU使用时间的上限，单位为秒。
    -u <程序数目> 　用户最多可开启的程序数目。
    -v <虚拟内存大小> 　指定可使用的虚拟内存上限，单位为KB。
    ```

* linux的fd数量限制查询

  * 所有进程允许打开的最大fd数量

  ```shell
  cat /proc/sys/fs/file-max   // 9223372036854775807
  ```

  * 所有进程已经打开的fd数量及允许的最大数量

  ```shell
  cat /proc/sys/fs/file-nr
  ```

  * 单个进程允许打开的最大fd数量

  ```shell
  ulimit -n
  ```

  * 单个进程（例如进程id为5454）已经打开的fd

  ```shell
  ls -l /proc/5454/fd/lsof -p 5454
  ```

* 进程/线程绑定cpu

* 意义
  * 一是现代服务器大多采用NUMA多处理器架构，一台服务器会安装多颗处理器（称为NUMA节点），而NUMA架构各节点资源较为独立的设计，决定了在不同NUMA节点共享数据的成本高昂，因此尽量将数据交互较为频繁的程序绑定在同一NUMA节点上是很重要的
  * 二是进程/线程**如果从一个核心切换至另一个核心上运行，需要面临上下文切换、缓存失效等问题，成本也很高**。在对性能要求较高的软件中，这已经是造成时延抖动的一大来源之一

* 进程/线程绑定

  * 在Linux系统下，进程都有一个CPU亲和力属性（affinity），通过以下命令可以查询

    ```bash
    # 查看cpu信息
    cat /proc/cpuinfo | grep processor
    processor	: 0
    # 查看某个进程可以运行的cpu
    taskset -pc 26419 
    pid 26419's current affinity list: 0
    ```

    以上查询结果的含义是，进程id为26419的进程，可以在0号CPU上运行，默认情况下，进程是可以在任意一个核心上运行的

  * 绑定cpu

    ```
    taskset -pc 0,1,2... pid	# 表示将pid进程绑定到0，1，2...号cpu执行
    ```

  * taskset命令依然适用于线程

  * 不能通过taskset+程序名直接启动程序并实现各个线程**绑定不同核心**了，该命令只能支持到进程级别，也就是说它会把进程下的所有线程都设置为相同的亲和度

  * 如果需要将同一进程中线程绑定到不同cpu，需要手动taskset tid：可以编写脚本启动并获取线程id，再多次调用taskset，指定线程id，将其绑定到不同核心上即可

* 编程绑定

  * sched_getaffinity、sched_setaffinity
  * pthread_setaffinity_np


### 6. advanced cmd
#### 3.1 crontab命令
详见:https://www.cnblogs.com/peida/archive/2013/01/08/2850483.html

corntab命令是用来指定用户计划任务的.用户将需要定时执行的任务写入crontab文件中,提交给crond进程定期执行.

* crontab命令用来对crontab文件进行管理
```
1．命令格式:
crontab [-u user] file
crontab [-u user] [ -e | -l | -r ]
2．命令功能:
通过crontab 命令,我们可以在固定的间隔时间执行指定的系统指令或 shell script脚本.时间间隔的单位可以是分钟/小时/日/月/周及以上的任意组合.这个命令非常设合周期性的日志分析或数据备份等工作.
3．命令参数:
-u user:用来设定某个用户的crontab服务,例如,"-u ixdba"表示设定ixdba用户的crontab服务,此参数一般有root用户来运行.
file:file是命令文件的名字,表示将file做为crontab的任务列表文件并载入crontab.如果在命令行中没有指定这个文件,crontab命令将接受标准输入(键盘)上键入的命令,并将它们载入crontab.
-e:编辑某个用户的crontab文件内容.如果不指定用户,则表示编辑当前用户的crontab文件.
-l:显示某个用户的crontab文件内容,如果不指定用户,则表示显示当前用户的crontab文件内容.
-r:从/var/spool/cron目录中删除某个用户的crontab文件,如果不指定用户,则默认删除当前用户的crontab文件.
-i:在删除用户的crontab文件时给确认提示.
```

* crontab文件内容

crond是Linux下的周期性执行系统任务的守护进程,他会根据/etc下的crontab配置文件的内容执行.用户需要将计划任务写入crontab文件中才能执行.

用户所建立的crontab文件中,每一行都代表一项任务,每行的每个字段代表一项设置,它的格式共分为六个字段,前五段是时间设定段,第六段是要执行的命令段,格式如下:
```
minute   hour   day   month   week   command

其中:
minute: 表示分钟,可以是从0到59之间的任何整数.
hour:表示小时,可以是从0到23之间的任何整数.
day:表示日期,可以是从1到31之间的任何整数.
month:表示月份,可以是从1到12之间的任何整数.
week:表示星期几,可以是从0到7之间的任何整数,这里的0或7代表星期日.
command:要执行的命令,可以是系统命令,也可以是自己编写的脚本文件.
在以上各个字段中,还可以使用以下特殊字符:
星号(*):代表所有可能的值,例如month字段如果是星号,则表示在满足其它字段的制约条件后每月都执行该命令操作.
逗号(,):可以用逗号隔开的值指定一个列表范围,例如,"1,2,5,7,8,9"
中杠(-):可以用整数之间的中杠表示一个整数范围,例如"2-6"表示"2,3,4,5,6"
正斜线(/):可以用正斜线指定时间的间隔频率,例如"0-23/2"表示每两小时执行一次.同时正斜线可以和星号一起使用,例如*/10,如果用在minute字段,表示每十分钟执行一次.
```

### 98. toBeAdjust

#### ar, nm, ldd, readelf, objdump

* ar：建立或修改备存文件，或是从备存文件中抽取文件

  ```shell
  ar[-dmpqrtx][cfosSuvV][a<成员文件>][b<成员文件>][i<成员文件>][备存文件][成员文件]
  必要参数：
  -d 　删除备存文件中的成员文件。
  -m 　变更成员文件在备存文件中的次序。
  -p 　显示备存文件中的成员文件内容。
  -q 　将文件附加在备存文件末端。
  -r 　将文件插入备存文件中。
  -t 　显示备存文件中所包含的文件。  # 常用
  -x 　自备存文件中取出成员文件。
  选项参数：
  a <成员文件> 　将文件插入备存文件中指定的成员文件之后。
  b <成员文件> 　将文件插入备存文件中指定的成员文件之前。
  c 　建立备存文件。
  f 　为避免过长的文件名不兼容于其他系统的ar指令指令，因此可利用此参数，截掉要放入备存文件中过长的成员文件名称。
  i <成员文件> 　将文件插入备存文件中指定的成员文件之前。
  o 　保留备存文件中文件的日期。
  s 　若备存文件中包含了对象模式，可利用此参数建立备存文件的符号表。
  S 　不产生符号表。
  u 　只将日期较新文件插入备存文件中。
  v 　程序执行时显示详细的信息。
  V 　显示版本信息。
  ```

* nm：nm用来列出目标文件的**符号表清单**

* ldd

  * 首先ldd不是一个可执行程序，而只是一个shell脚本
  * ldd能够显示**可执行模块的dependency**，其原理是通过设置一系列的环境变量，如下：LD_TRACE_LOADED_OBJECTS、LD_WARN、LD_BIND_NOW、LD_LIBRARY_VERSION、LD_VERBOSE等
  * ldd显示**可执行模块**的dependency的工作原理，其实质是通过ld-linux.so（elf动态库的装载器）来实现

* **readelf**：一般用于查看**ELF格式的文件信息**，常见的文件如在Linux上的**可执行文件**，**动态库(*.so)或者静态库(*.a) 等包含ELF格式**的文件

  * **系统里的目标文件是按照特定的目标文件格式来组织的，各个系统的目标文件格式都不相同**

  * ELF(Executable and Linking Format)**可执行可链接格式**是一种对象文件的格式，**用于定义不同类型的对象文件(Object files)中都放了什么东西、以及都以什么样的格式去放这些东西**。它自最早在 System V 系统上出现后，被 xNIX 世界所广泛接受，作为缺省的二进制文件格式来使用。可以说，ELF是构成众多xNIX系统的基础之一

    * ELF文件有三种类型：
      * **可重定位的对象文件**(Relocatable file) 由汇编器汇编生成的 .o 文件	
      * **可执行的对象文件**(Executable file) 可执行应用程序
      * **可被共享的对象文件**(Shared object file) 动态库文件，也即 .so 文件

    * 在Unix下使用**readelf命令来显示可执行程序的信息，功能与objdump相似，但是显示的更加具体**

  * ELF格式的文件在Linux系统下有.axf、 .bin、 .elf、 .o、 .prx、 .puff、 .ko、 .mod和.so等等

* objdump是用来**显示目标文件相关信息**的



### 99. quiz
#### 1. 查看某个服务是否启动

* 方法一：查看redis服务进程情况，这里拿redis服务举例,其他服务查询更改名字即可

  ```
  ps -ef|grep redis
  ```

* 方法二：查看6379（为redis的端口号）端口号是否被占用

  ```
  lsof -i :6379
  ```

* 方法三：显示tcp的端口和进程等相关情况

  ```
  netstat -tnlp
  ```

https://linuxtools-rst.readthedocs.io/zh-cn/latest/index.html