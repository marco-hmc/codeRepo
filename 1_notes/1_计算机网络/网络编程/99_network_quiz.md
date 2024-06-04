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


2/epoll和select的区别
3/epoll的高效,有几种工作模式( LT/ET)
5/TIMEWAIT是什么,为什么要设置TIMEWAIT状态
6/TCP的可靠性是如何实现的?(流量控制/拥塞控制/确认序号/校验???)

2/交给sub 线程的文件描述符如何回收的?
3/tcp粘包

4/tcp三次握手 /2次/4次?
5/tcp可靠性的实现原因
6/滑动窗口的作用