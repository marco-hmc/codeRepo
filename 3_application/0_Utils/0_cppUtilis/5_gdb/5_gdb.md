## gdb

#### 1. 启动调试命令
前置条件:编译生成执行码时带上 -g,如果使用Makefile,通过给CFLAGS指定-g选项,否则调试时没有符号信息.
gdb program //最常用的用gdb启动程序,开始调试的方式
gdb program core //用gdb查看core dump文件,跟踪程序core的原因
gdb program pid //用gdb调试已经开始运行的程序,指定pid即可
gdb attach pid //用gdb调试已经开始运行的程序,指定pid即可

#### 2.调试命令
##### 2.1 执行命令模式
-batch选项.
比如:打印$pid进程所有线程的堆栈并退出.
gdb -ex "set pagination 0" -ex "thread apply all bt" -batch -p $pid

###### 2.2 交互模式
run             //运行程序
continue        //中断后继续运行到下一个断点
step            //单步执行,进入函数
next            //单步执行
return          //函数未执行完,忽略未执行的语句,返回.
finish          //函数执行完毕返回.
call            //调用某一个函数 fun("1234")
(backtrace)bt   //显示栈桢
bt N            //显示开头N个栈桢
bt -N           //显示最后N个栈桢
(frame)f N      //显示第N层栈桢
list            //显示源码
set directory   //设置gdb的工作目录
pwd             //当前的工作目录

##### 2.3 反复执行
continue N    //连续执行cointiue N次,一般用于避免频繁断点
step N
next N

#### 3. 断点
break 函数名                         //设置断在某个函数
break 文件名:行号                    //设置断在某一行
info break                          //查看设置的断点信息
break if condition                  //条件断点
break 函数名 thread 线程号           //设置断点只断某个线程,通过info threads 查看线程号
delete 断点号 断点号...              //删除一个或多个断点
disable 断点号 断点号...             //禁止一个或多个断点
enable 断点号 断点号...              //打开一个或多个断点
command 断点号                      //断点触发时,执行命令,一般用于打印变量
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>print x
>end
(gdb)

#### 4.检测点
watch               //为表达式(变量)expr设置一个观察点.一量表达式值有变化时,马上停住程序.
rwatch              //当表达式(变量)expr被读时,停住程序.
awatch              //当表达式(变量)的值被读或被写时,停住程序.
info watchpoints    //列出当前所设置了的所有观察点.

经验:观察某个变量是否变化,被读或者被写,由于变量只在某一个作用域,可以获取变量的地址,然后观察.
比如:观察examined_rows变量什么时候被修改
(1).p &examined_rows,得到地址
(2).watch *(ha_rows *) 0x7ffec8005e28,则可以观察这个变量的变化情况.

#### 5.查看变量
(1)设置
set print elements N //指定打印的长度,对长字符串特别有用.
set print element 0 //输出完整的字符串
set print pretty //设置GDB打印结构的时候,每行一个成员,并且有相应的缩进,缺省是关闭的
print {type} variable
比如:
(gdb) p {ABC} 0x7fffffffe710
$2 = {val = 1.5, val2 = 10}

print xxx //打印变量
p /x xxx //16进制显示
p str@str_len //打印字符串

info locals //打印出当前函数中所有局部变量及其值.
info args //打印出当前函数的参数名及其值.
display 变量 //自动打印变量
undisplay //取消自动打印
注意:默认编译的时候,调试过程是看不见宏的值的,编译时候需要给选项.-g3

#### 6.内存查看
格式: x /nfu <addr> x 是 examine 的缩写
a.n表示要显示的内存单元的个数
b.f表示显示方式, 可取如下值
(1).x 按十六进制格式显示变量.
(2).d 按十进制格式显示变量.
(3).u 按十进制格式显示无符号整型.
(4).o 按八进制格式显示变量.
(5).t 按二进制格式显示变量.
(6).a 按十六进制格式显示变量.
(7).i 指令地址格式
(8).c 按字符格式显示变量.
(9).f 按浮点数格式显示变量.
c.u表示一个地址单元的长度
(1).b表示单字节,
(2).h表示双字节,
(3).w表示四字节,
(4).g表示八字节

