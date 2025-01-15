# Table of contents

* [本电子书信息](README.md)

## 本书概述

* **第2章：信息的表示和处理。** 我们讲述了计算机的算术运算，重点描述了会对程序员有 影响的无符号数和数的补码表示的特性。我们考虑数字是如何表示的，以及由此确定对于一个给定的字长，其可能编码值的范围。我们探讨有符号和无符号数字之间类型转换的效果，还阐述算术运算的数学特性。菜鸟级程序员经常很惊奇地了解到（用补码表示的）两个正数的和或者积可能为负。另一方面，补码的算术运算满足很多整数运算的代数特性，因此，编译器可以很安全地把一个常量乘法转化为一系列的移位和加法。我们用C 语言的位级操作来说明布尔代数的原理和应用。我们从两个方面讲述了 IEEE 标准的浮点格式：一是如何用它来表示数值，一是浮点运算的数学属性。

  对计算机的算术运算有深刻的理解是写出可靠程序的关键。比如，程序员和编译器不能用表达式（x-y&lt;0）来替代（x&lt;y），因为前者可能会产生溢出。甚至也不能用表达式（-y&lt;-x）来替代，因为在补码表示中负数和正数的范围是不对称的。算术溢出是造成程序错误和安全漏洞的一个常见根源，然而很少有书从程序员的角度来讲述计算机算术运算的特性。

* **第3章：程序的机器级表示。** 我们教读者如何阅读由 C 编译器生成的 x86-64 机器代码。我们说明为不同控制结构（比如条件、循环和开关语句）生成的基本指令模式。我们还讲述过程的实现，包括栈分配、寄存器使用惯例和参数传递。我们讨论不同数据结构（如结构、联合和数组）的分配和访问方式。我们还说明实现整数和浮点数算术运算的指令。我们还以分析程序在机器级的样子作为途径，来理解常见的代码安全漏洞（例如缓冲区溢出），以及理解程序员、编译器和操作系统可以采取的减轻这些威胁的措施。学习本章的概念能够帮助读者成为更好的程序员，因为你们懂得程序在机器上是如何表示的。另外一个好处就在于读者会对指针有非常全面而具体的理解。
* **第4章：处理器体系结构。** 这一章讲述基本的组合和时序逻辑元素，并展示这些元素如何在数据通路中组合到一起，来执行 x86-64 指令集的一个称为 “Y86-64” 的简化子集。我们从设计单时钟周期数据通路开始。这个设计概念上非常简单，但是运行速度不会太快。然后我们引入**流水线**的思想，将处理一条指令所需要的不同步骤实现为独立的阶段。这个设计中，在任何时刻，每个阶段都可以处理不同的指令。我们的五阶段处理器流水线更加实用。本章中处理器设计的控制逻辑是用一种称为 HCL 的简单硬件描述语言来描述的。用 HCL 写的硬件设计能够编译和链接到本书提供的模拟器中，还可以根据这些设计生成 Verilog 描述，它适合合成到实际可以运行的硬件上去。
* **第5章：优化程序性能。** 在这一章里，我们介绍了许多提高代码性能的技术，主要思想就是让程序员通过使编译器能够生成更有效的机器代码来学习编写 C 代码。我们一开始介绍的是减少程序需要做的工作的变换，这些是在任何机器上写任何程序时都应该遵循的。然后讲的是增加生成的机器代码中指令级并行度的变换，因而提高了程序在现代“超标量”处理器上的性能。为了解释这些变换行之有效的原理，我们介绍了一个简单的操作模型，它描述了现代乱序处理器是如何工作的，然后给出了如何根据一个程序的图形化表示中的关键路径来测量一个程序可能的性能。你会惊讶于对 C 代码做一些简单的变换能给程序带来多大的速度提升。
* **第6章：存储器层次结构。** 对应用程序员来说，存储器系统是计算机系统中最直接可见的部分之一。到目前为止，读者一直认同这样一个存储器系统概念模型，认为它是一个有一致访问时间的线性数组。实际上，存储器系统是一个由不同容量、造价和访问时间的存储设备组成的层次结构。我们讲述不同类型的随机存取存储器（RAM）和只读存储器（ROM），以及磁盘和✦固态硬盘✦的几何形状和组织构造。我们描述这些存储设备是如何放置在层次结构中的，讲述访问局部性是如何使这种层次结构成为可能的。我们通过一个独特的观点使这些理论具体化，那就是将存储器系统视为一个“存储器山”，山脊是时间局部性，而斜坡是空间局部性。最后，我们向读者阐述如何通过改善程序的时间局部性和空间局部性来提高应用程序的性能。

