#### 3. 介绍一下kafka
https://blog.csdn.net/qq_29186199/article/details/80827085

https://blog.csdn.net/student__software/article/details/81486431

kafka是一个分布式消息队列,包括producer/broker和consumer.kafka会对每个消息根据topic进行归类,每个topic又会分成多个partition,消息会根据先进先出的方式存储.消费者通过offset进行消费. 

kafka的特点是吞吐量高,可以进行持久化,高可用.
#### 4. 为什么kafka吞吐量高?/介绍一下零拷贝
kafka吞吐量高是因为一个利用了磁盘顺序读写的特性,速度比随机读写要快很多,另一个是使用了零拷贝,数据直接在内核进行输入和输出,减少了用户空间和内核空间的切换.

零拷贝:传统文件读取并发送至网络的步骤是:先将文件从磁盘拷贝到内核空间,然后内核空间拷贝到用户空间的缓冲区,再从用户空间拷贝到内核空间的socket缓冲区,最后拷贝到网卡并发送.而零拷贝技术是先将文件从磁盘空间拷贝到内核缓冲区,然后直接拷贝至网卡进行发送,减少了重复拷贝操作.

#### 9. 如何保证kafka的消息不丢失
https://blog.csdn.net/liudashuang2017/article/details/88576274

我们可以从三个方面保证kafka不丢失消息
* 首先从producer生产者方面,为send()方法注册一个回调函数,可以得知消息发送有没有成功;将重试次数retrie设置为3;设置acks参数为all,当消息被写入所有同步副本之后才算发送成功.
* 在consumer消费者方面,关闭自动提交;
* 在broker集群方面,设置复制系数replica.factor为大于等于3
#### 10. kafka如何选举leader
首先启动的broker在zookeeper中创建一个临时节点并让自己称为leader,其他的节点会创建watch对象进行监听并成为follower,当broker宕机的时候,其他follower会尝试创建这个临时节点,但是只有一个能够创建成功,创建成功的broker就会成为leader.