比如:x/3xh buf
表示从内存地址buf读取内容,3表示三个单位,x表示按十六进制显示,h表示以双字节为一个单位.

#### 7.多线程调试
info threads //查看线程
thread thread_no //切换到线程号
thread apply all command //所有线程都执行命令打印栈桢
比如:thread apply all bt //所有线程都打印栈桢

(1)线程锁
show scheduler-locking
set scheduler-locking on
set scheduler-locking off
默认是off,当程序继续运行的时候如果有断点,那么就把所有的线程都停下来,直到你指定某个线程继续执行(thread thread_no apply continue).
但是如果直接在当前线程执行continue的话,默认是会启动所有线程.这种模式有一种副作用,如果多个线程都断在同一个函数,这时候调试会出问题.
这个时候需要打开线程锁,但打开线程锁,意味着其它线程不能运行了.

(2)non-stop模式(7.0以后的版本支持)
set target-async 1
set pagination off
set non-stop on
gdb启动了不停模式,除了断点有关的线程会被停下来,其他线程会执行.

8.信号量
(1).singal 发送信号
假定你的程序已将一个专用的 SIGINT(键盘输入,或CTRL-C;信号2)信号处理程序设置成采取某个清理动作,
要想测试该信号处理程序,你可以设置一个断点并使用如下命令:
(gdb) signal 2
(2).handle 拦截信号
Handle命令可控制信号的处理,他有两个参数,一个是信号名,另一个是接受到信号时该作什么.几种可能的参数是:
* nostop 接收到信号时,不要将它发送给程序,也不要停止程序.
* stop 接受到信号时停止程序的执行,从而允许程序调试;显示一条表示已接受到信号的消息(禁止使用消息除外)
* print 接受到信号时显示一条消息
* noprint 接受到信号时不要显示消息(而且隐含着不停止程序运行)
* pass 将信号发送给程序,从而允许你的程序去处理它/停止运行或采取别的动作.
* nopass 停止程序运行,但不要将信号发送给程序.
比如:
handle SIGPIPE stop print //截获SIGPIPE信号,程序停止并打印信息
handle SIGUSR1 nostop noprint //忽略SIGUSR1信号

9.生成环境使用GDB场景
内核转储(coredump)
(1).配置产生core文件
前置条件:确保系统配置的core file size足够,一般设置成unlimited
ulimit -c unlimited

配置corefile的参数:
echo 2 > /proc/sys/fs/suid_dumpable [程序中切换用户,也要产生corefile]
mkdir /tmp/corefiles
chmod 777 /tmp/corefiles
echo "/tmp/corefiles/core">/proc/sys/kernel/core_pattern //配置core文件产生的目录为/tmp/corefiles
echo "1" > /proc/sys/kernel/core_uses_pid

注意:
a.确保配置的目录有足够的磁盘空间,否则产生core文件可能不完整.
b.对于MySQLd而言,要保证正确产生core-file,需要加上--core-file,默认这个参数是不打开的.
c.kill -9 pid 是不能产生core文件的,因为SIGKILL信号不能被捕获.

(2).使用core文件
gdb /usr/mysql/bin/mysqld core.24556

(3).dump已经运行进程的状态信息
gdb attach pid
(gdb) generate-core-file
调试完毕后,通过detach命令退出.
另外,通过gcore pid 命令也可以dump core文件,生成在当前目录下.

(4).打印线程信息
pstack pid
pt-pmp -p pid
pstack和pt-pmp都可以打印线程的信息,但是pt-pmp会对同类堆栈的线程做聚合汇总,相对于pstack功能更强大,显示也更友好.