* **第7章：链接。** 本章讲述静态和动态链接，包括的概念有可重定位的和可执行的目标文件、符号解析、重定位、静态库、共享目标库、位置无关代码，以及库打桩。大多数讲述系统的书中都不讲链接，我们要讲述它是出于以下原因。第一，程序员遇到的最令人迷惑的问题中，有一些和链接时的小故障有关，尤其是对那些大型软件包来说。第二，链接器生成的目标文件是与一些像加载、虚拟内存和内存映射这样的概念相关的。
* **第8章：异常控制流。** 在本书的这个部分，我们通过介绍异常控制流（即除正常分支和过程调用以外的控制流的变化）的一般概念，打破单一程序的模型。我们给出存在于系统所有层次的异常控制流的例子，从底层的硬件异常和中断，到并发进程的上下文切换，到由于接收 Linux 信号引起的控制流突变，到 C 语言中破坏栈原则的非本地跳转。 在这一章，我们介绍进程的基本概念，进程是对一个正在执行的程序的一种抽象。读者会学习进程是如何工作的，以及如何在应用程序中创建和操纵进程。我们会展示应用程序员如何通过 Linux 系统调用来使用多个进程。学完本章之后，读者就能够编写带作业控制的 Linux shell 了。同时，这里也会向读者初步展示程序的并发执行会引起不确定的行为。
* **第9章：虚拟内存。**我们讲述虚拟内存系统是希望读者对它是如何工作的以及它的特性有所了解。我们想让读者了解为什么不同的并发进程各自都有一个完全相同的地址范围，能共享某些页，而又独占另外一些页。我们还讲了一些管理和操纵虚拟内存的问题。特别地，我们讨论了存储分配操作，就像标准库的 malloc 和 free 操作。阐述这些内容是出于下面几个目的。它加强了这样一个概念，那就是虚拟内存空间只是一个字节数组，程序可以把它划分成不同的存储单元。它可以帮助读者理解当程序包含存储泄漏和非法指针引用等内存引用错误时的后果。最后，许多应用程序员编写自己的优化了的存储分配操作来满足应用程序的需要和特性。这一章比其他任何一章都更能展现将计算机系统中的硬件和软件结合起来阐述的优点。而传统的计算机体系结构和操作系统书籍都只讲述虚拟内存的某一方面。
* **第10章：系统级 I/O。** 我们讲述 Unix I/O 的基本概念，例如文件和描述符。我们描述如何共享文件，I/O 重定向是如何工作的，还有如何访问文件的元数据。我们还开发了一个健壮的带缓冲区的 I/O 包，可以正确处理一种称为 short counts 的奇特行为，也就是库函数只读取一部分的输入数据。我们阐述 C 的标准 I/O 库，以及它与 Linux I/O 的关系，重点谈到标准 I/O 的局限性，这些局限性使之不适合网络编程。总的来说，本章的主题是后面两章——网络和并发编程的基础。
* **第11章：网络编程。** 对编程而言，网络是非常有趣的 I/O 设备，它将许多我们前面文中学习的概念（比如进程、信号、字节顺序、内存映射和动态内存分配）联系在一起。网络程序还为下一章的主题——并发，提供了一个很令人信服的上下文。本章只是网络编程的一个很小的部分，使读者能够编写一个简单的 Web 服务器。我们还讲述位于所有网络程序底层的客户端-服务器模型。我们展现了一个程序员对 Internet 的观点，并且教读者如何用套接字接口来编写 Internet 客户端和服务器。最后，我们介绍超文本传输协议（HTTP），并开发了一个简单的迭代式 Web 服务器。
* **第12章：并发编程。** 这一章以 Internet 服务器设计为例介绍了并发编程。我们比较对照了三种编写并发程序的基本机制（进程、I/O多路复用和线程），并且展示如何用它们来建造并发Internet服务器。我们探讨了用 P、V 信号量操作来实现同步、线程安全和可重入、竞争条件以及死锁等的基本原则。对大多数服务器应用来说，写并发代码都是很关键的。我们还讲述了线程级编程的使用方法，用这种方法来表达应用程序中的并行性，使得程序在多核处理器上能执行得更快。使用所有的核解决同一个计算问题需要很小心谨慎地协调并发线程，既要保证正确性，又要争取获得高性能。

