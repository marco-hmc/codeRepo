# 自学CS顺序以及书单推荐

> marco

[toc]

* 一般建议先学计算机架构再学操作系统或数据库，先学计算机网络和操作系统再学分布式系统。
* 推荐学习_《深入理解计算机系统》_ 和 _《数据密集型应用系统设计》_

| 科目                                      | 为何要学？                                                   | 最佳书籍                                                     | 最佳视频                          |
| ----------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------------------------- |
| **[编程](#编程)**                         | 不要做一个“永远没彻底搞懂”诸如递归等概念的程序员。           | _[《计算机程序的构造和解释》](https://book.douban.com/subject/1148282/)_ | 着重学习前三章                    |
| **[计算机架构](#计算机架构)**             | 如果你对于计算机如何工作没有具体的概念，那么你所做出的所有高级抽象都是空中楼阁。 | _[《深入理解计算机系统》](https://book.douban.com/subject/26912767/)_ | 着重学习前六章                    |
| **[算法与数据结构](#算法和数据结构)**     | 如果你不懂得如何使用栈、队列、树、图等常见数据结构，遇到有难度的问题时，你将束手无策。 | _[《算法设计手册》](https://book.douban.com/subject/4048566/)_ | Steven Skiena’s lectures          |
| **[数学知识](#数学知识)**                 | 计算机科学基本上是应用数学的一个“跑偏的”分支，因此学习数学将会给你带来竞争优势。 | _[《计算机科学中的数学》](https://book.douban.com/subject/33396340/)_ | Tom Leighton’s MIT 6.042J         |
| **[操作系统](#操作系统)**                 | 你所写的代码，基本上都由操作系统来运行，因此你应当了解其运作的原理。 | _[《操作系统导论》](https://book.douban.com/subject/33463930/)_ | Berkeley CS 162                   |
| **[计算机网络](#计算机网络)**             | 互联网已然势不可挡：理解工作原理才能解锁全部潜力。           | _[《计算机网络：自顶向下方法》](https://book.douban.com/subject/30280001/)_ | Stanford CS 144                   |
| **[数据库](#数据库)**                     | 对于多数重要程序，数据是其核心，然而很少人理解数据库系统的工作原理。 | _[《Readings in Database Systems》](https://book.douban.com/subject/2256069/) （暂无中译本）_ | Joe Hellerstein’s Berkeley CS 186 |
| **[编程语言与编译器](#编程语言与编译器)** | 若你懂得编程语言和编译器如何工作，你就能写出更好的代码，更轻松地学习新的编程语言。 | _[《Crafting Interpreters》](https://craftinginterpreters.com/)_ | Alex Aiken’s course on Lagunita   |
| **[分布式系统](#分布式系统)**             | 如今，_多数_ 系统都是分布式的。                              | _[《数据密集型应用系统设计》](https://book.douban.com/subject/30329536/)_ | MIT 6.824                         |

## 1. 指引

### 1.1 编程

大多数计算机专业本科教学以程序设计“导论”作为开始。这类课程的最佳版本不仅能满足初学者的需要，还适用于那些在初学编程阶段遗漏了某些有益的概念和程序设计模式的人。

对于这部分内容，我们的标准推荐是这部经典著作：[《计算机程序的构造和解释》](https://book.douban.com/subject/1148282/)。

我们建议至少学完SICP的前三章，并完成配套的习题。如果需要额外的练习，可以去解决一些小的程序设计问题，比如[exercism](http://exercism.io)。

> **中文翻译新增：**  
>
> * 关于SICP国内视频观看地址  
>   * [MIT的免费视频课程（中英字幕）](https://www.bilibili.com/video/av8515129/)  
>   * [Brian Harvey 开设的 SICP 课程（英文字幕）](https://www.bilibili.com/video/av40460492/)  
> * Scheme 学习的相关资源参见：<https://github.com/DeathKing/Learning-SICP>  
> * 更详细的补充说明：[#3](https://github.com/keithnull/TeachYourselfCS-CN/issues/3)  

为什么这么要学SICP？因为 SICP 是独一无二的，它可以——至少很有可能——改变你对计算机和编程的基本认识。不是每个人都有这样的体验。有的人讨厌这本书，有的人看了前几页就放弃了。但潜在的回报让它值得一读。

如果你觉得SICP过于难，试试 _《Composing Programs》_。如果还是不合适，那我们推荐 _《程序设计方法》（[中文版](https://book.douban.com/subject/1140942/)，[英文版](http://www.htdp.org/)）_ ；如果你觉得SICP过于简单，那我们推荐 _[《Concepts, Techniques, and Models of Computer Programming》](https://book.douban.com/subject/1782316/)_ 。如果读这些书让你觉得没有收获，也行你应该先学习其他科目，一两年后再重新审视编程的理念。

> 新版原文删除了对 _《Concepts, Techniques, and Models of Computer Programming》_ 一书的推荐，但这本书对各种编程模型有深入的见解，值得一读。所以译文中依然保留。
> — 译者注

[![计算机程序的构造和解释](.自学CS顺序以及书单.asserts/66758473-ef7bff80-eed0-11e9-944a-15ae5c8542ca.jpg)](https://book.douban.com/subject/1148282/) 

### 1.2 计算机架构

计算机架构——有时候又被称为“计算机系统”或者“计算机组成”——是了解软件底层的的重要视角。根据我们的经验，这是自学的软件工程师最容易忽视的领域。

我们最喜欢的入门书是 _[《深入理解计算机系统》](https://book.douban.com/subject/26912767/)_。典型的[计算机体系结构导论课程](http://csapp.cs.cmu.edu/3e/courses.html)会涵盖本书的 1 - 6 章。

我们喜爱《深入理解计算机系统》，因为它的实用性，并且站在程序员的视角。虽然计算机体系结构的内容比本书所涉及的内容多得多，但对于那些想了解计算机系统以求编写更快、更高效、更可靠的软件的人来说，这本书是很好的起点。

对于那些既想了解这个主题又想兼顾硬件和软件的知识的人来说，我们推荐 _[《计算机系统要素》](https://book.douban.com/subject/1998341/)_，又名“从与非门到俄罗斯方块”（“Nand2Tetris”），这本书规模宏大，让读者对计算机内的所有部分如何协同工作有完全的认识。这本书的每一章节对应如何构建计算机整体系统中的一小部分，从用HDL（硬件描述语言）写基本的逻辑门电路出发，途经CPU和汇编，最终抵达诸如俄罗斯方块这般规模的应用程序。

我们推荐把此书的前六章读完，并完成对应的项目练习。这么做，你将更加深入地理解，计算机架构和运行其上的软件之间的关系。

[![深入理解计算机系统](.自学CS顺序以及书单.asserts/82109944-12270d00-976d-11ea-85a9-774e4f762ec9.png)](https://book.douban.com/subject/26912767/) [![计算机系统要素](.自学CS顺序以及书单.asserts/66758695-60231c00-eed1-11e9-8422-a4acfb10a390.jpg)](http://www.nand2tetris.org) 

### 算法与数据结构

关于算法与数据结构，有成百上千的书可供使用，但是我们的最爱是Steven Skiena编写的 _[《算法设计手册》](https://book.douban.com/subject/4048566/)_。显而易见，他对此充满热爱，迫不及待地想要帮助其他人理解。

最后，我们强烈推荐 _[《怎样解题》](https://book.douban.com/subject/2124114/)_。这本书极为优秀且独特，指导人们解决广义上的问题，因而一如其适用于数学，它适用于计算机科学。

[![算法设计手册](.自学CS顺序以及书单.asserts/66759121-361e2980-eed2-11e9-913c-8fc48c67122a.jpg)](https://book.douban.com/subject/4048566/) [![怎样解题](.自学CS顺序以及书单.asserts/66759282-8e552b80-eed2-11e9-89de-16b1f8d82e78.jpg)](https://book.douban.com/subject/2124114/) 

> 我可以广泛推荐的方法只有一个： 写之前先思考。
>
> — Richard Hamming

### 1.3 数学知识

对于计算机科学，数学中最相关的领域是“离散数学”，其中的“离散”与“连续”相对立，大致上指的是应用数学中那些有趣的主题，而不是微积分之类的。由于定义比较含糊，试图掌握离散数学的全部内容是没有意义的。较为现实的学习目标是，了解逻辑、排列组合、概率论、集合论、图论以及密码学相关的一些数论知识。考虑到线性代数在计算机图形学和机器学习中的重要性，该领域同样值得学习。

对于更加高阶的学习，我们推荐 _[《计算机科学中的数学》](https://book.douban.com/subject/33396340/)_，MIT同名课程的课程笔记，篇幅与书籍相当（事实上，现已出版）。这门课程的视频同样[可免费获得](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-042j-mathematics-for-computer-science-fall-2010/video-lectures/)，是我们所推荐的学习视频。

[![计算机科学中的数学](.自学CS顺序以及书单.asserts/66759673-4387e380-eed3-11e9-8469-3e677d108e91.jpg)](https://book.douban.com/subject/33396340/) 

### 1.4 操作系统

_[《操作系统概念》](https://book.douban.com/subject/30297919/)_ （“恐龙书”）和 _[《现代操作系统》](https://book.douban.com/subject/27096665/)_ 是操作系统领域的经典书籍。二者都因为写作风格和对学生不友好而招致了一些批评。

_[《操作系统导论》（Operating Systems: Three Easy Pieces）](https://book.douban.com/subject/33463930/)_ 是一个不错的替代品，并且[可在网上免费获得（英文版）](http://pages.cs.wisc.edu/~remzi/OSTEP/)。我们格外喜欢这本书的结构，并且认为这本书的习题很值得一做。

在读完《操作系统导论》后，我们鼓励你探索特定操作系统的设计。可以借助“{OS name} Internals”风格的书籍，比如 _[Lion's commentary on Unix](https://www.amazon.com/Lions-Commentary-Unix-John/dp/1573980137/)_， _[The Design and Implementation of the FreeBSD Operating System](https://www.amazon.com/Design-Implementation-FreeBSD-Operating-System/dp/0321968972/)_，以及 _[Mac OS X Internals](https://www.amazon.com/Mac-OS-Internals-Systems-Approach/dp/0321278542/)_。对于 Linux ，我们推荐 Robert Love 的 _[《Linux内核设计与实现》](https://book.douban.com/subject/6097773/)_。

为了巩固对操作系统的理解，阅读小型系统内核的代码并且为其增加特性是一个很不错的方法。比如，[xv6](https://pdos.csail.mit.edu/6.828/2016/xv6.html)，由MIT的一门课程所维护的从Unix V6到ANSI C和x86的移植，就是一个很棒的选择。《操作系统导论》有一个附录，记载了一些可能的[xv6实验项目](http://pages.cs.wisc.edu/~remzi/OSTEP/lab-projects-xv6.pdf)，其中充满了关于潜在项目的很棒想法。

[![操作系统导论](.自学CS顺序以及书单.asserts/66759780-78943600-eed3-11e9-8eb5-6472c318c265.jpg)](https://book.douban.com/subject/33463930/) 

### 1.5 计算机网络

鉴于有那么多关于网络服务端和客户端的软件工程，计算机网络是计算机科学中价值最为“立竿见影”的领域之一。我们的学生，系统性地学习了计算机网络，最终能够理解那些曾困扰他们多年的术语、概念和协议。

在这一主题上，我们最爱的书籍是 _[《计算机网络：自顶向下方法》](https://book.douban.com/subject/30280001/)_。书中的小项目和习题相当值得练习，尤其是其中的“Wireshark labs”（[这部分在网上可以获得](http://www-net.cs.umass.edu/wireshark-labs/)）。

对于计算机网络的学习，做项目比完成小的习题更有益。一些可能的项目有：HTTP服务器，基于UDP的聊天APP，[迷你TCP栈](http://jvns.ca/blog/2014/08/12/what-happens-if-you-write-a-tcp-stack-in-python/)，代理，负载均衡器，或者分布式哈希表。

[![《计算机网络：自顶向下方法》](.自学CS顺序以及书单.asserts/66760004-d9bc0980-eed3-11e9-9b3f-74bf54b9571f.jpg)](https://book.douban.com/subject/30280001/) 

> 你无法盯着水晶球预见未来，未来的互联网何去何从取决于社会。
>
> — Bob Kahn

### 1.6 数据库

比起其他主题，自学数据库系统需要更多的付出。这是一个相对年轻的研究领域，并且出于很强的商业动机，研究者把想法藏在紧闭的门后。此外，许多原本有潜力写出优秀教材的作者反而选择了加入或创立公司。

鉴于如上情况，我们鼓励自学者大体上抛弃教材，而是从[2015年春季学期的CS 186课程](https://archive.org/details/UCBerkeley_Course_Computer_Science_186)（Joe Hellerstein在Berkeley的数据库课程）开始，然后前往阅读论文。

对于初学者，有一篇格外值得提及的论文：“[Architecture of a Database System](http://db.cs.berkeley.edu/papers/fntdb07-architecture.pdf)”。这篇论文提供了独特的对关系型数据库管理系统（RDBMS）如何工作的高层次观点，是后续学习的实用梗概。

_[《Readings in Database Systems》](https://book.douban.com/subject/2256069/)_，或者以[数据库“红书”](http://www.redbook.io/)更为人知，是由Peter Bailis，Joe Hellerstein和Michael Stonebraker编纂的论文合集。对于那些想要在CS 186课程的水平更进一步的学习者，“红书”应当是下一步。

如果你坚持一定要一本导论教材，那我们推荐Ramakrishnan和Gehrke所著的 _[《数据库管理系统：原理与设计》](https://book.douban.com/subject/1155934/)_。如需更深一步，Jim Gray的经典著作 _[《Transaction Processing: Concepts and Techniques》](https://book.douban.com/subject/2586390/)_ 值得一读，不过我们不建议把这本书当作首要资源。

如果没有编写足够数量的代码，很难巩固数据库理论。CS 186课程的学生给Spark添加特性，倒是不错的项目，不过我们仅仅建议从零实现一个简单的关系型数据库管理系统。自然，它将不会有太多的特性，但是即便只实现典型的关系型数据库管理系统每个方面最基础的功能，也是相当有启发的。

最后，数据模型往往是数据库中一个被忽视的、教学不充分的方面。关于这个主题，我们推荐的书籍是 _[Data and Reality: A Timeless Perspective on Perceiving and Managing Information in Our Imprecise World](https://book.douban.com/subject/17915870/)_。

[![Readings in Database Systems](.自学CS顺序以及书单.asserts/66760126-08d27b00-eed4-11e9-82c6-46c571036aa1.jpg)](https://book.douban.com/subject/2256069/) [![数据库管理系统：原理与设计](.自学CS顺序以及书单.asserts/66760358-85655980-eed4-11e9-9130-66d2ecea5700.jpg)](https://book.douban.com/subject/1155934/) 

### 1.7 编程语言与编译器

另一本更为传统的推荐书籍是 _[《编译原理》](https://book.douban.com/subject/3296317/)_，通常称为“龙书”。不幸的是，这本书不是为自学者而设计的，而是供教师从中挑选一些主题用于1-2学期的教学。

如果你选择使用龙书进行自学，你需要从中甄选主题，而且最好是在导师的帮助下。我们建议依据某个视频课程来设定学习的结构，然后按需从龙书中获取深入的内容。我们推荐的在线课程是[Alex Aiken在MOOC平台 edX 所开设的](https://www.edx.org/course/compilers)。

[![编译原理](.自学CS顺序以及书单.asserts/66760486-ca898b80-eed4-11e9-80ba-df298ac8d5da.jpg)](https://book.douban.com/subject/3296317/) 

### 1.8 分布式系统

随着计算机在数量上的增加，计算机同样开始 _分散_。尽管商业公司过去愿意购买越来越大的大型机，现在的典型情况是，甚至很小的应用程序都同时在多台机器上运行。思考这样做的利弊权衡，即是分布式系统的研究所在，也是越来越重要的一项技能。

我们推荐的自学参考书是 Martin Kleppmann 的 _[《数据密集型应用系统设计》](https://book.douban.com/subject/30329536/)_。与传统的教科书相比，它是一本为实践者设计的具有很高的可读性的书，并且保持了深度和严谨性。

对于那些偏爱传统教材，或者希望可以从网上免费获取的人，我们推荐的教材是Maarten van Steen和Andrew Tanenbaum所著的 _《分布式系统原理与范型》（[中文第二版](https://book.douban.com/subject/3108801/)，[英文第三版](https://book.douban.com/subject/26979326/)）_。



[![数据密集型应用系统设计](.自学CS顺序以及书单.asserts/82111034-94ff9600-9774-11ea-9d49-90b00f746659.png)](https://book.douban.com/subject/30329536/) 



## 2. 附录

### 2.1 经典书推荐

#### 1.1 SICP

我们建议至少学完SICP的前三章，并完成配套的习题。

SICP，即计算机程序的构造和解释。因为 SICP 是独一无二的，它可以——至少很有可能——改变你对计算机和编程的基本认识。不是每个人都有这样的体验。有的人讨厌这本书，有的人看了前几页就放弃了。但潜在的回报让它值得一读。

如果你觉得SICP过于难，试试 _《Composing Programs》_。如果还是不合适，那我们推荐 _《程序设计方法》（[中文版](https://book.douban.com/subject/1140942/)，[英文版](http://www.htdp.org/)）_ ；如果你觉得SICP过于简单，那我们推荐 

#### 2.2 龙书

龙书，即编译原理，依旧是内容最为完整的编译器单本书籍。由于过分强调一些如今不够时新的主题的细节，比如解析，这本书招致了恶评。然而事实上，这本书从未打算供人一页一页的学习，而仅仅是为了给教师准备一门课程提供足够的材料。类似地，自学者可以从书中量身按需挑选主题，或者最好依照公开课授课教师在课程大纲中的建议。



## 科普类

### 1. 代码大全

构建之法

软件调试

head first java

**Java并发编程实战**

**大话设计模式**

高性能mySQL

Wireshark网络分析就这么简单

哥德尔·艾舍尔·巴赫：集异璧之大成

穿越计算机的迷雾

《黑客与画家》

码农翻身

逻辑的引擎

