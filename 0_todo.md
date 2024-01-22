[toc]
## 1. doing

### 1.0 un-organzied

monday: 1830-2130
tuesday: 1830-1930

**std::weak_ptr** 是一个不控制资源生命周期的智能指针,是对对象的一种弱引用,只是提供了对其管理的资源的一个访问手段,引入它的目的为协助 **std::shared_ptr** 工作.

**std::weak_ptr** 可以从一个 **std::shared_ptr** 或另一个 **std::weak_ptr** 对象构造,**std::shared_ptr** 可以直接赋值给 **std::weak_ptr** ,也可以通过 **std::weak_ptr** 的 **lock()** 函数来获得 **std::shared_ptr**.它的构造和析构不会引起引用计数的增加或减少.**std::weak_ptr** 可用来解决 **std::shared_ptr** 相互引用时的死锁问题(即两个**std::shared_ptr** 相互引用,那么这两个指针的引用计数永远不可能下降为 0, 资源永远不会释放).


例如,一台常见的笔记本电脑的屏幕DPI可能在100-200之间,而一台高分辨率的手机屏幕DPI可能超过300.

#### 用过数据库吗?masql数据库中会用到哪些锁?
乐观锁与悲观锁.
#### 谈一下对乐观锁和悲观锁的认识
乐观锁就是很乐观,觉得所有的资源都没有被同时访问,所以到了访问的最后才上锁.悲观锁很悲观,每次访问的时候都绝对所有的资源都被同时访问,所以,每次访问资源都会先上锁.<br>
具体:
* 悲观锁,总是觉得被人会修改数据,所以每次拿数据都会先上锁,这样别的进程还是线程都不能访问,直到它自己拿到锁.这种在传统关系型数据库就会常常用到,比如行锁,表锁,读写锁等,操作之前先上锁.
* 乐观锁,就不会觉得别人会修改数据,不上锁,在更新版本的时候,判断一下此期间别人是否更新棵数据,可以适用版本号等机制.乐观锁适用于多读的应用类型,这样可以提高吞吐量,像数据库如果提供类似与写机制,其实都是提供乐观锁

乐观锁适用于写少的情况,冲突少发生,加大吞吐量.悲观锁就适合写多的情况,冲突发生多.

#### 慢启动曲线
慢启动,先发一个,可以就发两个,两个可以发四个,如此下去,遇到sshread?那就线性,一个一个加,咦?拥塞了,丢包了?两种方案,快速重传或者将shhresh设为窗口的一半,然后又一个发,两个发,三个发,遇到sshresh的点,就一个一个发,这时就会看见网络卡顿.快速重传就将减半的sshresh+3,然后又一个一个发.
#### https在平时的项目中有用到过吗?
用过,套了一层SSL层.非对称加密到对称加密🔐
#### 三次握手的具体实现,time_wait原理?

#### 怎么求两个节点的最近公共祖先?

#### 100万个ip,找出最多的100个(内存放得下的时候,放不下的时候)
100万个IP,很多.分10万个ip,分别在散列表中进行计数.然后将分批计算的IP取前十个.组合,将相同的加一起计算,如果够100个就输出,不够就继续每批再取100个,再组合,加上原来的,继续通过快速排序,得出最多的100个ip(内存肯定放不下).
#### poll和epoll的区别
epoll是poll的升级版.其实poll和epoll都是用于同时监视多个文件描述符的.poll需要自己管理一组文件描述符的集合,而epoll就使得内核为我们管理这个结构体的数组,通过epoll_create.epoll不是一个函数,他是一组函数的实现.<br>
* poll布置完监视任务就需要取得监视的结果,而epoll就是用epoll_wait函数进行阻塞监视并返回监视结果.
epoll更成熟.<br>

## 讲讲cpp多线程与任务