## 写给指导教师们∶经过课堂验证的实验练习


* **数据实验。**这个实验要求学生实现简单的逻辑和算术运算函数，但是只能使用一个非常有限的C语言子集。比如，只能用位级操作来计算一个数字的绝对值。这个实验可帮助学生了解C语言数据类型的位级表示，以及数据操作的位级行为。
* **二进制炸弹实验。**二进制炸弹是一个作为目标代码文件提供给学生的程序。运行时，它提示用户输入 6 个不同的字符串。如果其中的任何一个不正确，炸弹就会“爆炸”，打印出一条错误消息，并且在一个打分服务器上记录事件日志。学生必须通过对程序反汇编和逆向工程来测定应该是哪 6 个串，从而解除各自炸弹的雷管。该实验能教会学生理解汇编语言，并且强制他们学习怎样使用调试器。 
* **缓冲区溢出实验。**它要求学生通过利用一个缓冲区溢出漏洞，来修改一个二进制可执行文件的运行时行为。这个实验可教会学生栈的原理，并让他们了解写那种易于遭受缓冲区溢出攻击的代码的危险性。 
* **体系结构实验。**第 4 章的几个家庭作业能够组合成一个实验作业，在实验中，学生修改处理器的 HCL 描述，增加新的指令，修改分支预测策略，或者增加、删除旁路路径和寄存器端口。修改后的处理器能够被模拟，并通过运行自动化测试检测出大多数可能的错误。这个实验使学生能够体验处理器设计中令人激动的部分，而不需要掌握逻辑设计和硬件描述语言的完整知识。 
* **性能实验。**学生必须优化应用程序的核心函数（比如卷积积分或矩阵转置）的性能。这个实验可非常清晰地表明高速缓存的特性，并带给学生低级程序优化的经验。 
* **cache 实验。**这个实验类似于性能实验，学生编写一个通用高速缓存模拟器，并优化小型矩阵转置核心函数，以最小化对模拟的高速缓存的不命中次数。我们使用 Valgrind 为矩阵转置核心函数生成真实的地址访问记录。 
* **shell实验。**学生实现他们自己的带有作业控制的 Unix shell 程序，包括 Ctrl+C和 Ctrl+Z 按键，fg、bg和 jobs 命令。这是学生第一次接触并发，并且让他们对 Unix 的进程控制、信号和信号处理有清晰的了解。 
* **malloc 实验。**学生实现他们自己的 malloc、free 和 realloc（可选）版本。这个实验可让学生们清晰地理解数据的布局和组织，并且要求他们评估时间和空间效率的各种权衡及折中。 
* **代理实验。**实现一个位于浏览器和万维网其他部分之间的并行 Web 代理。这个实验向学生们揭示了 Web 客户端和服务器这样的主题，并且把课程中的许多概念联系起来，比如字节排序、文件 I/O、进程控制、信号、信号处理、内存映射、套接字和并发。学生很高兴能够看到他们的程序在真实的 Web 浏览器和 Web 服务器之间起到的作用。

CS∶APP的教师手册中有对实验的详细讨论，还有关于下载支持软件的说明。 



## 出版信息 <a id="publish-info"></a>

* [出版者的话](publish-info/publisher-words.md)
* [中文版序一](publish-info/chinese-preface-1.md)
* [中文版序二](publish-info/chinese-preface-2.md)
* [译者序](publish-info/translators-preface.md)
* [前言](publish-info/preface.md)
* [关于作者](publish-info/about-authors.md)

