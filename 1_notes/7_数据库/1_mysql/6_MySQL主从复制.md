---
title: "MySQL主从复制与读写分离"
layout: post
author: "Marco"
header-style: text
hidden: true
tags:
  - 数据库
---

## MySQL主从复制与读写分离

> [参考资料](https://m.php.cn/article/462450.html)

### 1. 基本概念

- ***为什么要主从复制？***
- 在业务复杂的系统中，有这么一个情景，有一句sql语句需要锁表，导致暂时不能使用读的服务，那么就很影响运行中的业务，使用主从复制，让主库负责写，从库负责读，这样，即使主库出现了锁表的情景，通过读从库也可以保证业务的正常运行。
  - 做数据的热备，主库宕机后能够及时替换主库，保证业务可用性。
- 架构的扩展。业务量越来越大，I/O访问频率过高，单机无法满足，此时做多库的存储，降低磁盘I/O访问的频率，提高单个机器的I/O性能。
- ***主从复制的实现有哪些主要部分？***
  - binlog线程部分：主的数据库有一个bin-log二进制文件，记录所有sql语句；
  - io线程部分：从的数据库，把主的数据库的sql语句复制过来。
  - sql执行线程部分：从的数据库有一个重做日志(relay-log)，会再执行这些sql语句。使得主从同步。
- ***主从复制的步骤***
  - ![image-20220522132844896](https://s2.loli.net/2022/05/22/Olm8fQAvTg146Vz.png)
  - 步骤一：主库的更新、插入、删除事件写入到binlog；
  - 步骤二：从库发起连接，连接到主库；
  - 步骤三：主库创建一个binlog dump thread，把binlog的内容发送到从库；
  - 步骤四：从库启动之后，创建一个I/O线程，读取主库传过来的binlog内容写入到relay log；
  - 步骤五：从库创建一个sql线程，从relay log读取内容，将更新内容写入到从库中；

### 2. 进阶概念

> [参考资料](https://blog.csdn.net/linkingfei/article/details/102774992)

- 单master

- 一主一从

- 一主n从

- 横向集群

- 纵向集群

    