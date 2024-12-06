---
title: "2_分布式通信方案-RPC"
layout: post
author: "Marco"
header-style: text
hidden: true
tags:
  - 分布式
---

## 分布式通信方案-RPC

### 1. 基本概念

- ***什么是RPC？***

  ​	RPC（Remote Procedure Call）远程过程调用，简单的理解是一个节点请求另一个节点提供的服务。

- ***RPC服务的执行流程是怎样的？***

  > 一个应用部署在A服务器，想要调用B服务器上提供的方法。

  1. 首先先解决通信问题，A服务器和B服务器需要建立TCP连接。
  2. 再解决寻址问题，通过IP地址以及端口号访问B服务器，要知道方法的具体名称
  3. 方法的参数需要通过序列化变成二进制的形式传输过去，再通过反序列化解析二进制得到参数。从而使得B服务器得到参数，并计算出返回值。
  4. 返回值也需要通过序列化和反序列化传送给A。

- ***伪代码形式***

  ```c++
  // client
  int res = call(serverAddr, Multiply, lvalue, rvale);
  
  //server
  map<strig, function<>> myMap;
  myMap["Multiply"] = Multiply();
  listen(); // 等待请求
  call_id, argc = read();
  res = myMap[call_id](argc);
  send(res);
  ```

- ***RPC调用方式***

  - 同步调用
    - 客户端调用远程服务后，会一直阻塞直到远程调用返回结果，或者调用返回异常
  - Future异步调用
    - 客户端调用远程服务后，不会原地阻塞等待，而是立即返回一个Future对象，客户端可以决定何时到Future对象中获取调用结果
  - Callback回调调用
    - 客户端调用远程服务时，将Callback对象传递给RPC框架，然后直接返回处理其他逻辑，但获取到服务端调用结果或者异常信息后，再调用用户注册的Callback回调通知用户
  - Oneway单向调用
    - 客户端调用远程服务后，立即返回，且无需返回远程调用结果

### 2. 实战篇

1. [rest_rpc](https://github.com/qicosmos/rest_rpc)
2. [rpclib](https://github.com/rpclib/rpclib)
3. [phxrpc](https://github.com/Tencent/phxrpc)