(5).altert日志
这里主要针对mysqld问题排查,mysqld异常crash后,有时候在alter日志中可以看到最后crash线程的堆栈,但是一般只有函数名或一串二进制地址,无法定位到具体是crash到哪一行,通过addr2line可以解这个问题.
比如:alter日志中记录crash时的地址是0x64bd60,通过如下命令,可以定位到具体是哪一行
addr2line -e /usr/mysql/bin/mysqld 0x64bd60
/home/admin/131_20160715135613566_11155487_code/rpm_workspace/sql/sql_parse.cc:3067


### ref

参考文档
https://www.percona.com/blog/2011/08/26/getting-mysql-core-file-on-linux/

GDB调试程序用法 http://www.linuxidc.com/Linux/2013-06/86044.htm

GDB+GDBserver无源码调试Android 动态链接库的技巧 http://www.linuxidc.com/Linux/2013-06/85936.htm

使用hello-gl2建立ndk-GDB环境(有源码和无源码调试环境) http://www.linuxidc.com/Linux/2013-06/85935.htm

在Ubuntu上用GDB调试printf源码 http://www.linuxidc.com/Linux/2013-03/80346.htm

Linux下用GDB调试可加载模块 http://www.linuxidc.com/Linux/2013-01/77969.htm

Ubuntu下使用GDB断点Go程序 http://www.linuxidc.com/Linux/2012-06/62941.htm

使用GDB命令行调试器调试C/C++程序 http://www.linuxidc.com/Linux/2014-11/109845.htm

GDB 的详细介绍:请点这里
GDB 的下载地址:请点这里

## gdb

* 多线程调试中会有coredump的情况,如何定位错误?
* 警告错误位置和实际错误位置为什么会不一致,举例说明?
* 谈谈你对buffer overflow的理解?
* 
#### 1. 启动调试命令
前置条件:编译生成执行码时带上 -g,如果使用Makefile,通过给CFLAGS指定-g选项,否则调试时没有符号信息.
gdb program //最常用的用gdb启动程序,开始调试的方式
gdb program core //用gdb查看core dump文件,跟踪程序core的原因
gdb program pid //用gdb调试已经开始运行的程序,指定pid即可
gdb attach pid //用gdb调试已经开始运行的程序,指定pid即可

#### 2.调试命令
##### 2.1 执行命令模式
-batch选项.
比如:打印$pid进程所有线程的堆栈并退出.
gdb -ex "set pagination 0" -ex "thread apply all bt" -batch -p $pid

###### 2.2 交互模式
run             //运行程序
continue        //中断后继续运行到下一个断点
step            //单步执行,进入函数
next            //单步执行
return          //函数未执行完,忽略未执行的语句,返回.
finish          //函数执行完毕返回.
call            //调用某一个函数 fun("1234")
(backtrace)bt   //显示栈桢
bt N            //显示开头N个栈桢
bt -N           //显示最后N个栈桢
(frame)f N      //显示第N层栈桢
list            //显示源码
set directory   //设置gdb的工作目录
pwd             //当前的工作目录

##### 2.3 反复执行
continue N    //连续执行cointiue N次,一般用于避免频繁断点
step N
next N

#### 3. 断点
break 函数名                         //设置断在某个函数
break 文件名:行号                    //设置断在某一行
info break                          //查看设置的断点信息
break if condition                  //条件断点
break 函数名 thread 线程号           //设置断点只断某个线程,通过info threads 查看线程号
delete 断点号 断点号...              //删除一个或多个断点
disable 断点号 断点号...             //禁止一个或多个断点
enable 断点号 断点号...              //打开一个或多个断点
command 断点号                      //断点触发时,执行命令,一般用于打印变量
(gdb) command 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>print x
>end
(gdb)

#### 4.检测点
watch               //为表达式(变量)expr设置一个观察点.一量表达式值有变化时,马上停住程序.
rwatch              //当表达式(变量)expr被读时,停住程序.
awatch              //当表达式(变量)的值被读或被写时,停住程序.
info watchpoints    //列出当前所设置了的所有观察点.

