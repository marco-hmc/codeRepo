[toc]
## 1. doing

### 1.0 un-organzied

#### 腾讯一面



* malloc的认识?new的具体实现机制是什么样的?(先分配内存,再调用构造函数)
* 哈希冲突的解决算法?(开放地址法和拉链法)一致哈希了解吗?
* 进程间的通信方式有哪些?互斥的具体原理?

##### 阿里二面
1⃣️Linux
* Linux中,怎样删除一个目录中最后一次修改时间在一个星期以前的所有文件,具体代码怎么写?
* 如何写一个线程池?
* 你觉得这个线程池有哪些可以优化的地方


#### 百度
##### 百度二面

#### 知乎总结

* mq实现原理
* C++虚函数
* memcached一致性哈希
* socket函数select的缺陷
* epoll模型
* 同步互斥
* 异步非阻塞
* 单向图最短路径
* 动态规划算法

[C++面试会问什么?](https://www.zhihu.com/people/starktony/activities)

* 构造,基类先于成员,成员先于派生(先有爸爸👨),析构,派生类先于成员,成员先于基类(先打儿子,先欺负小的👦)

#### 虚继承 虚基类
令所有继承File的都变成虚继承
```cpp
class File{};
class InputFile:virtual public File{};
class OutputFile:virtual public File{};
class IOFile:public InputFile,public OutputFile{};
```
虚继承是一种机制,类通过虚继承指出它希望共享其虚基类的状态.在虚继承下,对给定虚基类,无论该类在派生层次中作为虚基类出现多少次,都只继承一个共享的基类子对象.<br>
这就很好解决了不用复制太多的成员变量.毕竟virtual始终秉承着一个观点,一个接口,你可以多种方法,始终一个接口.后面的实现都会覆盖本来的方法.<br>

#### 多重继承(虚继承)与访问控制 明智而审慎地使用多重继承
多重继承上面其实也有体现,例如Circle继承了Shape,Shape2.多重继承衍生出类层次<br>
* 共享接口: 通过使用类使得重复代码较少,且代码规格同一.通常称为 **运行时多态**或者接口继承
* 共享实现: 代码量较少且实现代码的规格同一,通常称为实现继承.<br>
一个类可以综合应用接口与实现继承.<br>


* 同步/异步/阻塞/非阻塞的理解
* 进程的调度算法
* 什么是死锁,如何解决死锁



### 1.1 trivals
  1. podcast
  2. 医保卡补办
  3. blog

    * [GitHub - Veeupup/veeupup.github.io: blog... maybe writing more..](https://github.com/Veeupup/veeupup.github.io)

### 1.2 questions 
  5. event事件

### 1.4 utils 
  1. gtest
  2. 多线程
  3. coredump怎么用
  4. 内存泄露检测怎么用?  
  5. gitbook
    * https://ganxunzou.gitbooks.io/gitlab-doc/content/gitbook-yu-gitlab-ji-cheng/gitbook-ci-an-zhuang.html
    * 可以参考modern-cpp-tutorial-master组织书

### 1.3 projects
  1. 日志库
  2. json解析
  3. 写一个自动提交加班时长的

### 1.5 readings
  1. **cpp**
    2_project\modern-cpp-tutorial-master\book\zh-cn\
  2. **refactor**
    1_notes\6_设计模式\refactoring2\ch1.md
  3. **js**

    1_notes\0_frontEnd\js\en.javascript.info-master\1-js\05-data-types\01-primitives-methods\article.md
  4. **template**

    2_project\Cpp-Templates-2ed-master\Cpp-Templates-2ed-master\docs\01_function_template.md
  5. real-time rendering
  6. [Ulrich Drepper. 每位程序员都需要知道的内存知识. 2007](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
  7. [<C++ 风格指南>](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/).
  13. [Jason Turner's C++ Weekly](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw) - nice collection of C++-related videos.
  15. [语法层面](https://blog.csdn.net/neverever01/article/details/108237531)
  16. [参考资料](https://mp.weixin.qq.com/s?__biz=MzU4ODI1MjA3NQ==&mid=2247490061&idx=2&sn=12149cbf01c461cb6e7193c87f86947b&chksm=fddeccc9caa945dfd40e5b721d3de6c072e6c63090d517c2abd7cdbad03913ffe1894ecf515e&scene=126&sessionid=1598581626&key=327ff69e53d289e265ba4be42c78ab289d247b013a397b5e56a76f8e15d507e2b246f5f8e182aea30e297541e608b44b6afc4aef2a158685ddc7b89ac3819a93af1a874e7eb8032ca33fcbfdc490c6d80ff937238fae8bf025d4df48edd109b337fce874a51bcfd3c4d6c73519144f1d2bb2d2642e053526abb49c65f1ad7a7a&ascene=1&uin=MTY3MDE4MjUzNw%3D%3D&devicetype=Windows+10+x64&version=62090529&lang=zh_CN&exportkey=Ae7A2lvgN6N2S9zIIGtxrwk%3D&pass_ticket=IxOgoA0uCVNmIWk3JlME4s%2BV8YtCCJRms%2FWOtZaGjo%2F4rRk9WXulOQCMRIzciJYH)  

--------------------------------------------------------


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

* 有什么适合提高 C/C++ 网络编程能力的开源项目推荐？

  https://www.zhihu.com/question/20124494

