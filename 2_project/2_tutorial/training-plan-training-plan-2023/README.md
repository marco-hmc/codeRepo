## DSCLab 新生培养计划

培养方向：数据库方向基础知识积累、分布式数据库研发

培养目标：

1. 具备一定的软件工程能力
2. 掌握基础数据结构和数据库关键技术
3. 掌握分布式原理和应用开发

技能培养：

**C++ / JAVA / GO 任选一门主力学习, Python 选修**

1. Git、Stencil、Visio 、Docker 等工具的使用
2. 软件工程能力（代码规范、协作开发、UML 的使用、代码测试、文档撰写）
3. Research、Presentation 能力

**时间安排表：**


|  Week   |          Point          | Detail                                                                                                                                                                  | Project                                                                                                                                                                                                                              |
| :-----: | :---------------------: | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
|    1    |         基础知识-引入         | 了解数据库系统的基本概念和架构，包括数据库管理系统（DBMS）的组成部分和功能。                                                                                                                                | 课程学习 & 撰写相关文档                                                                                                                                                                                                                        |
|    2    |      基础知识-计算 & 存储       | 学习数据库中的数据存储和管理技术，包括数据的物理存储结构、索引、文件组织和存储管理。了解数据库系统的计算模型和查询处理技术，如查询计划、查询优化和执行策略。                                                                                          | 课程学习 & 撰写相关文档                                                                                                                                                                                                                        |
|    3    |    基础知识-查询优化 & AI4DB    | 学习高级的查询优化技术，包括代价估算、查询重写和物理计划生成。了解AI在数据库系统中的应用，如自动化索引选择、查询优化和参数调优。                                                                                                       | 课程学习 & 撰写相关文档                                                                                                                                                                                                                        |
|   4-5   |     CMU-Buffer Pool     | 以个人为单位，实现一个buffer pool，并测试其性能及内存占用。并撰写相关文档                                                                                                                              | [项目地址](https://15445.courses.cs.cmu.edu/spring2023/project1/)                                                                                                                                                                        |
|   6-8   |    CMU-B+Tree Index     | 在buffer pool的基础上，实现一个B+树，需包含单元测试及测试性能。                                                                                                                                  | [项目地址](https://15445.courses.cs.cmu.edu/spring2023/project2/)                                                                                                                                                                        |
|   8-9   |      CMU-Execution      | 了解 SQL Engine 组件及功能，学习 SQL 解析流程及抽象语法树。学习执行算子，如 Join, Agg, Scan 的不同实现。了解基本的查询优化方法，了解 Volcano 及 Vectorized 执行器架构                                                          | 撰写相关文档<br />实现数据库的执行器。[项目地址](https://15445.courses.cs.cmu.edu/spring2023/project3/)                                                                                                                                                  |
|  10-11  | CMU-Concurrency-Control | 理解事务的概念及产生原因、理解ACID特性<br/>并发控制（乐观、悲观）<br/>数据持久化和故障恢复（日志、检查点、快照）                                                                                                         | 撰写相关文档<br />基于锁实现数据库的并发控制，要求保证事务的ACID特性 [项目地址](https://15445.courses.cs.cmu.edu/spring2023/project4/)                                                                                                                                |
|   12    | TinySQL Optimizer Part1 | 搜索框架 System R 和 Cascades                                                                                                                                                | 撰写相关文档, 实现项目<br>[Project 4: TinySQL Optimizer](https://github.com/talent-plan/tinysql/blob/course/courses/proj4-README-zh_CN.md)                                                                                                     |
|   13    | TinySQL Optimizer Part2 | 代价估算以及统计信息以及 Join Reorder                                                                                                                                               | 撰写相关文档, 实现项目<br>[Project 4: TinySQL Optimizer]()                                                                                                                                                                                     |
|   14    |       Data Mining       | 掌握机器学习的经典算法和数据挖掘的基本流程。                                                                                                                                                  | 整理算法文档<br /> 完成分类和时间序列预测两个项目 <br /> [项目地址](./Week12-Data%20Mining/)                                                                                                                                                                  |
|   15    |           NLP           | 掌握NLP基础工具，以及预训练模型的使用方法。                                                                                                                                                 | 整理算法文档 <br />掌握NLP工具包 <br />完成文本分类项目<br />[项目地址](./Week13-NLP)                                                                                                                                                                       |
|   16    |           CV            | 掌握CV常见模型，实现简单的图像分类，了解多模态模型的构建。                                                                                                                                          | 整理算法文档 <br />完成图像分类项目<br />[项目地址](./Week14-CV)                                                                                                                                                                                       |
|   17    |  Transformer & LLM 基础   | 学习 Transformer & LLM 基础                                                                                                                                                 | 撰写相关文档<br>[Self-Attention](https://www.bilibili.com/video/BV1Wv411h7kN/?p=38&vd_source=4a123edfa6cfeff60587a45315c38bad) [Transformer](https://www.bilibili.com/video/BV1Wv411h7kN/?p=49&vd_source=4a123edfa6cfeff60587a45315c38bad) |
|   18    |        LLM 模型结构         | 学习 LLM 模型结构, 尝试手写小参数模型并训练                                                                                                                                               | 撰写相关文档, 实现项目<br>[GPT in 60 Lines of NumPy 项目地址](https://jaykmody.com/blog/gpt-from-scratch/#fine-tuning)                                                                                                                             |
| 19 - 20 |     LLM for 数据库参数调优     | LLM + Database 项目实践, 掌握 LLM 4 Database 实战能力                                                                                                                             | [项目地址](https://github.com/SolidLao/GPTuner)                                                                                                                                                                                          |
|   21    |  TinyKV-Standalone KV   | 分布式相关概念、时钟 <br/> CAP、BASE <br/> 拜占庭问题 <br /> [Zab](https://marcoserafini.github.io/papers/zab.pdf) <br/> [Gossip](https://flopezluis.github.io/gossip-simulator/) <br/> | 实现单机的kv server<br />[Project1 StandaloneKV](https://github.com/tidb-incubator/tinykv/blob/course/doc/project1-StandaloneKV.md)                                                                                                       |
|   22    |    TinyKV Raft KV 2A    | 实现基础Raft协议<br/>（1）Leader 选举<br/>（2）日志复制<br/>（3）RawNode 接口                                                                                                               | [Project2 RaftKV](https://github.com/tidb-incubator/tinykv/blob/course/doc/project2-RaftKV.md)                                                                                                                                       |
| 23 - 24 |    TinyKV Raft KV 2B    | 在 Raft 之上搭建一个容错的 KV 服务器<br/>（1）PeerStorage<br/>（2）Raft ready process                                                                                                    | [Project2 RaftKV](https://github.com/tidb-incubator/tinykv/blob/course/doc/project2-RaftKV.md)                                                                                                                                       |
| 25 - 26 |    TinyKV Raft KV 2C    | 增加 raftlog GC 和 snapshot 的支持<br/>（1）Raft快照实现<br/>（2）raftstore                                                                                                           | [Project2 RaftKV](https://github.com/tidb-incubator/tinykv/blob/course/doc/project2-RaftKV.md)                                                                                                                                       |
|   27    |    TinyKV Trasaction    | 分布式事务(2PC / 3PC) <br />基于Percolator实现分布式事务，分析Percolaor的优缺点                                                                                                              | [Project 4 Transactions](https://github.com/tidb-incubator/tinykv/blob/course/doc/project4-Transaction.md)                                                                                                                           |


说明：整个学习流程的作业和文档需要在实验室 Github 仓库里面提交，每个 Project
会事先建立好框架，每个同学按照框架进行代码和文档的撰写。并且在代码过程中抽象公共代码库方便后续同学的使用，且需做好
todo-list，方便功能的完善。

## 如何提交作业

1. 第一次提交作业的时候请先 `fork` 当前项目到自己的仓库

2. 在自己的仓库里面进行作业的更新

   以第一次作业为例，比如你 `fork` 之后你的代码地址为 `git@github.com:ehds/training-plan.git`

    1. 克隆仓库到本地：

       `git clone git@github.com:ehds/training-plan.git`

    2. 进入当前实验文件夹`Week1-Databse-Introduction`

       `cd Week1-Databse-Introduction`

    3. 新建一个自己的文件夹，名字+实验名称，参考 Example

       `cp -r Example DongShengHe-Week1`

       完善实验文档 Markdown 文件

    4. add 作业内容

       `git add .`

    5. commit 修改

       `git commit -m "message"` （message使用英文填写你所做的修改）如 `git commit -m “complete week1 experiment`

    6. push 分支

       `git push origin master`

3. 提交 PR

   在 Gihub 仓库界面新建一个 pull request 到实验室仓库

4. 审核与修改

   待审核人审核后，根据修改意见进行修改，待通过后即可

## 如何提问

大家遇到问题首先合理利用搜索引擎，网络上可能已经存在比较完美的解决方案

在向同学和老师提问的时候，请先描述问题出现的背景和出现问题的状况，这样更加有利于问题的解决。

请参考[提问的智慧。](https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way/blob/master/README-zh_CN.md)