经验:观察某个变量是否变化,被读或者被写,由于变量只在某一个作用域,可以获取变量的地址,然后观察.
比如:观察examined_rows变量什么时候被修改
(1).p &examined_rows,得到地址
(2).watch *(ha_rows *) 0x7ffec8005e28,则可以观察这个变量的变化情况.

#### 5.查看变量
(1)设置
set print elements N //指定打印的长度,对长字符串特别有用.
set print element 0 //输出完整的字符串
set print pretty //设置GDB打印结构的时候,每行一个成员,并且有相应的缩进,缺省是关闭的
print {type} variable
比如:
(gdb) p {ABC} 0x7fffffffe710
$2 = {val = 1.5, val2 = 10}

print xxx //打印变量
p /x xxx //16进制显示
p str@str_len //打印字符串

info locals //打印出当前函数中所有局部变量及其值.
info args //打印出当前函数的参数名及其值.
display 变量 //自动打印变量
undisplay //取消自动打印
注意:默认编译的时候,调试过程是看不见宏的值的,编译时候需要给选项.-g3

#### 6.内存查看
格式: x /nfu <addr> x 是 examine 的缩写
a.n表示要显示的内存单元的个数
b.f表示显示方式, 可取如下值
(1).x 按十六进制格式显示变量.
(2).d 按十进制格式显示变量.
(3).u 按十进制格式显示无符号整型.
(4).o 按八进制格式显示变量.
(5).t 按二进制格式显示变量.
(6).a 按十六进制格式显示变量.
(7).i 指令地址格式
(8).c 按字符格式显示变量.
(9).f 按浮点数格式显示变量.
c.u表示一个地址单元的长度
(1).b表示单字节,
(2).h表示双字节,
(3).w表示四字节,
(4).g表示八字节

比如:x/3xh buf
表示从内存地址buf读取内容,3表示三个单位,x表示按十六进制显示,h表示以双字节为一个单位.

#### 7.多线程调试
info threads //查看线程
thread thread_no //切换到线程号
thread apply all command //所有线程都执行命令打印栈桢
比如:thread apply all bt //所有线程都打印栈桢

(1)线程锁
show scheduler-locking
set scheduler-locking on
set scheduler-locking off
默认是off,当程序继续运行的时候如果有断点,那么就把所有的线程都停下来,直到你指定某个线程继续执行(thread thread_no apply continue).
但是如果直接在当前线程执行continue的话,默认是会启动所有线程.这种模式有一种副作用,如果多个线程都断在同一个函数,这时候调试会出问题.
这个时候需要打开线程锁,但打开线程锁,意味着其它线程不能运行了.

(2)non-stop模式(7.0以后的版本支持)
set target-async 1
set pagination off
set non-stop on
gdb启动了不停模式,除了断点有关的线程会被停下来,其他线程会执行.

8.信号量
(1).singal 发送信号
假定你的程序已将一个专用的 SIGINT(键盘输入,或CTRL-C;信号2)信号处理程序设置成采取某个清理动作,
要想测试该信号处理程序,你可以设置一个断点并使用如下命令:
(gdb) signal 2
(2).handle 拦截信号
Handle命令可控制信号的处理,他有两个参数,一个是信号名,另一个是接受到信号时该作什么.几种可能的参数是:
* nostop 接收到信号时,不要将它发送给程序,也不要停止程序.
* stop 接受到信号时停止程序的执行,从而允许程序调试;显示一条表示已接受到信号的消息(禁止使用消息除外)
* print 接受到信号时显示一条消息
* noprint 接受到信号时不要显示消息(而且隐含着不停止程序运行)
* pass 将信号发送给程序,从而允许你的程序去处理它/停止运行或采取别的动作.
* nopass 停止程序运行,但不要将信号发送给程序.
比如:
handle SIGPIPE stop print //截获SIGPIPE信号,程序停止并打印信息
handle SIGUSR1 nostop noprint //忽略SIGUSR1信号

9.生成环境使用GDB场景
内核转储(coredump)
(1).配置产生core文件
前置条件:确保系统配置的core file size足够,一般设置成unlimited
ulimit -c unlimited

