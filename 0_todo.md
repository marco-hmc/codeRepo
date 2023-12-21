[toc]
## 1. doing

### 1.0 un-organzied
* 怎么理解所有存储在图形系统中的几何数据都已节点的形式存储?上下的背景信息都可以介绍一下

  在计算机图形学中,场景通常被组织为一种称为"场景图"(Scene Graph)的数据结构.场景图是一种树形结构,其中每个节点代表场景中的一个对象或一组对象.这些对象可以是几何形状(如三角形/立方体等)/光源/摄像机或者其他的图形实体.

  场景图的一个关键特性是,每个节点的变换(位置/旋转和缩放)是相对于其父节点的.这意味着,如果你移动一个节点,那么所有的子节点也会跟着移动.这使得一些操作变得非常方便,例如旋转一个节点以及其所有的子节点,或者在不改变相对位置的情况下移动一组节点.

  在这种结构中,几何数据(即模型的顶点/边和面)通常存储在叶子节点中,而变换/材质和其他属性则存储在内部节点中.当渲染场景时,图形系统会遍历场景图,并将每个节点的变换应用到其几何数据上,然后将结果发送到图形硬件进行渲染.

  这种方式的优点是可以方便地组织和管理复杂的场景,以及方便地实现一些复杂的效果,例如层级动画/物体的相对运动等.缺点是需要更多的内存来存储场景图,以及更多的计算资源来处理场景图的遍历和变换的应用.

### 1.1 trivals
  1. podcast
  2. 医保卡补办
  3. blog
    * [GitHub - Veeupup/veeupup.github.io: blog... maybe writing more..](https://github.com/Veeupup/veeupup.github.io)
  4. 家里的电脑也弄一个vs+cmake的方案

### 1.2 questions 
  1. 智能指针实现
     * weak_ptr是用于解决什么问题的
     * 智能指针的实际使用放啊
  3. 虚函数表
  4. network/ os
  5. event事件
  6. debug的控制台,支持print,header-only,支持switcher功能
  7. .rc文件是什么?.rcc文件是什么?.rc.in文件是什么?
     1. `.rc` 文件:在 Windows 环境中,`.rc` 文件通常是资源脚本文件,用于在编译时包含在应用程序中的资源,如图标/菜单和其他界面元素.在 Unix-like 系统中,`.rc` 文件通常是 shell 或其他程序的配置文件,如 `bashrc`/`vimrc` 等.在 Qt/C++ 程序中,`.rc` 文件可能是 Qt 资源文件,用于在编译时将资源(如图像/翻译文件等)嵌入到可执行文件中.

     2. `.rcc` 文件:在 Qt 环境中,`.rcc` 文件是一个二进制资源文件,它包含了在编译时嵌入到 Qt 应用程序中的资源.你可以使用 Qt 的 `rcc` 工具从 `.qrc` 资源文件生成 `.rcc` 文件.

     3. `.rc.in` 文件:`.rc.in` 文件通常是一个模板配置文件,用于生成实际的 `.rc` 文件.这种文件通常在编译或安装过程中被处理,其中的某些占位符或变量会被替换为实际

    一般通过CONFIGURE_FILE(template.rc.in, target.rc.in)方式拷贝.

  8. .rc文件由什么去解析?.rcc文件由什么去解析?具体是怎么使用的

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
