## 资料收集

### **面经&学习路线**

[一站式学习资料](https://[www.r2coding.com/#/](http://www.r2coding.com/#/))

[cpp-guide-web](https://balloonwj.github.io/cpp-guide-web/)

[后端架构师技术图谱](https://github.com/xingshaocheng/architect-awesome)

[cpp-notes](https://github.com/VitoChueng/RegularNotes)

[BestJavaer](https://github.com/crisxuan/bestJavaer)

[面试突击学习](https://github.com/wolverinn/Waking-Up)

[cpp后台开发知识](https://github.com/twomonkeyclub/BackEnd)

[双非硕上岸之路](https://github.com/forthespada/CSLearning)

[CS-Notes](https://github.com/CyC2018/CS-Notes)



### **书籍**

[awesome-cs-books](https://github.com/imarvinle/awesome-cs-books)

[超过1000本!计算机经典书籍PDF分享]**(**https://github.com/forthespada/CS-Books)

### **网络编程**

[TCP-IP-NetworkNote](https://github.com/riba2534/TCP-IP-NetworkNote)

### **数据库**

[sqlite3-c++](https://www.runoob.com/sqlite/sqlite-update.html)

[sqlite](https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/)

### **开源项目**

[汇总](http://ezlippi.com/blog/2014/12/c-open-project.html)

* <现代操作系统> Tanenbaum.A.S: 
* <程序员的自我修养:链接/装载与库>
* <Linux系统编程>
* <Linux内核设计与实现>
* <Windows程序设计>第五版(第六版以后,这个不再是用Windows Native API写C程序了,而是转到C#平台上了),这本书是中国第一代程序的windows启蒙书籍,你所看到的大多数桌面软件,如QQ,的开发者可能都是通过阅读这本书启蒙起来的.
<Windows核心编程>,这本书搞Windows开发的一定都知道这本书的分量.
<linux内核情景分析>毛德操老师的书,非常的实在,另外他写了一套关于Windows源码分析的书,这本书是基于开源的"Windows"ReactOS,书名叫<Windows内核情景分析>.
<编译系统透视:图解编译原理>,编译原理方面的实践书.
<编程之美>,关于面试的,主要是一些算法和逻辑思维题实战.
<程序员的修炼之道__从小工到专家>这本书特别推荐学生看一下,能大幅度地提高你实际编码的技巧和编码风格.
<代码整洁之道>同上
<大话设计模式>
<Windows PE文件权威指南>
<Java编程思想>
<80x86汇编语言程序设计教程>

* 推荐学习_<深入理解计算机系统>_ 和 _<数据密集型应用系统设计>_

| 科目                                      | 为何要学?                                                   | 最佳书籍                                                     | 最佳视频                          |
| ----------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------- |
| **[编程](#编程)**                         | 不要做一个"永远没彻底搞懂"诸如递归等概念的程序员.           | _[<计算机程序的构造和解释>](https://book.douban.com/subject/1148282/)_ | 着重学习前三章                    |
| **[计算机架构](#计算机架构)**             | 如果你对于计算机如何工作没有具体的概念,那么你所做出的所有高级抽象都是空中楼阁. | _[<深入理解计算机系统>](https://book.douban.com/subject/26912767/)_ | 着重学习前六章                    |
| **[算法与数据结构](#算法和数据结构)**     | 如果你不懂得如何使用栈/队列/树/图等常见数据结构,遇到有难度的问题时,你将束手无策. | _[<算法设计手册>](https://book.douban.com/subject/4048566/)_ | Steven Skiena's lectures          |
| **[数学知识](#数学知识)**                 | 计算机科学基本上是应用数学的一个"跑偏的"分支,因此学习数学将会给你带来竞争优势. | _[<计算机科学中的数学>](https://book.douban.com/subject/33396340/)_ | Tom Leighton's MIT 6.042J         |
| **[操作系统](#操作系统)**                 | 你所写的代码,基本上都由操作系统来运行,因此你应当了解其运作的原理. | _[<操作系统导论>](https://book.douban.com/subject/33463930/)_ | Berkeley CS 162                   |
| **[计算机网络](#计算机网络)**             | 互联网已然势不可挡:理解工作原理才能解锁全部潜力.           | _[<计算机网络:自顶向下方法>](https://book.douban.com/subject/30280001/)_ | Stanford CS 144                   |
| **[数据库](#数据库)**                     | 对于多数重要程序,数据是其核心,然而很少人理解数据库系统的工作原理. | _[<Readings in Database Systems>](https://book.douban.com/subject/2256069/) (暂无中译本)_ | Joe Hellerstein's Berkeley CS 186 |
| **[编程语言与编译器](#编程语言与编译器)** | 若你懂得编程语言和编译器如何工作,你就能写出更好的代码,更轻松地学习新的编程语言. | _[<Crafting Interpreters>](https://craftinginterpreters.com/)_ | Alex Aiken's course on Lagunita   |
| **[分布式系统](#分布式系统)**             | 如今,_多数_ 系统都是分布式的.                              | _[<数据密集型应用系统设计>](https://book.douban.com/subject/30329536/)_ | MIT 6.824                         |

## 1. 指引

### 1.1 编程

大多数计算机专业本科教学以程序设计"导论"作为开始.这类课程的最佳版本不仅能满足初学者的需要,还适用于那些在初学编程阶段遗漏了某些有益的概念和程序设计模式的人.

对于这部分内容,我们的标准推荐是这部经典著作:[<计算机程序的构造和解释>](https://book.douban.com/subject/1148282/).

我们建议至少学完SICP的前三章,并完成配套的习题.如果需要额外的练习,可以去解决一些小的程序设计问题,比如[exercism](http://exercism.io).

> **中文翻译新增:**  
>
> * 关于SICP国内视频观看地址  
>   * [MIT的免费视频课程(中英字幕)](https://www.bilibili.com/video/av8515129/)  
>   * [Brian Harvey 开设的 SICP 课程(英文字幕)](https://www.bilibili.com/video/av40460492/)  
> * Scheme 学习的相关资源参见:<https://github.com/DeathKing/Learning-SICP>  
> * 更详细的补充说明:[#3](https://github.com/keithnull/TeachYourselfCS-CN/issues/3)  

为什么这么要学SICP?因为 SICP 是独一无二的,它可以__至少很有可能__改变你对计算机和编程的基本认识.不是每个人都有这样的体验.有的人讨厌这本书,有的人看了前几页就放弃了.但潜在的回报让它值得一读.

如果你觉得SICP过于难,试试 _<Composing Programs>_.如果还是不合适,那我们推荐 _<程序设计方法>([中文版](https://book.douban.com/subject/1140942/),[英文版](http://www.htdp.org/))_ ;如果你觉得SICP过于简单,那我们推荐 _[<Concepts, Techniques, and Models of Computer Programming>](https://book.douban.com/subject/1782316/)_ .如果读这些书让你觉得没有收获,也行你应该先学习其他科目,一两年后再重新审视编程的理念.

> 新版原文删除了对 _<Concepts, Techniques, and Models of Computer Programming>_ 一书的推荐,但这本书对各种编程模型有深入的见解,值得一读.所以译文中依然保留.
> _ 译者注

[![计算机程序的构造和解释](.自学CS顺序以及书单.asserts/66758473-ef7bff80-eed0-11e9-944a-15ae5c8542ca.jpg)](https://book.douban.com/subject/1148282/) 

### 1.2 计算机架构

计算机架构__有时候又被称为"计算机系统"或者"计算机组成"__是了解软件底层的的重要视角.根据我们的经验,这是自学的软件工程师最容易忽视的领域.

我们最喜欢的入门书是 _[<深入理解计算机系统>](https://book.douban.com/subject/26912767/)_.典型的[计算机体系结构导论课程](http://csapp.cs.cmu.edu/3e/courses.html)会涵盖本书的 1 - 6 章.

我们喜爱<深入理解计算机系统>,因为它的实用性,并且站在程序员的视角.虽然计算机体系结构的内容比本书所涉及的内容多得多,但对于那些想了解计算机系统以求编写更快/更高效/更可靠的软件的人来说,这本书是很好的起点.

对于那些既想了解这个主题又想兼顾硬件和软件的知识的人来说,我们推荐 _[<计算机系统要素>](https://book.douban.com/subject/1998341/)_,又名"从与非门到俄罗斯方块"("Nand2Tetris"),这本书规模宏大,让读者对计算机内的所有部分如何协同工作有完全的认识.这本书的每一章节对应如何构建计算机整体系统中的一小部分,从用HDL(硬件描述语言)写基本的逻辑门电路出发,途经CPU和汇编,最终抵达诸如俄罗斯方块这般规模的应用程序.

我们推荐把此书的前六章读完,并完成对应的项目练习.这么做,你将更加深入地理解,计算机架构和运行其上的软件之间的关系.

[![深入理解计算机系统](.自学CS顺序以及书单.asserts/82109944-12270d00-976d-11ea-85a9-774e4f762ec9.png)](https://book.douban.com/subject/26912767/) [![计算机系统要素](.自学CS顺序以及书单.asserts/66758695-60231c00-eed1-11e9-8422-a4acfb10a390.jpg)](http://www.nand2tetris.org) 

### 算法与数据结构

关于算法与数据结构,有成百上千的书可供使用,但是我们的最爱是Steven Skiena编写的 _[<算法设计手册>](https://book.douban.com/subject/4048566/)_.显而易见,他对此充满热爱,迫不及待地想要帮助其他人理解.

最后,我们强烈推荐 _[<怎样解题>](https://book.douban.com/subject/2124114/)_.这本书极为优秀且独特,指导人们解决广义上的问题,因而一如其适用于数学,它适用于计算机科学.

## 2. 附录

### 2.1 经典书推荐

#### 1.1 SICP

我们建议至少学完SICP的前三章,并完成配套的习题.

SICP,即计算机程序的构造和解释.因为 SICP 是独一无二的,它可以__至少很有可能__改变你对计算机和编程的基本认识.不是每个人都有这样的体验.有的人讨厌这本书,有的人看了前几页就放弃了.但潜在的回报让它值得一读.

如果你觉得SICP过于难,试试 _<Composing Programs>_.如果还是不合适,那我们推荐 _<程序设计方法>([中文版](https://book.douban.com/subject/1140942/),[英文版](http://www.htdp.org/))_ ;如果你觉得SICP过于简单,那我们推荐 

#### 2.2 龙书

龙书,即编译原理,依旧是内容最为完整的编译器单本书籍.由于过分强调一些如今不够时新的主题的细节,比如解析,这本书招致了恶评.然而事实上,这本书从未打算供人一页一页的学习,而仅仅是为了给教师准备一门课程提供足够的材料.类似地,自学者可以从书中量身按需挑选主题,或者最好依照公开课授课教师在课程大纲中的建议.

## 科普类

### 1. 代码大全

构建之法

软件调试

head first java

**Java并发编程实战**

**大话设计模式**

高性能mySQL

Wireshark网络分析就这么简单

哥德尔`艾舍尔`巴赫:集异璧之大成

穿越计算机的迷雾

<黑客与画家>

码农翻身

逻辑的引擎

## 3. 计算机网络

### 3.1 重点学习内容

### 3.2 **资料推荐：**

* 《Wireshark网络分析就这么简单》 
  * 更偏向于实战
* 计算机网络 第7版（谢希仁 著）
  - 学习网络，可以先看**计算机网络**这本书，讲解通俗易懂，前面的物理层和链路层可以快速看，了解基本原理即可，重点学习网络层、传输层和应用层，其中传输层的TCP和UDP是面试最常考的，非常重要。网络的知识比较容易理解，但是知识点比较繁杂，一段时间不看就很容易忘记，建议学习之后将各个知识点整理成文档或者笔记，有助于找工作前复习。
* TCP/IP详解 原书第2版（卷1）
  - 学完**计算机网络**，可以基本建立计算机网络的知识体系，但是这本书深度不够，建议继续学习**TCP/IP详解 卷1**，作为对TCP/IP协议的深入，这本书讲解非常细致，看的过程中很容易陷入细节，对整本书系统学习的话比较花时间，如果时间有限的话，可以先选择性地学习一些章节，建议先将传输层的内容看完，有助于对TCP和UDP的深入理解，其他层的内容可以根据个人情况选择性的学习。
* UNIX网络编程 第3版（卷1）
  - 另外，如果想要对网络编程进行实践，可以继续学习**UNIX网络编程 卷1**

## 4. 操作系统

####   操作通用知识

*  深入理解计算机系统 第3版（CSAPP）
   *  先看**深入理解计算机系统**，操作系统方面的神书，内容非常经典，而且比较通俗易懂，适合入门，软件的话建议先学习第二部分和第三部分，再根据个人情况学习第一部分。
*  《程序员自我修养》 
   *  如果想对**编译链接**的原理进行深入学习，可以参考**程序员的自我修养**，这本书非常详细的讲解了程序编译过程中的具体细节。
*  操作系统 精髓与设计原理 第8版
   *  然后再学习**操作系统 精髓与设计原理**，这本书比现代操作系统更通俗易懂，可以结合CSAPP一起看，两本书的知识点相互有所弥补。
*  ==协程==(GO web2.0时代重要的东西.处理高并发)

-------

## 6. 数据库

### 6.1 重点学习内容

### 6.2 **资料推荐：**

*  高性能MySQL 
  *  本书深度讲解了mysql引擎架构、索引设计、SQL查询优化的实战技巧、复制、分片等原理，还有运维技能。适合精读。 
* 《 经典原版书库：数据库系统概念（英文精编版·第6版） 》
* 数据库的知识面试问的不多，但是数据库对于以后工作是肯定会用到的，如果有时间建议将基础打好，可以先看**数据库系统概念**，了解数据库的基础知识，然后阅读**mysql必知必会**这本书，可以帮助你快速学习 *mysql* 的基本语法。


## ==8. 分布式==

### 8.1 重点学习内容

* 一致性协议
* raft/paxos/zab/cap等理论

### 8.2 **资料推荐：**

* 大话设计模式

  * 本书并没有局限于那种分布式框架，而是着重讲解分布式整体架构设计理念和基础知识。

    **作者水平非常高，本书广度非常大**（诚然并不是很深，要在一本书里将那么多知识深度讲解也是不可能的），深入浅出，大家不用担心晦涩难懂（在这里更加推荐英文基础好的话直接读英文原版）。

## 9. 实战项目

### *9.1 C语言制作斗地主发牌*

*[c语言 斗地主的发牌期](https://study.163.com/course/introduction/1321006.htm#/courseDetail)*

*可以掌握基本项目开发。*

### 9.2 C语言的http server

[tinyhttpd](https://github.com/EZLippi/Tinyhttpd)

超轻量级http server，可以用来理解服务器程序的原理和本质。

### 9.3 c语言的数据库

[dbl_tutorial](https://github.com/cstack/db_tutorial)

用c从零开始搭建一个简单的数据库

### 9.4 C++ 网站压力测试

[压力测试](http://home.tiscali.cz/~cz210552/webbench.html)

这个资料使用fork()模拟多个客户端同时访问我们设定的URL，测试网站在压力下工作的性能。适合用于学习网络编程

### 9.5 c++ Lightweight web server

[high performance webserver](https://github.com/linyacool/WebServer)

[lightweight web server based on linux epoll](https://github.com/imarvinle/WebServer)

### 9.6 libjson

[json解析器](https://github.com/cesanta/frozen)

 这是一个超级高效的JSON解析器，并且高度可定制的，非常轻巧。 

### ==9.7 kv存储==

[levelDB](https://github.com/google/leveldb)

这是一个基于LSM结构的KV存储，levldb常常被用作各类数据库、存储系统的存储引擎，估计在BAT都能找到它的使用。

分布式存储数据库


[有哪些你看了以后大呼过瘾的编程书](https://www.zhihu.com/question/50408698)

## 1. 计算机

* SICP
  
  * SICP帮助读者了解CS的核心概念,属于从高空俯瞰世界,刚入门的读者不应该错过.
  
*  Clean Architecture: A Craftsman's Guide to Software Structure and Design
  
*  这本书是Uncle Bob最近几年的博文合集,读完以后有种灵台清明的感觉,做code review的时候思路清晰了很多. 
  
*  寒江独钓:windows内核安全编程

*  密码故事-人类智力的另类较量

  ![img](https://pic2.zhimg.com/50/v2-da063b75aace2ac7dcb4e453d2a19b98_hd.jpg?source=1940ef5c)

  ....

*  DOOM启示录

  ![img](.书单.asserts/v2-e020b309c91a608cd2d84b0fef17e297_hd.jpg)

## C/C++

* [C++标准程序库--自修教程与参考手册](http://pan.baidu.com/s/1qWLNhaG)
* [C++程序设计原理与实践](http://pan.baidu.com/s/1ntqfhPJ)
* [C++程序设计语言_特别版](http://pan.baidu.com/s/1o6jX3iq)
* [C++编程惯用法__高级程序员常用方法和技巧](http://pan.baidu.com/s/1i3sVhJZ)
* [C++编程规范-101条规则准则与最佳实践](http://pan.baidu.com/s/1ntDfM21)
* [C++语言的设计和演化](http://pan.baidu.com/s/1kT3a2dp)
* [C++释难解惑](http://pan.baidu.com/s/1nt4ssrf)
* [C和C++安全编码(中文版)](http://pan.baidu.com/s/1hqqVtp6)
* [Exceptional C++ Style(Herb Sutter).中文版](http://pan.baidu.com/s/1qWCtFOC)
* [Exceptional C++ 中文版](http://pan.baidu.com/s/1pLCHC)
* [More Exceptional C++(中文版)](http://pan.baidu.com/s/1qWLNgZE)
* [From C++ to Objective-C-english](http://pan.baidu.com/s/1o6LRolc)
* [From C++ to Objective-C-中文版]
* [Linux C编程一站式学习6.14--宋劲衫](http://pan.baidu.com/s/1bny7ga7)
* [从缺陷中学习C/C++](http://pan.baidu.com/s/1c0GLTOs)
* [你必须知道的222个C++语言问题.范立锋.扫描版](http://pan.baidu.com/s/1c03oHVE)
* [深入学习:GNU C++ for Linux 编程技术](http://pan.baidu.com/s/1dDkVKVB)
* [编写高质量代码  改善C++程序的150个建议.李健.扫描版](http://pan.baidu.com/s/1pJlXxk3)

## C/C++进阶

* [Accelerated C++中文版 ]
* [Advanced c++ Programming  Styles and Idioms中文版]
* [C++ API设计--英文版]
* [C++ API设计]
* [C++代码设计与重用]
* [C++标准库__自学教程与参考手册(第2版)英文版]
* [C++沉思录(Ruminations on C++)中文第2版]
* [C++程序设计]
* [C++设计新思维(Modern_C++_Design)]
* [大规模C++程序设计]
* [模板编程与OO编程范型--混搭]
* [深度探索C++对象模型]
* [高质量C++／C编程指南]
* [Imperfect C++]

## 网络相关

* [图解TCP_IP_第5版](http://pan.baidu.com/s/1o6181v0)
* [深入理解Nginx模块开发与架构解析](http://pan.baidu.com/s/1c0zQUyO)

## 数据库

* [Google MapReduce-中文版]
* [Google MapReduce-英文版osdi04]
* [NoSQL数据库笔谈]
* [The Google File System]
* [高性能MySQL(第2版)中文版.施瓦茨.扫描版](http://pan.baidu.com/s/1zpaWY)

### Hadoop

* [Hadoop 2.0基本架构与发展趋势]
* [Hadoop入门实战手册]
* [Hadoop实战-陆嘉恒(高清完整版)].pdf
* [Hadoop开发者入门专刊]
* [Hadoop开发者第一期]
* [Hadoop开发者第二期]
* [hadoop开发者第三期]
* [Hadoop开发者第四期]
* [Hadoop权威指南(第2版)]
* [为何Hadoop是分布式大数据处理的未来]

### MongoDB

* [MongoDB_实践]
* [MongoDB基础教程]
* [MongoDB开发使用手册]
* [MongoDB开发应用实践_潘凡]
* [MongoDB权威指南]
* [10 Key Performance Indicators for MongoDB]
* [u dont know mongodb]
* [MongoDB.in.Action(2011.12).Kyle.Banker.文字版]
* [O'Reilly:深入学习MongoDB(霍多罗夫).巨成等.扫描版]

## 软件工程

* [97+Things+Every+Programmer+Should+Know]
* [Google的C++编码规范 中文]
* [人月神话20周年纪念版--中文版]
* [代码大全(第二版,中文版)]
* [代码整洁之道-完整版]
* [修改代码的艺术]
* [当析构函数遇到多线程--C++中线程安全的对象回调]
* [敏捷软件开发:原则/模式与实践]
* [程序员修炼之道-从小工到专家]
* [程序员的自我修养_链接/装载与库]
* [编码__隐匿在计算机软硬件背后的语言]
* [编程匠艺:编写卓越的代码(第二版)(奋斗的小鸟)]
* [计算机程序的构造和解释中文版]
* [设计模式-可复用面向对象软件的基础]
* [软件架构的艺术]
* [重构-改善既有代码的设计 中文版]
* [高效程序员的45个习惯:敏捷开发修炼之道]
* [黑客与画家]

## Linux

* [Bash 新手指南 ]
* [高级Bash脚本编程指南]
* [LINUX UNIX设计思想]
* [LINUX内核设计与实现(第二版)].pdf
* [L]inux常用命令.cpp
* [LINUX常用命令]
* [Linux程序设计(Begin Linux Programming)第]四版源码.zip
* [Linux系统案例精解]
* [Linux网络编程]
* [UNIX编程艺术中文版]
* [Linux网络编程-宋敬彬-孙海滨]
* [鸟哥的Linux私房菜_基础学习篇(第三版)].pdf
* [鸟哥的Linux私房菜_服务器架设篇(第三版)].pdf

## 大数据

* [大数据:互联网大规模数据挖掘与分布式处理]
* [谁说菜鸟不会数据分析  入门篇]

## 算法

* [Algorithms and Data Structures]
* [数据结构算法与应用]
* [算法导论]

## 面试资料

* [程序员面试题精选100题]
* [程序员面试宝典(第三版)]
* [剑指offer 名企面试官精讲典型编程题]

## 闲读

* [MacTalk`人生元编程(池建强)]
* [图灵的秘密  他的生平/思想及论文解读]
* [我编程,我快乐:程序员职业规划之道]
* [数学之美]
* [浪潮之巅]
* [淘宝技术这十年,完整最终确认版]
* [程序员的职业素养]

## 版本管理

* [Git Internals-eng]
* [Pro Git - eng]
* [Pro Git - 中文版]
* [git - 简易指南](http://rogerdudler.github.io/git-guide/index.zh.html)
* [Git 参考手册](http://gitref.justjavac.com)
* [Pro Git](http://git-scm.com/book/zh)
* [Git Magic](http://www-cs-students.stanford.edu/~blynn/gitmagic/intl/zh_cn/)
* [GotGitHub](http://www.worldhello.net/gotgithub/index.html)
* [Git Community Book 中文版](http://gitbook.liuhui998.com/index.html)
* [Mercurial 使用教程](http://mercurial.selenic.com/wiki/ChineseTutorial)
* [HgInit (中文版)](http://bucunzai.net/hginit/)

《C++新经典:对象模型》