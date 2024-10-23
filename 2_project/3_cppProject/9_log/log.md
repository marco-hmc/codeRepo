#### 在进程崩掉后如何追踪日志

* 进程日志

  * 在程序开发中，肯定会记录一些日志，而日志记录的好坏可以直接影响调试，进而影响程序的发布进程
  * 目前有很多的开源日志库，选择合适的即可。如log4cplus等
  * 日志等级较多时，**一般在运行时，只记录WARN级别以上信息**，**如果有实时调整日志级别，将非常有助于定位问题**。
    **实时打开DEBUG级别日志，能详细跟踪程序流程**
  * 如果不能实时调整，只能重启的方式，这时bug可能不易复现

* core文件

  * 生产环境可能不会产生core文件，这时日志的记录就尤其重要了
  * 测试环境建议先打开内核转储：ulimit -c unlimited，或者调试到配置里，不用每次开个终端都要设置一遍
  * **注意，core文件与编译时的-g选项结合使用，且编译时不要加-02，否则gdb会看不到调试信息**
  * 使用gdb -c core a.out调试，bt打印崩溃时的栈信息，基本可以发现出问题的代码行

  * 更多gdb的命令可以查看相关man page，基本介绍可以参考内核转储coredump简介

* dmesg
  * 打印内核日志信息

  * 系统级别相关的信息会存储在此处，如进程异常崩溃退出等，也会有记录

  * 当一个进程使用的内存较大时，会被操作系统kill掉，这样的信息就会记录在dmesg中

    ```
    [1892837.939243] Out of memory: Kill process 10735 (oomServer) score 952 or sacrifice child
    ```

  * 根据进程异常崩溃信息，可以反推崩溃位置

    ```
    [5596955.061423] traps: TrapServer[32530] trap divide error ip:4bb78a sp:7ff530ff7230 error:0 in TrapServer[400000+251000]
    ```

  * 根据ip位置，使用`addr2line -e TrapServer 4bb78a`可打印进程的行号

* linux系统日志

  * https://blog.csdn.net/Mikeoperfect/article/details/79234585
  * https://blog.csdn.net/dubendi/article/details/78782691