---

* [第 1 章：计算机系统漫游](ch01-a-tour-of-computer-systems/README.md)
  * [1.1 信息就是位 + 上下文](ch01-a-tour-of-computer-systems/1.1.md)
  * [1.2 程序被其他程序翻译成不同的格式](ch01-a-tour-of-computer-systems/1.2.md)
  * [1.3 了解编译系统如何工作是大有益处的](ch01-a-tour-of-computer-systems/1.3.md)
  * [1.4 处理器读并解释储存在内存中的指令](ch01-a-tour-of-computer-systems/1.4.md)
  * [1.5 高速缓存至关重要](ch01-a-tour-of-computer-systems/1.5.md)
  * [1.6 存储设备形成层次结构](ch01-a-tour-of-computer-systems/1.6.md)
  * [1.7 操作系统管理硬件](ch01-a-tour-of-computer-systems/1.7.md)
  * [1.8 系统之间利用网络通信](ch01-a-tour-of-computer-systems/1.8.md)
  * [1.9 重要主题](ch01-a-tour-of-computer-systems/1.9.md)
  * [1.10 小结](ch01-a-tour-of-computer-systems/1.10-xiao-jie.md)

## 第一部分：程序结构和执行 <a id="part1"></a>

* [第 2 章：信息的表示和处理](part1/ch02-representing-and-manipulating-information/README.md)
  * [2.1 信息存储](part1/ch02-representing-and-manipulating-information/2.1-xin-xi-cun-chu.md)
  * [2.2 整数表示](part1/ch02-representing-and-manipulating-information/2.2-zheng-shu-biao-shi.md)
  * [2.3 整数运算](part1/ch02-representing-and-manipulating-information/2.3-zheng-shu-yun-suan.md)
  * [2.4 浮点数](part1/ch02-representing-and-manipulating-information/2.4-fu-dian-shu.md)
  * [2.5 小结](part1/ch02-representing-and-manipulating-information/2.5-xiao-jie.md)
  * [家庭作业](part1/ch02-representing-and-manipulating-information/jia-ting-zuo-ye.md)
* [第 3 章：程序的机器级表示](part1/ch03-machine-level-representing-of-programs/README.md)
  * [3.1 历史观点](part1/ch03-machine-level-representing-of-programs/3.1-a-historial-perspective.md)
  * [3.2 程序编码](part1/ch03-machine-level-representing-of-programs/3.2-program-encodings.md)
  * [3.3 数据格式](part1/ch03-machine-level-representing-of-programs/3.3-data-formats.md)
  * [3.4 访问信息](part1/ch03-machine-level-representing-of-programs/3.4-accessing-information.md)
* [第 4 章：处理器体系结构](part1/ch04-processor-architecture.md)
* [第 5 章：优化程序性能](part1/ch05-optimizing-program-performance.md)
* [第 6 章：存储器层次结构](part1/ch06-the-memory-hierarchy.md)

## 第二部分：在系统上运行程序 <a id="part2"></a>

* [第 7 章：链接](part2/ch07-linking/README.md)
  * [7.1 编译器驱动程序](part2/ch07-linking/7.1-compiler-drviers.md)
  * [7.2 静态链接](part2/ch07-linking/7.2-static-linking.md)
  * [7.3 目标文件](part2/ch07-linking/7.3-object-files.md)
  * [7.4 可重定位目标文件](part2/ch07-linking/7.4-relocatable-object-files.md)
  * [7.5 符号和符号表](part2/ch07-linking/7.5-symbols-and-symbol-tables.md)
  * [7.6 符号解析](part2/ch07-linking/7.6-symbol-resolution.md)
  * [7.7 重定位](part2/ch07-linking/7.7-relocation.md)
  * [7.8 可执行目标文件](part2/ch07-linking/7.8-executable-object-files.md)
  * [7.9 加载可执行目标文件](part2/ch07-linking/7.9-loading-executable-object-files.md)
  * [7.10 动态链接共享库](part2/ch07-linking/7.10-dynamic-linking-with-shared-libraries.md)
  * [7.11 从应用程序中加载和链接共享库](part2/ch07-linking/7.11-loading-and-linking-shared-libraries-from-applications.md)
  * [7.12 位置无关代码](part2/ch07-linking/7.12-position-independent-code.md)
  * [7.13 库打桩机制](part2/ch07-linking/7.13-library-interpositioning.md)
  * [7.14 处理目标文件的工具](part2/ch07-linking/7.14-tools-for-manipulating-object-files.md)
  * [7.15 小结](part2/ch07-linking/7.15-summary.md)
  * [家庭作业](part2/ch07-linking/homework.md)
