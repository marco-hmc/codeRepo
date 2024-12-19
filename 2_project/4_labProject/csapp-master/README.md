# 本电子书信息

个人整理的《深入理解计算机系统》中文电子版（原书第 3 版）与实验材料：[https://hansimov.gitbook.io/csapp/](https://hansimov.gitbook.io/csapp/)

制作者：[**Hansimov**](https://github.com/Hansimov)\*\*\*\*

OCR 支持：WPS PDF

感谢：[**九卿**](https://github.com/taseikyo)

GitHub：[https://github.com/Hansimov/csapp](https://github.com/Hansimov/csapp)

已施工部分：序、前言、第 1、7、8、9、10、11、12 章，全部实验简介，实验 1、2 文档

待施工部分：第 2、3、4、5、6 章，实验 3、4、5、6、7、8、9 文档

{% page-ref page="ch01-a-tour-of-computer-systems/" %}

{% page-ref page="part2/ch07-linking/" %}

{% page-ref page="part2/ch08-exceptional-control-flow/" %}

{% page-ref page="part2/ch09-virtual-memory/" %}

{% page-ref page="part3/ch10-system-level-io/" %}

{% page-ref page="part3/ch11-network-programming/" %}

{% page-ref page="part3/ch12-concurrent-programming/" %}

{% page-ref page="labs/labs-overview/" %}

![深入理解计算机系统 - Computer Systems: A Programmer's Perspective](.gitbook/assets/shen-ru-li-jie-ji-suan-ji-xi-tong-yuan-shu-di-3-ban-.pdf..2020092219095231900.png)

这本教材有四个特点。
第一，涉及面广，覆盖了二进制、汇编、组成、体系结构、操作系统、网络与并发程序设计等计算机系统最重要的方面。
第二，具有相当的深度，本书从程序出发逐步深人到系统领域的重要问题，而非点到为止，学完本书后读者可以很好地理解计算机系统的工作原理。
第三，在过去的教学体系中这本书所涉及的很多内容只能在高年级讲授，而本书通过合理的安排将计算机系统领域最核心的内容巧妙地展现给学生
（例如，不需要掌握逻辑设计与硬件描述语言的完整知识，就可以体验处理器设计）。
第四，本书配备了非常实用、有趣的实验。
例如，模仿硬件仅用位操作完成复杂的运算，
模仿 tracker 和 hacker 去破解密码以及攻击自身的程序，
设计处理器，
实现简单但功能强大的 Shell 和 Proxy 等。

比如，一个 switch 语句是否总是比一系列的 if-else 语句高效得多？一个函数调用的开销有多大？while 循环比 for 循环更有效吗？指针引用比数组索引更有效吗？为什么将循环求和的结果放到一个本地变量中，会比将其放到一个通过引用传递过来的参数中，运行起来快很多呢？为什么我们只是简单地重新排列一下算术表达式中的括号就能让函数运行得更快?？

理解链接时出现的错误。根据我们的经验，一些最令人困扰的程序错误往往都与链接器操作有关，尤其是当你试图构建大型的软件系统时。比如，链接器报告说它无法解析一个引用，这是什么意思？静态变量和全局变量的区别是什么？如果你在不同的 C 文件中定义了名字相同的两个全局变量会发生什么？静态库和动态库的区别是什么？我们在命令行上排列库的顺序有什么影响？最严重的是，为什么有些链接错误直到运行时才会出现？在第 7 章中，你将得到这些问题的答案。

避免安全漏洞。多年来，缓冲区溢出错误是造成大多数网络和 Internet 服务器上安全漏洞的主要原因。存在这些错误是因为很少有程序员能够理解需要限制从不受信任的源接收数据的数量和格式。学习安全编程的第一步就是理解数据和控制信息存储在程序栈上的方式会引起的后果。作为学习汇编语言的一部分，我们将在第 3 章中描述堆栈原理和缓冲区溢出错误。我们还将学习程序员、编译器和操作系统可以用来降低攻击威胁的方法。
