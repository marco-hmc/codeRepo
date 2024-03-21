## chatRoom

> Marco

[toc]

本次项目并未有功能、或者设计上的突破，纯属造轮子。但很喜欢网上一句话，`I don't understand if I can not write it.`。因此也就有了这篇博文。完整做完实验，你可以有如下收获。一是用于巩固socket通信的用法；二是尝试使用简易的sql服务；三是加强对`c/c++`工程开发的理解。

> 本文代目对应[仓库](https://github.com/marco-hmc/chatRoom_tiny)
>
> 预计完成时间：4h

### 1. demo1

* **Task:**

  用socket通信完成最简单聊天室功能。

* **Ref:**

  [C socket编程–相关api](https://blog.csdn.net/qq_27870421/article/details/100173212)

  

### 2. demo2

* **Task:**

  加入数据库功能，提供注册等服务。
  
* **How to use：**

  ```shell
  cmake
  激活服务端：
  	./server
  激活客户端：
  	./client 127.0.0.1 8000
  ```
  
  
  
* **Ref:**

  [基于linux的多功能聊天室](https://www.cnblogs.com/samuelwnb/p/4265519.html)
  
  [SQL using c/c++ and SQlite](https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/?ref=lbp)
  
  [sqlite-教程](https://www.runoob.com/sqlite/sqlite-tutorial.html)