#### C中如何调用C++函数?并重写类内成员函数声明
[c中如何调用C++函数](https://blog.csdn.net/nizqsut/article/details/52148973)<br>
[综合C调用C++,C++调用C](https://www.cnblogs.com/ruili07/p/9728389.html)

#### C++写一个线程池框架(list/queue/conditional),多线程操作,C++面向对象建模和多态以及单元测试
CPU之间的负载调度/做异步编程/非阻塞线程的拓展思路/非阻塞线程与可阻塞线程之间死锁关系.

#### 生产者消费者消息队列 线程

#### 编译生成的二进制文件计算机是怎么识别的 

#### cpp文件是怎么运行起来的 
#### 优先队列的时间复杂度 
#### 堆的维护时间复杂度 
#### c++继承和虚函数 
#### 虚函数的作用 
#### tcp以什么保证可靠 

#### tcp数据校验是怎么做的
#### 死锁怎么发生的 
#### hash表是什么 
#### 谈谈对归一化方法的了解
#### 求数组中最小的10个数,用堆写
#### 分段分页机制
#### C++垃圾回收,shared_ptr的引用计数出现循环引用怎么办

#### C中的malloc和free做了哪些事情,free怎么知道free多长,C++中的delete又怎么知道delete多长

在C中,`malloc`和`free`是用于动态内存管理的函数.它们的作用是分配和释放内存空间.

`malloc`函数用于分配指定大小的内存块,并返回一个指向该内存块的指针.它接受一个参数,即要分配的内存块的大小(以字节为单位).`malloc`会在堆(heap)中找到足够大的连续内存块,并将其标记为已分配.然后,它返回指向该内存块的指针,以便我们可以使用它来存储数据.

`free`函数用于释放先前通过`malloc`函数分配的内存块.它接受一个参数,即要释放的内存块的指针.当我们调用`free`函数时,它会将该内存块标记为未分配,并将其返回给堆,以便其他程序可以使用.

在C中,`free`函数并不知道要释放的内存块的大小.它假设我们已经知道要释放的内存块的大小,并正确地传递了指向该内存块的指针.这是因为`malloc`和`free`之间没有直接的通信机制来传递内存块的大小信息.

在C++中,`delete`和`delete[]`是用于释放动态分配的内存的运算符.与`malloc`和`free`类似,`delete`和`delete[]`也用于分配和释放内存空间.

`delete`运算符用于释放通过`new`运算符分配的单个对象的内存.它接受一个参数,即要释放的对象的指针.当我们调用`delete`运算符时,它会先调用对象的析构函数,然后释放对象占用的内存.

`delete[]`运算符用于释放通过`new[]`运算符分配的数组对象的内存.它接受一个参数,即要释放的数组对象的指针.当我们调用`delete[]`运算符时,它会先调用数组中每个元素的析构函数,然后释放整个数组占用的内存.

与C中的`free`函数类似,C++中的`delete`和`delete[]`运算符也不知道要释放的内存块的大小.它们假设我们已经知道要释放的内存块的大小,并正确地传递了指向该内存块的指针.

总结一下,无论是C中的`malloc`和`free`,还是C++中的`delete`和`delete[]`,它们都是用于动态内存管理的函数或运算符.它们分别用于分配和释放内存空间,但并不知道要释放的内存块的大小.因此,在使用它们时,我们需要确保正确地传递内存块的大小信息.

#### STL库,vector的内存管理,deque的内存管理,list的排序
vector的内存管理原理是动态数组.当我们创建一个vector对象时,它会分配一块连续的内存来存储元素.当我们向vector中添加元素时,如果当前内存空间不足以容纳新的元素,vector会自动重新分配更大的内存块,并将原有的元素复制到新的内存块中.这个过程称为动态内存分配.当我们从vector中删除元素时,vector会释放不再使用的内存,以便节省内存空间.

deque的内存管理原理是双端队列.deque是由多个连续的内存块组成的,每个内存块都存储一定数量的元素.当我们向deque中添加或删除元素时,deque会根据需要在内存块的前端或后端进行插入或删除操作.这种设计使得deque在插入和删除元素时具有较好的性能,因为它不需要像vector那样重新分配内存和复制元素.

list的排序是通过链表的操作实现的.链表是由一系列节点组成的数据结构,每个节点都包含一个元素和指向下一个节点的指针.当我们对list进行排序时,list会使用一种称为"归并排序"的算法.归并排序将链表分割成较小的子链表,然后逐步合并这些子链表,直到得到一个有序的链表.归并排序的时间复杂度为O(nlogn),在大多数情况下比其他排序算法更高效.

### 给自己一个小目标,每天都攻克一个知识点,一周后回来看看自己的进展
#### 腾讯一面
* 字节对齐以及为什么要字节对齐?字节对齐的相关规则,举例一个char型数据,在内存中会分配多少字节?
* vector/list以及map/set这些的数据结构是怎么样的?(连续型内存,类似数组;红黑树)
* 上述结构中插入数据和删除数据的时间复杂度是怎么样的?
* 几个基本排序算法的最好时间复杂度以及平均复杂度?
* 红黑树是什么样的数据结构?红黑树和B数的区别?
* 变量的定义和声明有什么区别?声明的关键字?(extern?)
* malloc的认识?new的具体实现机制是什么样的?(先分配内存,再调用构造函数)
* 哈希冲突的解决算法?(开放地址法和拉链法)一致哈希了解吗?
* 进程间的通信方式有哪些?互斥的具体原理?
* 用过数据库吗?masql数据库中会用到哪些锁?
* 谈一下对乐观锁和悲观锁的认识
* 流量控制是怎么实现的?(滑动窗口)滑动窗口的大小具体是怎么变化的?
* 慢启动曲线
* https在平时的项目中有用到过吗?
* 三次握手的具体实现,time_wait原理?
* 怎么求两个节点的最近公共祖先?
* 100万个ip,找出最多的100个(内存放得下的时候,放不下的时候)
* poll和epoll的区别
* 一个项目中有很多模块,互相调用,应该怎么设计
#### 腾讯二面
* 隔一个删除一个map中的元素(主要考察迭代器的失效问题) , 虚函数如何实现的,画出内存图
* Linux:文件系统 (这个我不会,没怎么问),进程线程区别,详细说明 管道/共享内存/信号量,在共享内存中如何使用mutex,1G共享内存,切割为很多记录,每个大小1K,多个进程访问,如何对每个记录进程保护 (不同同时读写一个记录)
* select和epoll
* nginx和apache对比

#### 头条
* 编译生成的二进制文件计算机是怎么识别的 
* cpp文件是怎么运行起来的 
* 优先队列的时间复杂度 
* 堆的维护时间复杂度 
* c++继承和虚函数 
* 虚函数的作用 
* tcp以什么保证可靠 

* tcp数据校验是怎么做的 
* 死锁怎么发生的 
* hash表是什么 
* 谈谈对归一化方法的了解
* 找出排序数组中离第k个数最近的m个数,最近的意思是相减绝对值最小
* 求数组中最小的10个数,用堆写
* 分段分页机制
* C++垃圾回收,shared_ptr的引用计数出现循环引用怎么办
* C中的malloc和free做了哪些事情,free怎么知道free多长,C++中的delete又怎么知道delete多长
* 问STL库,vector的内存管理,deque的内存管理,list的排序

#### 阿里
* PageRank
* 两个数相乘,用什么数据结构(栈)
* hashmap源码(我没看).hashmap如何实现(广义链表).
* 找数组中加和为k的一组数.
##### 阿里一面
1⃣️算法:
* 在无序数组中找最大的K个数?
* 对无序数组`A[0:n-1]`进行预处理(不能改变`A[0:n-1]`内元素的顺序),使得能在O(1)时间内快速找到子数组`A[i:j]`的和?
* 在一个单向链表中实现快排?(快排效率以及内省排序)
* 讲解一下内省排序的原理?

2⃣️C++基础
* 用const修饰类成员函数的作用?
* 能否在一个const成员函数中调用非const成员函数,为什么?
* 模板的实现和声明是否一定要在同一个头文件中,为什么? 

3⃣️Linux
* 讲讲你对Linux内存的了解?
* Linux内存的页表的作用是什么?
* Linux内核地址空间的布局,内核地址空间是如何访问物理内存的?

##### 阿里二面
1⃣️Linux
* Linux中,怎样删除一个目录中最后一次修改时间在一个星期以前的所有文件,具体代码怎么写?
* 如何写一个线程池?
* 你觉得这个线程池有哪些可以优化的地方
2⃣️C++
* 多态的作用是什么,它是怎样实现的?
* C++中的override是什么,它是怎样实现的?
3⃣️ GDB
* 多线程调试中会有coredump的情况,如何定位错误?
* 警告错误位置和实际错误位置为什么会不一致,举例说明?
* 谈谈你对buffer overflow的理解?
4⃣️Linux
* 在Linux中,若父子进程中有一个异常终止,会对另一个进程有影响吗,为什么?
* 如何修改你的程序,使其解决因异常终止而带来的影响?
5⃣️高并发
* 假设在某一时刻由几万个并发请求同时产生,请设计一个方案来处理这种情况.

#### 百度
##### 百度二面
* 特殊的地方,不允许使用STL容器,自己实现链表或是数组,要写出完整功能,包括构造析构函数.注意边界情况和内存泄漏

#### 知乎总结
* redis持久化机制
* redis销毁方式机制
* mq实现原理
* C++虚函数
* hash冲突的解决
* memcached一致性哈希
* socket函数select的缺陷
* epoll模型
* 同步互斥
* 异步非阻塞
* 回调的概念
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

##### 深入了解虚拟继承对象模型
为了解决多份拷贝的问题,引入了虚继承,看如下一个🌰
```cpp
class MyClassA:virtual public MyClass
class MyClassB:virtual public MyClass
class MyClassC:public MyClassA,public MyClassB
```
那么除了秉承这个观点还有什么呢?没错,还有一个虚基类表vbtable.虚继承的引入把对象的模型变得十分复杂,除了每个基类(MA和MB)和公共基类(M)的虚函数表指针需要记录📝外,每个虚拟继承了MyClass的父类还需要记录一个虚基类表vbtable的指针vbptr.<br>
![MyClassC的对象模型](./img/Myclass.jpg)<br>
虚基类表每一项记录📝了被继承的虚基类子对象相对于虚基类表指针的偏移量.参考[虚函数与虚继承寻踪](http://www.cnblogs.com/fanzhidongyzby/archive/2013/01/14/2859064.html)<br>

* 同步/异步/阻塞/非阻塞的理解
* 进程的调度算法
* 什么是死锁,如何解决死锁


请注意,这些都是非常粗略的估计,实际的耗时可能会有很大的差异.

marco-hmc: Help me write the program for submitting information to one website which need to be login in first. Do it and explain it step by step.

GitHub Copilot: Sure, here are the steps to write a Python program to submit information to a website that requires login:

1. Import the necessary libraries. We will use `requests` for making HTTP requests and `BeautifulSoup` for parsing HTML.

```python
import requests
from BeautifulSoup4 import BeautifulSoup
```

2. Define the URLs for the login page and the form submission page. Also, define your login credentials.

```python
login_url = 'https://www.example.com/login'
form_url = 'https://www.example.com/form'
credentials = {
    'username': 'your_username',
    'password': 'your_password'
}
```

3. Start a new session and get the login page.

```python
session = requests.Session()
response = session.get(login_url)
```

4. Parse the login page, find the login form and extract all the input fields. Then, update the credentials dictionary with these fields.

```python
soup = BeautifulSoup(response.text, 'html.parser')
form = soup.find('form')
fields = form.findAll('input')

formdata = {}
for field in fields:
    if 'name' in field.attrs:
        formdata[field.attrs['name']] = field.attrs['value'] if 'value' in field.attrs else ''

# Update the formdata with our credentials
formdata.update(credentials)
```

5. Submit the login form with our credentials.

```python
response = session.post(login_url, data=formdata)
```

6. Check if login was successful. This will depend on how the website indicates a successful login. In this example, we'll just print the status code and the first 500 characters of the response text.

```python
print(response.status_code)
print(response.text[:500])
```

7. If login was successful, you can now submit information to the website. Let's say we want to submit a form with the following information:

```python
formdata = {
  'field1': 'value1',
  'field2': 'value2',
  'field3': 'value3'
}
```

8. Submit the form.

```python
response = session.post(form_url, data=formdata)
```

9. Check if form submission was successful.

```python
print(response.status_code)
print(response.text[:500])
```

### 1.1 trivals
  1. podcast
  2. 医保卡补办
  3. blog
    * [GitHub - Veeupup/veeupup.github.io: blog... maybe writing more..](https://github.com/Veeupup/veeupup.github.io)

### 1.2 questions 
  1. 智能指针实现
     * weak_ptr是用于解决什么问题的
     * 智能指针的实际使用放啊
  3. 虚函数表
  4. network/ os
  5. event事件
  7. debug的控制台,支持print,header-only,支持switcher功能
  8. .rc文件是什么?.rcc文件是什么?.rc.in文件是什么?
     1. `.rc` 文件:在 Windows 环境中,`.rc` 文件通常是资源脚本文件,用于在编译时包含在应用程序中的资源,如图标/菜单和其他界面元素.在 Unix-like 系统中,`.rc` 文件通常是 shell 或其他程序的配置文件,如 `bashrc`/`vimrc` 等.在 Qt/C++ 程序中,`.rc` 文件可能是 Qt 资源文件,用于在编译时将资源(如图像/翻译文件等)嵌入到可执行文件中.

     2. `.rcc` 文件:在 Qt 环境中,`.rcc` 文件是一个二进制资源文件,它包含了在编译时嵌入到 Qt 应用程序中的资源.你可以使用 Qt 的 `rcc` 工具从 `.qrc` 资源文件生成 `.rcc` 文件.

     3. `.rc.in` 文件:`.rc.in` 文件通常是一个模板配置文件,用于生成实际的 `.rc` 文件.这种文件通常在编译或安装过程中被处理,其中的某些占位符或变量会被替换为实际

    一般通过CONFIGURE_FILE(template.rc.in, target.rc.in)方式拷贝.

  9. .rc文件由什么去解析?.rcc文件由什么去解析?具体是怎么使用的

.rc文件通常由特定的解析器或编译器解析.在Windows环境中,.rc文件由资源编译器(Resource Compiler)解析.资源编译器将.rc文件中的资源(如图标/菜单/对话框等)编译成二进制格式,以便在应用程序中使用.

.rcc文件是Qt框架中的一种二进制资源文件,由Qt的资源编译器(rcc)解析.rcc工具将.qrc文件中的资源(如图像/翻译文件等)编译成.rcc文件,然后可以在Qt应用程序中使用.

具体使用.rc文件和.rcc文件的步骤如下:

1. .rc文件的使用:
   - 创建一个.rc文件,定义所需的资源,如图标/菜单/对话框等.
   - 使用资源编译器(如Windows的rc.exe)将.rc文件编译成二进制格式的资源文件(.res).
   - 在应用程序中使用资源文件,例如通过调用LoadResource函数加载资源.

2. .rcc文件的使用:
   - 创建一个.qrc文件,定义所需的资源,如图像/翻译文件等.
   - 使用Qt的资源编译器(rcc)将.qrc文件编译成二进制格式的.rcc文件.
   - 在Qt应用程序中使用.rcc文件,例如通过调用QResource::registerResource函数注册资源文件,然后可以通过资源路径来访问资源.

请注意,具体的使用方法可能会因不同的开发环境和工具链而有所差异.

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