* [第 8 章：异常控制流](part2/ch08-exceptional-control-flow/README.md)
  * [8.1 异常](part2/ch08-exceptional-control-flow/8.1-exceptions.md)
  * [8.2 进程](part2/ch08-exceptional-control-flow/8.2-processes.md)
  * [8.3 系统调用错误处理](part2/ch08-exceptional-control-flow/8.3-system-call-error-handling.md)
  * [8.4 进程控制](part2/ch08-exceptional-control-flow/8.4-process-control.md)
  * [8.5 信号](part2/ch08-exceptional-control-flow/8.5-signals.md)
  * [8.6 非本地跳转](part2/ch08-exceptional-control-flow/8.6-nonlocal-jumps.md)
  * [8.7 操作进程的工具](part2/ch08-exceptional-control-flow/8.7-tools-for-manipulating-processes.md)
  * [8.8 小结](part2/ch08-exceptional-control-flow/8.8-summary.md)
  * [家庭作业](part2/ch08-exceptional-control-flow/homework.md)
* [第 9 章：虚拟内存](part2/ch09-virtual-memory/README.md)
  * [9.1 物理和虚拟寻址](part2/ch09-virtual-memory/9.1-physical-and-virtual-addressing.md)
  * [9.2 地址空间](part2/ch09-virtual-memory/9.2-address-spaces.md)
  * [9.3 虚拟内存作为缓存的工具](part2/ch09-virtual-memory/9.3-vm-as-a-tool-for-caching.md)
  * [9.4 虚拟内存作为内存管理的工具](part2/ch09-virtual-memory/9.4-vm-as-a-tool-for-memory-management.md)
  * [9.5 虚拟内存作为内存保护的工具](part2/ch09-virtual-memory/9.5-vm-as-a-tool-for-memory-protection.md)
  * [9.6 地址翻译](part2/ch09-virtual-memory/9.6-address-translation.md)
  * [9.7 案例研究：Intel Core i7 / Linux 内存系统](part2/ch09-virtual-memory/9.7-case-study-the-intel-core-i7-linux-memory-system.md)
  * [9.8 内存映射](part2/ch09-virtual-memory/9.8-memory-mapping.md)
  * [9.9 动态内存分配](part2/ch09-virtual-memory/9.9-dynamic-memory-allocation.md)
  * [9.10 垃圾收集](part2/ch09-virtual-memory/9.10-garbage-collection.md)
  * [9.11 C 程序中常见的与内存有关的错误](part2/ch09-virtual-memory/9.11-common-memoory-related-bugs-in-c-programs.md)
  * [9.12 小结](part2/ch09-virtual-memory/9.12-summary.md)
  * [家庭作业](part2/ch09-virtual-memory/homework.md)

## 第三部分：程序间的交互和通信 <a id="part3"></a>

