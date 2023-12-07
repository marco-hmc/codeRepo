#### 1. 介绍一下Hadoop
Hadoop是一套大数据解决方案,提供了一套分布式的系统基础架构,包括HDFS,MapReduce和YARN.
* HDFS提供分布式的数据存储
* MapReduce负责进行数据运算 
* YARN负责任务调度

HDFS是主从架构的,包括namenode,secondarynamenode和datanode.datanode负责存储数据,namenode负责管理HDFS的目录树和文件元信息.<br>
MapReduce包括jobtracker,tasktracker和client.Jobtracker负责进行资源调度和作业监控.tasktracker会周期性的通过心跳向jobtracker汇报资源使用情况.