配置corefile的参数:
echo 2 > /proc/sys/fs/suid_dumpable [程序中切换用户,也要产生corefile]
mkdir /tmp/corefiles
chmod 777 /tmp/corefiles
echo "/tmp/corefiles/core">/proc/sys/kernel/core_pattern //配置core文件产生的目录为/tmp/corefiles
echo "1" > /proc/sys/kernel/core_uses_pid

注意:
a.确保配置的目录有足够的磁盘空间,否则产生core文件可能不完整.
b.对于MySQLd而言,要保证正确产生core-file,需要加上--core-file,默认这个参数是不打开的.
c.kill -9 pid 是不能产生core文件的,因为SIGKILL信号不能被捕获.

(2).使用core文件
gdb /usr/mysql/bin/mysqld core.24556

(3).dump已经运行进程的状态信息
gdb attach pid
(gdb) generate-core-file
调试完毕后,通过detach命令退出.
另外,通过gcore pid 命令也可以dump core文件,生成在当前目录下.

(4).打印线程信息
pstack pid
pt-pmp -p pid
pstack和pt-pmp都可以打印线程的信息,但是pt-pmp会对同类堆栈的线程做聚合汇总,相对于pstack功能更强大,显示也更友好.

(5).altert日志
这里主要针对mysqld问题排查,mysqld异常crash后,有时候在alter日志中可以看到最后crash线程的堆栈,但是一般只有函数名或一串二进制地址,无法定位到具体是crash到哪一行,通过addr2line可以解这个问题.
比如:alter日志中记录crash时的地址是0x64bd60,通过如下命令,可以定位到具体是哪一行
addr2line -e /usr/mysql/bin/mysqld 0x64bd60
/home/admin/131_20160715135613566_11155487_code/rpm_workspace/sql/sql_parse.cc:3067


### ref

参考文档
https://www.percona.com/blog/2011/08/26/getting-mysql-core-file-on-linux/

GDB调试程序用法 http://www.linuxidc.com/Linux/2013-06/86044.htm

GDB+GDBserver无源码调试Android 动态链接库的技巧 http://www.linuxidc.com/Linux/2013-06/85936.htm

使用hello-gl2建立ndk-GDB环境(有源码和无源码调试环境) http://www.linuxidc.com/Linux/2013-06/85935.htm

在Ubuntu上用GDB调试printf源码 http://www.linuxidc.com/Linux/2013-03/80346.htm

Linux下用GDB调试可加载模块 http://www.linuxidc.com/Linux/2013-01/77969.htm

Ubuntu下使用GDB断点Go程序 http://www.linuxidc.com/Linux/2012-06/62941.htm

使用GDB命令行调试器调试C/C++程序 http://www.linuxidc.com/Linux/2014-11/109845.htm

https://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html

https://www.cs.toronto.edu/~krueger/csc209h/tut/gdb_tutorial.html

#### **gdb**