* [第 10 章：系统级 I/O](part3/ch10-system-level-io/README.md)
  * [10.1 Unix I/O](part3/ch10-system-level-io/10.1-unix-io.md)
  * [10.2 文件](part3/ch10-system-level-io/10.2-files.md)
  * [10.3 打开和关闭文件](part3/ch10-system-level-io/10.3-opening-and-closing-files.md)
  * [10.4 读和写文件](part3/ch10-system-level-io/10.4-reading-and-writing-files.md)
  * [10.5 用 RIO 包健壮地读写](part3/ch10-system-level-io/10.5-robust-reading-and-writing-with-the-rio-package.md)
  * [10.6 读取文件元数据](part3/ch10-system-level-io/10.6-reading-file-metadata.md)
  * [10.7 读取目录内容](part3/ch10-system-level-io/10.7-reading-directory-contents.md)
  * [10.8 共享文件](part3/ch10-system-level-io/10.8-sharing-files.md)
  * [10.9 I/O 重定向](part3/ch10-system-level-io/10.9-io-redirection.md)
  * [10.10 标准 I/O](part3/ch10-system-level-io/10.10-standard-io.md)
  * [10.11 综合：我该使用哪些 I/O 函数？](part3/ch10-system-level-io/10.11-putting-it-together-which-io-functions-should-i-use.md)
  * [10.12 小结](part3/ch10-system-level-io/10.12-summary.md)
  * [家庭作业](part3/ch10-system-level-io/homework.md)
* [第 11 章：网络编程](part3/ch11-network-programming/README.md)
  * [11.1 客户端—服务器编程模型](part3/ch11-network-programming/11.1-the-client-server-programming-model.md)
  * [11.2 网络](part3/ch11-network-programming/11.2-networks.md)
  * [11.3 全球 IP 因特网](part3/ch11-network-programming/11.3-the-global-ip-internet.md)
  * [11.4 套接字接口](part3/ch11-network-programming/11.4-the-sockets-interface.md)
  * [11.5 Web 服务器](part3/ch11-network-programming/11.5-web-servers.md)
  * [11.6 综合：TINY Web 服务器](part3/ch11-network-programming/11.6-putting-it-together-the-tiny-web-server.md)
  * [11.7 小结](part3/ch11-network-programming/11.7-summary.md)
  * [家庭作业](part3/ch11-network-programming/homework.md)
* [第 12 章：并发编程](part3/ch12-concurrent-programming/README.md)
  * [12.1 基于进程的并发编程](part3/ch12-concurrent-programming/12.1-concurrent-programming-with-processes.md)
  * [12.2 基于 I/O 多路复用的并发编程](part3/ch12-concurrent-programming/12.2-concurrent-programming-with-io-multiplexing.md)
  * [12.3 基于线程的并发编程](part3/ch12-concurrent-programming/12.3-concurrent-programming-with-threads.md)
  * [12.4 多线程程序中的共享变量](part3/ch12-concurrent-programming/12.4-shared-variables-in-threaded-programs.md)
  * [12.5 用信号量同步线程](part3/ch12-concurrent-programming/12.5-synchronizing-thread-with-semaphores.md)
  * [12.6 使用线程提高并行性](part3/ch12-concurrent-programming/12.6-using-threads-for-parallelism.md)
  * [12.7 其他并发问题](part3/ch12-concurrent-programming/12.7-other-concurrency-issues.md)
  * [12.8 小结](part3/ch12-concurrent-programming/12.8-summary.md)
  * [家庭作业](part3/ch12-concurrent-programming/homework.md)

---

* [附录 A：错误处理](appendix-error-handling.md)
* [参考文献](references.md)

## 实验 <a id="labs"></a>

* [实验总览](labs/labs-overview/README.md)
  * [常见问题](labs/labs-overview/common-problems.md)
* [实验 1：Data Lab](labs/data-lab/README.md)
  * [README（讲师版）](labs/data-lab/readme-instructor.md)
  * [README（学生版）](labs/data-lab/readme-student.md)
  * [Writeup](labs/data-lab/writeup.md)
* [实验 2：Bomb Lab](labs/bomb-lab/README.md)
  * [README（讲师版）](labs/bomb-lab/readme-jiang-shi-ban.md)
  * [Writeup](labs/bomb-lab/writeup.md)
* [实验 3：Attack Lab](labs/attack-lab.md)
* [实验 4：Architechture Lab](labs/arch-lab.md)
* [实验 5：Cache Lab](labs/cache-lab.md)
* [实验 6：Performance Lab](labs/perf-lab.md)
* [实验 7：Shell Lab](labs/shell-lab.md)
* [实验 8：Malloc Lab](labs/malloc-lab.md)
* [实验 9：Proxy Lab](labs/proxy-lab.md)

