https://blog.csdn.net/u011204847/article/details/51010205

spark是一个通用内存并行计算框架.它可以在内存中对数据进行计算,效率很高,spark的数据被抽象成RDD(弹性分布式数据集)并且拥有DAG执行引擎,兼容性和通用性很好.可以和Hadoop协同工作.
#### 6. 介绍一下spark-streaming
https://blog.csdn.net/yu0_zhang0/article/details/80569946

spark-streaming是spark的核心组件之一.主要提供高效的流计算能力.spark-streaming的原理是将输入数据流以时间片进行拆分,然后经过spark引擎以类似批处理的方式处理每个时间片数据.

spark-streaming将输入根据时间片划分成一段一段的Dstream(也就是离散数据流),然后将每一段数据转换成RDD进行操作. 

#### 7. spark的transformation和action有什么区别
spark的算子分成transformation和action两类
* transformation是变换算子,这类算子不会触发提交,是延迟执行的.也就是说执行到transformation算子的时候数据并没有马上进行计算,只是记住了对RDD的逻辑操作 
* action算子是执行算子,会出发spark提交作业,并将数据输出到spark

#### 8. spark常用的算子说几个
spark的算子分为两类:transformation和action

常用的transformation算子:
```scala
// union 求并集
val rdd8 = rdd6.union(rdd7)

// intersection 求交集 
val rdd9 = rdd6.intersection(rdd7)

// join 将rdd进行聚合连接,类似数据库的join 
val rdd3 = rdd1.join(rdd2)

// map flatMap mapPartition 传入一个函数对数据集中的每一个数据进行操作 
val arr1 = Array(1,2,3,4,5)
val arr2 = rdd1.map(_+1)

// countByKey reduceByKey partitionByKey 统计每个key有多少个键值对 
```
常用的action算子
```scala
// reduce 按照一定的方法将元素进行合并 
val rdd2 = rdd1.reduce(_+_)

// collect 将RDD转换为数组
rdd1.collect

// top 返回最大的k个元素
rdd1.top(2)
```

#### 11. 说下spark中的宽依赖和窄依赖
https://blog.csdn.net/a1043498776/article/details/54889922

* 宽依赖:指子RDD的分区依赖于父RDD的所有分区,举例:groupbykey,join
* 窄依赖:指父RDD的每个分区被最多一个子RDD的分区所依赖,举例:map,filter
![](https://img-blog.csdn.net/20170206221148299?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYTEwNDM0OTg3NzY=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
#### 12. 说下spark中stage是依照什么划分的
https://zhuanlan.zhihu.com/p/57124273

spark中的stage其实是一组并行的任务,spark会将多个RDD根据依赖关系划分成有向无环图DAG,DAG会被划分成多个stage,划分的依据是RDD之间的宽窄依赖.遇到宽依赖就划分stage.因为宽依赖与窄依赖的区别之一就是宽依赖会发生shuffle操作,所以也可以说stage的划分依据是是否发生shuffle操作.

#### 13. spark的内存管理是怎样的
https://www.jianshu.com/p/4f1e551553ae 

https://www.cnblogs.com/wzj4858/p/8204282.html

spark的内存包括静态内存管理和统一内存管理两种机制.静态内存管理中存储和执行两块内存区域是分开的,统一内存管理中两块内存之间可以相互借用<br>
* 静态内存管理:静态内存管理机制下堆内内存包括安全内存,存储内存,shuffle内存和unroll内存

![](fig/spark内存一.png)
  * 统一内存管理:统一内存管理机制下内存分为spark内存,用户内存和保留内存三部分.用户内存存放用户代码逻辑和自定义数据结构等,保留内存存放的是spark的内部对象和逻辑.
    ![](https://upload-images.jianshu.io/upload_images/195230-f119edabb5683f38.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

#### 14. spark的容错机制是什么样的
https://blog.csdn.net/dengxing1234/article/details/73613484

spark的容错机制是通过血统(lineage)和checkpoint来实现的 .

* RDD的lineage可以看作是一个重做日志(redo log)记录的是它粗粒度上的transformation操作.当rdd的分区数据丢失时,它可以根据lineage重新计算来恢复数据. 在窄依赖上可以直接计算父RDD的节点数据进行恢复,在宽依赖上则要等到父RDD所有数据计算完后并将结果shuffle到子RDD上才能完成恢复.
* 如果DAG中的lineage过长,或者在宽依赖上进行checkpoint的收益更大,就会使用checkpoint进行容错,将RDD写入磁盘进行持久化存储,如果节点数据丢失,就从磁盘读取数据进行恢复.