[gdb-tutorial-1](http://www.cs.toronto.edu/~krueger/csc209h/tut/gdb_tutorial.html)

[gdb-tutorial-2](https://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html)


### gdb调试

#### 基本命令

* [详见1](https://blog.csdn.net/qq_26399665/article/details/81165684)
* [详见2](https://blog.csdn.net/weixin_45596153/article/details/101453983)

#### gdb调试多线程

```c++
info threads //显示当前可调式的所有线程 
thread ID //切换当前调试的线程为指定ID的线程
thread apply all command //所以的线程都执行command命令
thread apply ID1,ID2.... command //指定线程执行command命令
set scheduler-locking off|on|step： 	// 在使用step或continue命令调试当前被调试线程的时候，其他线程也是同时执行的，如果我们只想要被调试的线程执行，而其他线程停止等待，那就要锁定要调试的线程，只让它运行。 	
    //off:不锁定任何线程，所有线程都执行。     
    //on:只有当前被调试的线程会执行。 　　 
    //step:阻止其他线程在当前线程单步调试的时候抢占当前线程。只有当next、continue、util以及finish的时候，其他线程才会获得重新运行的show scheduler-locking： 查看当前锁定线程的模式i threads 实现线程间切换
```

#### gdb调试多进程

```c++
// 设置方法
set follow-fork-mode [parent][child] 
set detach-on-fork [on|off]  
// 查看上述两个属性的值
show follow-fork-mode //查看系统默认的模式
show detach-on-fork
/* 
	parent                   on               只调试主进程（GDB默认）
	child                    on               只调试子进程
	parent                   off              同时调试两个进程，gdb跟主进程，子进程block在fork位置
	child                    off              同时调试两个进程，gdb跟子进程，主进程block在fork位置
*/

// 查询正在调试的进程
info inferiors  //查询正在调试的进程
inferior 进程编号 // 切换调试的进程
add-inferior [-copies n] [-exec executable] //添加新的调试进程
detach inferior [进程编号] //释放掉 
kill inferior [进程编号] 
remove-inferior [进程编号] //删除该进程
set schedule-multiple 
set print interior-events on/off
```

#### Core dump(核心转储)概念及调试方法

* 程序由于各种异常或者bug导致在运行过程中异常退出或者中止，并且在满足一定条件下会产生一个叫core的文件，通常情况下，core文件会包含了程序运行时的**内存，寄存器状态，堆栈指针，内存管理信息还有各种函数调用堆栈信息**等，我们可以理解为是程序工作当前状态存储生成第一个文件，许多的程序出错的时候都会产生一个core文件，通过工具分析这个文件，我们可以定位到程序异常退出的时候对应的堆栈调用等信息，找出问题所在并进行及时解决
* **产生core dump的几种情况**
  * **内存访问越界**
  * **多线程程序使用了线程不安全的函数**：应该使用**可重入的函数**
  * **多线程读写的数据未加锁保护**：对于会被多个线程同时访问的全局数据，应该注意加锁保护，否则很容易造成core dump
  * **非法指针**：使用空指针，随意使用指针转换
  * **堆栈溢出**：不要使用大的局部变量（因为局部变量都分配在栈上），这样容易造成堆栈溢出，破坏系统的栈和堆结构，导致出现莫名其妙的错误
* `ulimit  -c` 可以设置core文件的大小，如果**这个值为0.则不会产生core文件**，这个**值太小，则core文件也不会产生**，因为core文件一般都比较大
* 使用`ulimit  -c unlimited`来设置无限大，则**任意情况下都会产生core文件**
* 控制core文件保存位置和文件名格式
  * echo "/var/core_log/core-%e-%p-%t" > /proc/sys/kernel/core_pattern，这是临时的，这个也是动态加载和生成的
  * 永久修改在/etc/sysctl.conf文件中，在该文件的最后加上两行：sysctl -w kernel.core_pattern=/var/core_log/core-%e-%t-%p 和kernel.core_uses_pid = 0，最后执行sysctl –p生效
  * 以下是参数列表:
    * %p - insert pid into filename 当前pid(进程id)
    * %u - insert current uid into filename 当前uid(用户id)
    * %g - insert current gid into filename 当前gid(用户组id)
    * %s - insert signal that caused the coredump into the filename 导致产生core的信号
    * %t - insert UNIX time that the coredump occurred into filename core文件生成时的unix时间
    * %h - insert hostname where the coredump happened into filename 主机名
    * %e - insert coredumping executable name into filename 导致产生core的命令名/文件名
* 调试
  * gcc -o test -test.c -g
  * 运行程序./test，产生core文件在/var/core_log目录中
  * 进入/var/core_log，gdb调试core文件：gdb /path/test core-test-time-pid
  * gdb运行直到发生coredump，此时利用bt指令查看堆栈信息定位发生点

#### [**内存泄漏调试方法**](https://blog.csdn.net/weixin_36343850/article/details/77856051)

* 内存泄漏的概念
  * 内存泄漏是指由于疏忽或错误造成了程序未能释放掉不再使用的内存的情况。内存泄漏并非指内存在物理上的消失，而是**应用程序分配某段内存后，由于设计错误，失去了对该段内存的控制，因而造成了内存的浪费**
  * 内存泄漏是指堆内存的泄漏。堆内存是指程序从堆中分配的、大小任意的(内存块的大小可以在程序运行期决定)、使用完后必须显示释放的内存。应用程序一般使用malloc、realloc、new等函数从堆中分配到一块内存，使用完后，程序必须负责相应的调用free或delete释放该内存块。否则，这块内存就不能被再次被申请使用，我们就说这块内存泄漏了
* 内存泄漏分类
  * 堆内存泄漏 （Heap leak）。对内存指的是程序运行中根据需要分配通过malloc,realloc new等从堆中分配的一块内存，再是完成后必须通过调用对应的 free或者delete 删掉。如果程序的设计的错误导致这部分内存没有被释放，那么此后这块内存将不会被使用，就会产生Heap Leak
  * 系统资源泄露（Resource Leak）。主要指程序使用系统分配的资源比如 Bitmap,handle ,SOCKET等没有使用相应的函数释放掉，导致系统资源的浪费，严重可导致系统效能降低，系统运行不稳定
  * 没有将基类的析构函数定义为虚函数。当基类指针指向子类对象时，如果基类的析构函数不是virtual，那么子类的析构函数将不会被调用，子类的资源没有正确是释放，因此造成内存泄露

#### 什么时候发生段错误？

* MMU在做逻辑地址到物理地址的转换时发生2次检查
  * 检查逻辑地址是否在某个已定义的内存映射区域，这一步通过和mm_struct中，mmap指针所记录的vm_area_struct链表中的每个每个节点所限定的虚拟内存区域比较实现。vm_area_struct结构中的vm_start和vm_end成员记录该节点所定义的虚拟内存区域的起始/结束地址（逻辑地址）。**如果要访问的地址不在任何一个区域中，则说明是一个非法的地址**。Linux在搜索vm_area_struct是，不是使用链表，而是使用树结构加速查找速度
  * MMU得到该地址的页表项，检查页表项中的权限信息，如果**操作（读/写）与权限不符**，则触发保护异常(**使用野指针，试图修改字符串常量**等)

* 上述两种操作**都会导致段错误**

* core文件中是什么，gdb调试core文件

  * **在一个程序崩溃时，它一般会在指定目录下生成一个core文件**。core文件**仅仅是一个内存映象(同时加上调试信息)，主要是用来调试的**。通过core文件调试步骤：
    * ulimit -c unlimted（**打开core，默认没有打开**）
    * 运行./a.out（编译的时候加调试选项-g） **死锁阻塞，Ctrl+\ 产生core dump**
    * gdb ./a.out core.xxx

#### gdb调试死锁

* **借助 Core Dump**。在程序莫名其妙down掉了，此时操作系统会把当前的内存状况存储在一个core 文件中，通过查看core文件就可以直观的程序是因为什么而垮掉了。有时候程序down了, 但是core文件却没有生成，core文件的生成跟你当前系统的环境设置有关系，可以用下面的语句设置一下，然后再运行程序便会生成core文件

  ```shell
  ulimit -c unlimited
  ```

* core文件生成的位置一般于运行程序的路径相同，文件名一般为“**core.进程号**”

* 在多线程调试中使用Core Dump：

  * 使用 kill 命令产生 core dump文件：kill -11 pid 产生core文件
  * 使用gdb工具打开core文件 gdb dead_lock_demo core
  * 打印堆栈信息 **thread apply all bt查看死锁位置**
  
* 另外gdb可跟踪运行中的程序，使用`attach pid`命令可直接attach到进程或者线程，bt查看其运行的栈信息，这种方式容易定位死锁的进程

#### strace

- `strace -p pid`即可打印出进程的**系统调用信息，包括参数，返回值**等
- 它还能**调试进程接收到的信号情况**
- 频繁地系统调用会影响性能，这个命令可以用来调试性能及bug
