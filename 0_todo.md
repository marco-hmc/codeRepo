[toc]
## 1. doing
  1. podcast
  3. gtest
  7. 智能指针实现
     * 为什么弃用unique_ptr
     * weak_ptr是用于解决什么问题的
     * 智能指针的实际使用放啊
  8. 医保卡补办
  9. cmake,qt5怎么用
  10. \2_project\modern-cpp-tutorial-master\book\zh-cn\01-intro.md
  11. C++基于流的undoController
  12. C++的transactionManager
  13. C++的commandDispatcher
  14. 日志库
  15. json解析
  16. chrono库
  17. 多线程
  18. cas和adl
  19. 写一个自动提交加班时长的
  20. gitbook
    https://ganxunzou.gitbooks.io/gitlab-doc/content/gitbook-yu-gitlab-ji-cheng/gitbook-ci-an-zhuang.html
  20. C++中的反射机制
  21. PLM结合电子商务技术与协同技术,将产品开发流程与SCM/CRM/ERP等系
  22. 为什么要引入ObjectID,而不是用指针这种更朴素的做法?
  23. event时间
  24. **红黑树**
  25. **A*寻路/霍夫曼编码**
  26. blog参考
    [GitHub - Veeupup/veeupup.github.io: blog... maybe writing more..](https://github.com/Veeupup/veeupup.github.io)
  28. real-time rendering
  29. 可以参考modern-cpp-tutorial-master组织书
  30. 
     - [Ulrich Drepper. 每位程序员都需要知道的内存知识. 2007](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
  31. [<Effective Modern C++>](https://www.amazon.cn/dp/B016OFO492/ref=sr_1_3?ie=UTF8&qid=1525613457&sr=8-3&keywords=Effective+C%2B%2B)和 [<C++ 风格指南>](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/).
  32. notes
  33. [<Effective Modern C++>](https://www.amazon.cn/dp/B016OFO492/ref=sr_1_3?ie=UTF8&qid=1525613457&sr=8-3&keywords=Effective+C%2B%2B)和 [<C++ 风格指南>](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/).
  34. notes
   * [cppreference](http://en.cppreference.com/w/cpp) - especially useful for finding examples and documentation of new library features.
   * [C++ Rvalue References Explained](http://thbecker.net/articles/rvalue_references/section_01.html) - a great introduction I used to understand rvalue references, perfect forwarding, and move semantics.
   * [clang](http://clang.llvm.org/cxx_status.html) and [gcc](https://gcc.gnu.org/projects/cxx-status.html)'s standards support pages. Also included here are the proposals for language/library features that I used to help find a description of, what it's meant to fix, and some examples.
   * [Compiler explorer](https://godbolt.org/)
   * [Scott Meyers' Effective Modern C++](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996) - highly recommended series of books!
   * [Jason Turner's C++ Weekly](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw) - nice collection of C++-related videos.
   * [What can I do with a moved-from object?](http://stackoverflow.com/questions/7027523/what-can-i-do-with-a-moved-from-object)

--------------------------------------------------------

  1. **refactoring2** 
    1_notes\6_设计模式\refactoring2\ch1.md
  2. **js**
    1_notes\0_frontEnd\js\en.javascript.info-master\1-js\05-data-types\01-primitives-methods\article.md
  3. **Cpp-Templates-2ed-master**
    2_project\Cpp-Templates-2ed-master\Cpp-Templates-2ed-master\docs\01_function_template.md
  4. modern-cpp
    2_project\modern-cpp-tutorial-master\book\zh-cn\00-preface.md
  
##  2. todo
  * **project**
    * OS-project
    * network-project
    * 自己做一个vs code插件,可以实现将词汇自动粘贴到某个给定路径,自己用来背单词用.

  * **内存管理**
    * https://blog.csdn.net/zzxiaozhao/article/details/102527023
    * https://www.tutorialspoint.com/operating_system/index.htm

  * **toBeOrganized**
    * wk document:
      * 整理wukong侧的东西,看看有没有用的. 
      * https://confluence.zwcad.com/pages/viewpage.action?pageId=60719484
      * 整理一些笔记给liujun.

* * **一/多机数据处理**.

  有 10 台机器,每台机器上保存着 10 亿个 64-bit 整数(不一定刚好 10 亿个,可能有上下几千万的浮动),一共约 100 亿个整数(其实一共也就 80GB 数据,不算大,选这个量级是考虑了 VPS 虚拟机的容量,便于实验).编程求出:

  \1. 这些数的平均数.

  \2. 这些数的中位数.

  \3. 出现次数最多的 100 万个数.

  *4. (附加题)对这 100 亿个整数排序,结果顺序存放到这 10 台机器上.

  *5. (附加健壮性要求)你的程序应该能正确应对输入数据的各种分布(均匀/正态/Zipf).

  *6. (附加伸缩性要求)你的程序应该能平滑扩展到更多的机器,支持更大的数据量.比如 20 台机器/一共 200 亿个整数,或者 50 台机器/一共 500 亿个整数.

* **二/N-皇后问题的多机并行求解**.利用多台机器求出 N-皇后问题有多少个解.(注意目前的世界纪录是 N = 26,[A000170 - OEIS](https://link.zhihu.com/?target=http%3A//oeis.org/A000170) )

  \1. 8 皇后问题在单机上的运算时间是毫秒级,有 92 个解,编程实现之.

  \2. 研究 N-皇后问题的并行算法,写一个单机多线程程序,争取达到线性加速比(以 CPU 核数计).再设法将算法扩展到多机并行.

  \3. 用 10 台 8 核的机器(一共 80 个 CPU cores),求解 19-皇后和 20-皇后问题,看看分别需要多少运行时间.你的方案能否平滑扩展到更多的机器?

  *4. (附加题)如果这 10 台机器的型号不一,有 8 核也有 16 核,有旧 CPU 也有更快的新 CPU,你该采用何种负载均衡策略,以求缩短求解问题的时间(至少比 plain round-robin 算法要好)?




## 3. done

## 4. unorganized

## 软件

### 1. 翻译

1. 全局热键

   [Qt全局热键之使用QxtGlobalShortcut实现-CSDN博客](https://blog.csdn.net/hp_cpp/article/details/105968709)

2. 翻译

   [Qt国际化翻译(中英切换)步骤:可子界面翻译_使用qt实现翻译但切换后界面没有文字_买的挂什么时候到账的博客-CSDN博客](https://blog.csdn.net/weixin_52764460/article/details/119040216)

   [[新手]基于C++Qt5通过调用百度翻译API制作简易翻译工具_qt+百度api实现翻译_无机无机无忌的博客-CSDN博客](https://blog.csdn.net/yyy90/article/details/113762827)



### 2. 闹钟+todo

