https://github.com/elohim-meth/rtti
Windows核心编程

给一个内存碎片概念的章节目录，或者结构图。能够囊括主要知识点和内容
https://www.bilibili.com/video/BV1j8cLeaELc/?spm_id_from=333.1007.tianma.1-2-2.click&vd_source=8215bf938da2fb524fa6ffc652bb3c53

## 1. spring festival task

* task: cmake-template
  * purpose: Enhance C ++ engineering construction capabilities
  * date: 0128
  * procedure
    * simple-project
    * ctest
    * thirdParty
    * vs-debug
    * lldb-debug

* task: cs144
  * purpose: To get a comprehensive understanding of network.
  * date: 0128-
  * procedure
    * lab1-2
    * lab3
    * lab4
    * lab5

* task: re-start blog
  * purpose: for cv.
  * date: 
  * procedure:
    * study-notes: 
      * network
      * os
      * cpp
        * grammar
        * multithread
        * std
        * functionalProgramming
        * template
      * thirdParty
        * openmp

* task: new job
  * purpose: 
  * date: 
  * procedure
    * update-cv
    * update-blog
    * lab3

* optional
  * threadPool
  * memoryPool
  * simple: dataBase
  * operator optimize


## 1. doing
  * vs工程
    - debug
    - https://github.com/cpp-best-practices/cmake_template
    - 整一个cmake-template，能够支持vs，支持vsc
    - vsc能够使用llvm-debugger
  * 3D笔记
  * csapp
  * mps:
    * memory-notes
  * 内存笔记
  * 单测笔记
  * 买衣服
  * 画图
    * graphViz
    * plantUml
      https://plantuml.com/zh/
  * threadPool:
  * notes:
    * qt子事件循环
  * **project**
    * memoryPoolSystem
      * https://memory-pool-system.readthedocs.io/en/latest/
    * dataStructure
      * AVL树
      * b树
    * hashTable
    * otSumbit_python
    * OS-project-csapp
      * https://hansimov.gitbook.io/csapp/part1/ch04-processor-architecture
      * https://github.com/CDDSCLab/training-plan?tab=readme-ov-file
    * network-project
      * https://github.com/rkimball/tinytcp
      * cs144
      * chatRoom
    * vs code-plugin
      可以实现将词汇自动粘贴到某个给定路径,自己用来背单词用.
    * opengl
    * spdlog
      * https://zhuanlan.zhihu.com/p/674073158
      * https://www.cnblogs.com/shuqin/p/12214439.html
      * https://zsyyblog.com/3b9abd4f.html
    * game
      * tetris-AI-server-clint
    - [downDemo github](https://github.com/downdemo?tab=repositories)

## c++ todo notes
### 1. 语言特性

- **结构化绑定及其手搓**：C++17 引入的特性，用于解构对象。
- **具名要求**：C++20 中的 concept 特性，用于定义类型要求。
- **迭代器 trait**：用于描述迭代器的特性。
- **值类别**：包括左右值、泛左值（glvalue）、纯右值（prvalue）等。
- **移动语义**：C++11 引入的特性，用于优化资源管理。
- **转发引用（俗称万能引用）**：C++11 引入的特性，用于完美转发。
- **std::forward<T>() 完美转发**：用于实现完美转发的标准库函数。
- **表达式求值**：包括弃值表达式、不求值表达式、潜在求值表达式、常量表达式等。
- **临时量实质化（C++17）**：C++17 引入的特性，用于延长临时对象的生命周期。
- **标准布局类**：符合特定布局规则的类。
- **用户定义字面量**：C++11 引入的特性，用于定义自定义的字面量。
- **构造函数异常处理**：处理构造函数中抛出的异常。
- **函数 try 块**：用于捕获函数中的异常。
- **模块**：C++20 引入的特性，用于模块化代码。
- **全局模块片段及其存在的意义**：C++20 引入的特性，用于定义全局模块片段。
- **模块分区**：C++20 引入的特性，用于分割模块。
- **在 CMake 工程中声明模块范围库**：在 CMake 中使用模块的方式。
- **requires 子句**：C++20 引入的特性，用于定义模板的约束。
- **约束的归入（subsume）**：C++20 中的 concept 特性，用于约束的归入。
- **约束的偏序**：C++20 中的 concept 特性，用于定义约束的偏序。
- **concept**：C++20 引入的特性，用于定义类型要求。
- **原子约束**：C++20 中的 concept 特性，用于定义原子约束。
- **约束规范化过程**：C++20 中的 concept 特性，用于规范化约束。
- **协程**：C++20 引入的特性，用于实现协程。
- **协程 promise_type**：协程的 promise 类型。
- **挂起点**：协程中的挂起点。
- **等待体**：协程中的等待体。
- **协程抛异常**：协程中的异常处理。
- **显式对象形参（C++23）**：C++23 引入的特性，用于显式指定对象形参。

### 2. 范围库（Ranges Library）

- **范围适配器**：C++20 引入的特性，用于适配范围。
- **范围工厂**：用于创建范围的工厂函数。
- **视图**：C++20 引入的特性，用于表示范围的视图。
- **老式迭代器对和新式迭代器+哨位概念的对比**：比较传统迭代器对和新的迭代器+哨位概念。
- **范围生成器**：用于生成范围的生成器函数。
- **范围库中常用的 concept**：范围库中常用的概念，如可间接写入、可间接读取等。

### 3. 元编程

- **用元编程实现 constexpr 编译期算法**：使用元编程实现编译期算法，如编译期汉诺塔、编译期递归、拼接字符数组、打函数表等。
- **奇特重现模板模式（CRTP）以及其在 C++20 范围适配器中的应用概念库**：CRTP 模式及其在范围适配器中的应用。
- C++17 的 CTAD 语法 

### 4. 格式化

- **格式化器特化**：自定义格式化器的特化。
- **基本格式化器**：标准库中的基本格式化器。
- **格式串格式**：格式化字符串的格式。

### 5. 其他

- **可变仿引用对象的 operator= 成员必须带 const 限定的依据**：解释为什么可变仿引用对象的赋值运算符成员必须带 const 限定。

#### 1. ELF 文件的节结构

- **ELF 文件**：Executable and Linkable Format 文件，是一种标准的文件格式，用于可执行文件、目标代码、共享库等。
- **节结构**：ELF 文件由多个节（Section）组成，每个节包含不同类型的数据，如代码段、数据段、符号表等。
- **映射到进程地址空间**：
  - **代码段（.text）**：包含可执行代码，映射到进程的代码段。
  - **数据段（.data）**：包含已初始化的全局变量和静态变量，映射到进程的数据段。
  - **未初始化数据段（.bss）**：包含未初始化的全局变量和静态变量，映射到进程的 BSS 段。
  - **只读数据段（.rodata）**：包含只读数据，如字符串常量，映射到进程的只读数据段。

#### 2. 全局变量和静态变量的存储位置

- **全局变量**：存储在数据段（.data）或 BSS 段（.bss）。
- **静态变量**：与全局变量类似，存储在数据段（.data）或 BSS 段（.bss）。

#### 4. 栈的结构和细节

- **函数参数入栈顺序**：通常从右到左入栈。
- **函数局部变量在栈中的布局**：局部变量在栈帧中按声明顺序分配。
- **栈帧指针（Frame Pointer, FP）**：指向当前栈帧的起始位置。
- **栈顶指针（Stack Pointer, SP）**：指向当前栈顶位置。

#### 5. 常见的函数调用约定

- **cdecl**：C 语言默认调用约定，参数从右到左入栈，调用者清理栈。
- **stdcall**：Windows API 调用约定，参数从右到左入栈，调用者清理栈。
- **thiscall**：C++ 成员函数调用约定，`this` 指针作为隐藏参数传递。
- **fastcall**：使用寄存器传递参数，提高调用效率。

#### 6. 操作系统的保护模式和实模式

- **保护模式**：提供内存保护、多任务和虚拟内存等功能，现代操作系统常用。
- **实模式**：早期 x86 处理器的工作模式，直接访问物理内存，无内存保护。

#### 7. 中断向量表

- **中断向量表**：存储中断处理程序入口地址的表，每个中断类型对应一个入口地址。

#### 8. Linux 下的 CAS（Compare-And-Swap）

- **CAS**：一种原子操作，用于实现无锁并发数据结构，比较并交换内存中的值。

#### 9. Daemon 进程和僵尸进程

- **Daemon 进程**：后台运行的服务进程，无控制终端。
  - **产生方法**：通过 `fork` 创建子进程，父进程退出，子进程成为 Daemon 进程。

- **僵尸进程**：子进程退出后，父进程未调用 `wait` 系统调用回收子进程资源。
  - **消除方法**：父进程调用 `wait` 系统调用回收子进程资源。


### 其他技术领域

#### 1. 图形学
- **图形学**：研究计算机生成和处理图像的技术，包括渲染、光照、纹理映射等。

#### 2. 游戏服务器
- **游戏服务器**：支持多人在线游戏的服务器，处理游戏逻辑、玩家交互、数据存储等。

#### 3. 网络通讯架构
- **网络通讯架构**：设计和实现网络通信的结构，包括协议、数据传输、网络安全等。

#### 4. 虚拟现实
- **虚拟现实**：通过计算机技术生成逼真的虚拟环境，用户可以通过视觉、听觉、触觉等感官与虚拟环境交互。

#### 5. 嵌入式系统
- **嵌入式系统**：专用计算机系统，嵌入到设备中执行特定任务，如家电、汽车、工业控制等。

#### 6. 设备驱动
- **设备驱动**：操作系统与硬件设备之间的接口，负责设备的初始化、数据传输、控制等。

#### 7. 音频视频
- **音频视频**：处理和传输音频、视频数据的技术，包括编码、解码、压缩、传输等。

#### 8. AI 底层
- **AI 底层**：人工智能技术的基础，包括机器学习算法、神经网络、数据处理等。

### 参考书籍

- 《程序员的自我修养：链接、装载与库》：涵盖操作系统、编译原理、链接和装载等方面的知识，是程序员必读书籍。

### 面试问题示例

1. **操作系统原理**：
   - 请解释 Linux 下 ELF 文件的节结构，映射到进程地址空间后分别对应哪些段？
   - 全局变量和静态变量存储在进程地址空间的哪里？
   - 请解释堆和栈的区别，以及栈的结构和细节。
   - 请解释 cdecl、stdcall、thiscall、fastcall 的区别。

2. **数据结构与算法**：
   - 请编写一个从 1 加到 100 的求和函数，并写出该函数的汇编代码。
   - 请编写哈希表插入元素的算法，元素类型是任意类型。

3. **其他技术领域**：
   - 请解释什么是 Daemon 进程，如何产生 Daemon 进程？
   - 请解释僵尸进程的产生和消除方法。
   - 请解释图形学的基本概念和算法。
   - 请解释游戏服务器的架构和实现。
   - 请解释网络通讯的基本原理和架构设计。
   - 请解释虚拟现实的基本概念和实现技术。
   - 请解释嵌入式系统的基本原理和开发方法。
   - 请解释设备驱动的开发和调试方法。
   - 请解释音频视频的处理和编解码技术。
   - 请解释 AI 底层的算法和实现。

山那边的人-海这边的人