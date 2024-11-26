# 高性能并行编程与优化 - 课件

欢迎光临开源并行课！您将学到现代 C++ 与高性能计算相关知识！
这里用来存放上课用到的 **源代码** 和 **课件** 等。

* 每周六14点开播：https://live.bilibili.com/14248205
* 录播也会上传到：https://space.bilibili.com/263032155

![CC-BY-NC-SA](tools/cc-by-nc-sa.jpg)

# 下载课件

如果你不知道 Git 如何使用，可以点击这里：[一键下载](https://github.com/archibate/course/archive/refs/heads/master.zip)。

# 目录结构

* 01/slides.ppt - 第一课的课件
* 01/01 - 第一课第一小节的代码
* 01/02 - 第一课第二小节的代码
* 02/slides.ppt - 第二课的课件
* 以此类推……

每一小节的代码目录下都有一个 run.sh，里面是编译运行该程序所用的命令。

# 课程大纲

1. 编译器如何自动优化：从汇编角度看C++
1. C++11起的多线程编程：从mutex到无锁并行
1. 并行编程常用框架：OpenMP与Intel TBB
1. 被忽视的访存优化：内存带宽与cpu缓存机制
1. GPU专题：wrap调度，共享内存，barrier
1. 并行算法实战：reduce，scan，矩阵乘法等
1. 存储大规模三维数据的关键：稀疏数据结构
1. 物理仿真实战：邻居搜索表实现pbf流体求解

# 参考资料

- [热心观众整理的学习资料](https://github.com/jiayaozhang/OpenVDB_and_TBB)
- [HackingCpp 图文教程](https://hackingcpp.com/)
- [Performance Analysis and Tuning on Modern CPUs](http://faculty.cs.niu.edu/~winans/notes/patmc.pdf)
- [C++ 并发编程实战](https://www.bookstack.cn/read/Cpp_Concurrency_In_Action/README.md)
- [深入理解计算机原理 (CSAPP)](http://csapp.cs.cmu.edu/)
- [并行体系结构与编程 (CMU 15-418)](https://www.bilibili.com/video/av48153629/)
- [因特尔 TBB 编程指南](https://www.inf.ed.ac.uk/teaching/courses/ppls/TBBtutorial.pdf)
- [实用网站 CppInsights 解构 C++ 语法糖](https://cppinsights.io)
- [实用网站 GodBolt 查看不同编译器生成的汇编](http://godbolt.org)

