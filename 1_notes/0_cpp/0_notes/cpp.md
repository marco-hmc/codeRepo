# 基础

#### **网络通信部分**
* 网络通信部分,主要有两大块,
1. 第一个是程序启动时,与服务端的交互;
2. 第二个就是文件下载与分享的 P2P 网络.
Prerequisites:
1. 具体的就是 Socket 的各种 API 函数,以及基于这些 API 逻辑的组合
2. 当然可能也会用到操作系统平台所特有的网络 API 函数,如 **WSAAsyncSelect** 网络模型.
Design Points:
1. 网络通信部分如何与 UI 部分进行数据交换:
   是使用队列?
    如果使用队列,多线程之间如何保持资源的一致性和解决资源竞态,使用 Event/CriticalSection/Mutex/Semaphore 等?
   全局变量?
   或者相应的 Windows 操作平台提供的特殊通信技术,如 PostMessage 函数/管道?

* 一款 C++ 软件 = C++ 语法 + 操作系统 API 函数调用

#### 3.4 COW
* 什么是COW(copy on swap)?有什么用?
* 在什么场景下使用?
* 怎么实现?

#### 3.5 CAS
* 什么是CAS(copy and swap)?有什么用?
  在C++编程中,"copy-and-swap"(CAS)是一种常用的技术,用于实现赋值操作符(operator=).CAS的基本思想是先创建一个副本,然后交换副本和原对象.
* 在什么场景下使用?
  实现赋值操作符:CAS是实现赋值操作符(operator=)的一种常见方法.它可以简化代码,并提供强异常安全性.

  提供强异常安全性:如果你的代码需要在异常发生时保持一致性(即,不会因为异常而处于无效状态),那么CAS可能是一个好的选择.在CAS中,如果复制操作抛出异常,原对象不会被修改.

  避免自我赋值问题:在传统的赋值操作符实现中,你需要检查自我赋值(即,a = a).但是在CAS中,由于赋值操作符接受的是一个副本,所以不需要检查自我赋值.

  然而,CAS并不适用于所有情况.CAS的一个主要缺点是它需要进行复制操作,这可能会导致性能问题.如果你的对象很大,或者复制操作很昂贵,那么你可能需要使用其他方法来实现赋值操作符.

* 什么时候需要用move
  * 对于callback函数来说
  * 对于将对象插入到容器来说
  * 交换两个对象
  * 
## main函数执行前完成什么工作？

main函数执行之前主要是初始化系统资源

1. 设置栈指针
2. 初始化static静态和global全局变量，即data段内容
3. 将未初始化部分的赋初值：数值型short，int，long等为0，bool为FALSE，指针为NULL，等等，即.bss段的内容
4. 运行全局构造器，估计是C++中构造函数之类
5. 将main函数的参数，argc，argv等传递给main函数，然后才真正运行main函数

**在C++内部，在全局构造函数中，访问其他全局或者静态变量，其结果是不可预知的**

## NULL和nullptr的区别

* 在C语言中，NULL通常被定义为：#define NULL ((void *)0)

* 所以NULL实际上是一个空指针，如果在C语言中写入以下代码，编译是没有问题的，因为在**C语言中把空指针赋给int和char指针的时候，发生了隐式类型转换，把void指针转换成了相应类型的指针**

  ```c++
  int  *pi = NULL;
  char *pc = NULL;
  ```

* 以上代码如果使用C++编译器来编译则是会出错的，因为C++是强类型语言，void*是不能隐式转换成其他类型的指针的，所以实际上编译器提供的头文件做了相应的处理

  ```c++
  #ifdef __cplusplus
  #define NULL 0
  #else
  #define NULL ((void *)0)
  #endif
  ```

## 虚函数指针、虚函数表

- 虚函数指针：在含有虚函数类的对象中，指向虚函数表，在运行时确定。
- 虚函数表：在程序只读数据段（`.rodata section`，见：目标文件存储结构:http://t.cn/E4WVBeF），存放虚函数指针，如果派生类实现了基类的某个虚函数，则在虚表中覆盖原本基类的那个虚函数指针，在编译时根据类的声明创建

## 虚继承

* 虚继承用于解决多继承条件下的菱形继承问题（浪费存储空间、存在二义性）
* 底层实现原理与编译器相关，一般通过**虚基类指针**和**虚基类表**实现，**每个虚继承的子类都有一个虚基类指针**（占用一个指针的存储空间，4/8字节）和**虚基类表**（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承
* 实际上，**vbptr 指的是虚基类表指针**（virtual base table pointer），该指针指向了一个**虚基类表**（virtual table），**虚表中记录了虚基类与本类的偏移地址**；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间

## 虚继承、虚函数区别

- 相同之处：都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）

- 不同之处：

- - 虚函数不占用存储空间
  - 虚函数表存储的是虚函数地址
  - 虚基类依旧存在继承类中，只占用存储空间
  - 虚基类表存储的是虚基类相对直接继承类的偏移
  - 虚继承
  - 虚函数

## 构造函数或析构函数调用虚函数

* 简要结论： 
  1. **从语法上讲，调用完全没有问题**
  2. 但是从效果上看，往往不能达到需要的目的
* Effective 的解释是： 
  * 派生类对象构造期间进入基类的构造函数时，对象类型变成了基类类型，而不是派生类类型
  * 同样，进入基类析构函数时，对象也是基类类型

# C++11

## 原子变量介绍

* 解决多线程下共享变量的问题(i++，指令重排问题)：对于共享变量的访问进行加锁，加锁可以保证对临界区的互斥访问，
* C++11提供了一些原子变量与原子操作解决用户加锁操作麻烦或者容易出错的问题
* C++11标准在标准库atomic头文件提供了模版std::atomic<>来定义原子量，而对于大部分内建类型，C++11提供了一些特化，如，std::atomic_int (std::atomic<int>)等
* 自定义类型变成原子变量的条件是该类型必须为**Trivially Copyable类型**(简单的判断标准就是这个类型可以用std::memcpy按位复制)
* atomic有一个成员函数is_lock_free，这个成员函数可以告诉我们到底这个类型的原子量是使用了原子CPU指令实现了无锁化，还是依然使用的加锁的方式来实现原子操作

## [内存序](https://www.cnblogs.com/FateTHarlaown/p/8919235.html)

## shared_ptr要点

* https://www.cnblogs.com/yahoo17/p/12862958.html

* 对于std::shared_ptr，即便父类析构函数并非虚函数，其子类的析构函数依然可以被调用，因为其 ref_count 记住了子类的实际类型

* 它借由模板构造函数窃取到了实际的指针信息，即子类的信息

  ```c++
  template <>
  class _Ptr_base<B> {
      //...
  
  private:
      B* _Ptr;
      _Ref_count_base* _Rep;
  }
  
  template <>
  class _Ref_count<D> : public _Ref_count_base {
  public:
      explicit _Ref_count(D* _Px) : _Ref_count_base(), _Ptr(_Px) {}
  
  private:
      // 最后析构函数会调用到这里
      virtual void _Destroy() noexcept override {
          delete _Ptr;
      }
  
      D* _Ptr;
  };
  
  template <>
  class shared_ptr<B> : public _Ptr_base<B> {
      explicit shared_ptr(D* _Px) {
          _Ptr = _Px; // _Ptr 静态类型是 B，但保存 new D() 的裸指针
          _Rep = new _Ref_count<D>(_Px) // _Ref_count 是 _Ref_count_base 的子类，该类保存了一个指向 D 的指针
      }
  }
  
  
  std::shared_ptr<Base> ptr(new Derived());
  
  // 如下图，ref_count中的ptr指针在初始化时，是根据模板推导出的Derived类型
  // 最后share_ptr析构的时候，是直接delete ptr，而ptr是子类类型，所以会调用子类的析构函数
  ```

  <img src="imgs/c++/shared_ptr.png" alt="shared_ptr" style="zoom:67%;" />

## enable_share_from_this

* C++11开始时支持 `enable_shared_from_this`，它一个模板类，定义在头文件 `<memory>`，其原型为： 

  ```c++
  // <memory>
  
  template< class T > 
  class enable_shared_from_this;
  ```

* std::enable_shared_from_this 能让其一个对象（假设其名为 t ，且已被一个 std::shared_ptr 对象 pt 管理）**安全地生成其他额外的** std::shared_ptr 实例（假设名为 pt1, pt2, … ） ，**它们与 pt 共享对象 t 的所有权**

* 若一个类 T **继承** std::enable_shared_from_this ，**则会为该类 T 提供成员函数**： shared_from_this 。 当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr 类对象管理时，调用 T::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr 对象，它**与 pt 共享 t 的所有权**

* 为什么要用 `enable_shared_from_this`？

  * **需要在类对象的内部中获得一个指向当前对象的 shared_ptr 对象**
  * 如果在一个程序中，对象内存的生命周期全部由智能指针来管理。在这种情况下，**要在一个类的成员函数中，对外部返回this指针就成了一个很棘手的问题**

* 什么时候用？

  - 当一个类被 `share_ptr` 管理，且在**类的成员函数里需要把当前类对象作为参数传给其他函数时**，这时就需要传递一个指向自身的 `share_ptr`

* 如何安全地将 this 指针返回给调用者?

  - **一般来说，我们不能直接将this指针返回**。**如果函数将 this 指针返回到外部某个变量保存，然后这个对象自身已经析构了，但外部变量并不知道，此时如果外部变量再使用这个指针，就会使得程序崩溃**

    ```c++
    class obj {
    public:
    	// 这样做语法上没有问题，但是破坏了智能指针的语义了，使用了原生指针
        obj* getRawThis() {
            return this;  
        }
    	
        // 这样做程序会崩掉，这个临时变量在函数完毕后会被析构掉，会执行delete this
        shared_ptr<obj> getSharedCopy() {
            return shared_ptr<obj>(this); 
        }
    	
        // 这样做就更憨了，obj对象本身持有了包覆自己this指针的shared_ptr，
        // 那么他们的生命周期是“同步”的，这样被管理的obj永远不会释放
        shared_ptr<obj>& getSharedRef() {
            if(p == nullptr) {
                p = new shared_ptr<obj>(this);
            }
            return *p;   
        }
    
        // 当然，从上面也可以看出，实际上核心的问题，就是：
        // 1. 如果采用返回拷贝，那么临时变量会把this析构掉
        // 2. 如果采用返回引用，那么obj对象本身必须持有一个管理他的shared_ptr，这样会导致obj永远不会被释放
        // 可用的解决方案有以下两种
    
    
        void getSharedFromParam(shared_ptr<obj>& p) {
            p.reset(this);    // 通过函数参数来实现规避掉拷贝语义，但是这样太过于丑陋
        }
    	
        // 这是C++11推荐的方法，可以实现安全的返回一个shared_ptr<this>，
        // 返回到外面的shared_ptr的拷贝的use_count是1，不用担心this被意外delete和引用计数异常的问题
        shared_ptr<obj> getSharedFromThis() {
            return shared_from_this();
        }
    private:
        shared_ptr<obj> *p;
    };
    ```

* enable_shared_from_this类中的成员函数

  ```c++
  (constructor)：构造一个 enable_shared_from_this 对象，是一个受保护的成员函数，成员属性为 protected
  (destructor)：销毁一个 enable_shared_from_this 对象，是一个受保护的成员函数，成员属性为 protected
  operator=：返回到 this 的引用，是一个受保护成员函数，成员属性为 protected
  shared_from_this：返回共享 *this 指针所有权的 shared_ptr，是一个 public 属性的成员函数。
  weak_from_this(C++17)：返回共享 *this 所指针有权的 weak_ptr，是一个public 属性的成员函数
  ```

* 源码及存在问题

  * 原理分析：enable_shared_from_this类中使用了一个私有weak_ptr来保存地址，在shared_from_this()通过把这个weak_ptr转换为引用计数为1的shared_ptr返回，避免了临时shared_ptr析构导致this被delete

  ```c++
  // 源码
  template<typename _Tp>
  class enable_shared_from_this
  {
  protected:  //在public继承后，仍对子类可见
      enable_shared_from_this() noexcept { }
      ~enable_shared_from_this() { }
  
      //...
  
  public:
      shared_ptr<_Tp>
          shared_from_this()
      { return shared_ptr<_Tp>(this->_M_weak_this); }
  
      //...
  
  private:
      mutable weak_ptr<_Tp>  _M_weak_this;  //const函数也可以修改该变量
  
      //  _M_weak_assign函数在类型T被包覆在shared_ptr的过程中会被调用
      template<typename _Tp1>
      void _M_weak_assign(_Tp1* __p, const __shared_count<>& __n) const noexcept
      { _M_weak_this._M_assign(__p, __n); }
  };
  
  // 其中_M_assign()是weak_ptr的父类__weak_ptr的成员函数
  // _M_assign()的源码如下
  void  _M_assign(_Tp* __ptr, const __shared_count<_Lp>& __refcount) noexcept
  {
      if (use_count() == 0)
      {
          _M_ptr = __ptr;
          _M_refcount = __refcount;
      }
  }
  // _M_assign()的作用是为指针赋地址和引用计数（当然引用计数对weak_ptr没什么意义）
  // 所以，_M_weak_assign这个会在智能指针构造时会被调用的函数，
  // 是为了为从enable_shared_from_this中继承得来的_M_weak_this赋地址！
  
  auto p = new obj();
  p->getSharedFromThis()->doSomething(); // 这里会报一个异常：bad_weak_ptr，坑
  
  /*
  原因在于没有把obj交给shared_ptr管理起来而是直接使用了原生指针
  所以导致了 _M_weak_this没有初始化！
  进而在调用shared_from_this()时，把一个空weak_ptr转换为shared_ptr导致了异常。
  同理，也不能将继承了enable_shared_from_this的对象创建在栈上。
  这是STL在提醒我们，不要破坏智能指针的语义！
  */
  ```

* 使用示例

  ```c++
  #include <iostream>
  #include <stdlib.h>
  #include <memory>
  using namespace std;
  
  // 比较推荐的写法
  struct Good : std::enable_shared_from_this<Good> // note: public inheritance
  {
      std::shared_ptr<Good> getptr() {
          return shared_from_this();
      }
  };
  
  // 错误的用法：用不安全的表达式试图获得 this 的 shared_ptr 对象
  struct Bad
  {
      std::shared_ptr<Bad> getptr() {
          return std::shared_ptr<Bad>(this);
      }
      ~Bad() { std::cout << "Bad::~Bad() called\n"; }
  };
   
  int main()
  {
      // 正确的用法: 两个 shared_ptr 共享同一个对象
      std::shared_ptr<Good> gp1 = std::make_shared<Good>();
      std::shared_ptr<Good> gp2 = gp1->getptr();
      std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
   
      // 错误的用法: 调用 shared_from_this 但其没有被 std::shared_ptr 占有 
      try {
          Good not_so_good;
          std::shared_ptr<Good> gp1 = not_so_good.getptr();
      } 
      catch(std::bad_weak_ptr& e) {
          // 在 C++17 之前，编译器不能捕获 enable_shared_from_this 抛出的std::bad_weak_ptr 异常
          // 这是在C++17之后才有的特性
          std::cout << e.what() << '\n';    
      }
   
      // 错误的用法，每个 shared_ptr 都认为自己是对象的唯一拥有者
      // 调用错误的用法，会导致两次析构 Bad的对象，第二次析构时，指针指向的空间已经被析构，
      // 会导致程序出错
      std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
      std::shared_ptr<Bad> bp2 = bp1->getptr();
      std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
  
      return 0;
  }  
  ```

* 使用注意事项
  * enable_shared_from_this 的常见实现为：**其内部保存着一个对 this 的弱引用**（例如 std::weak_ptr )。 std::shared_ptr 的构造函数检测无歧义且可访问的 (C++17 起) enable_shared_from_this 基类，并且若内部存储的弱引用没有被以存在的 std::shared_ptr 占有，则 (C++17 起)赋值新建的 std::shared_ptr 为内部存储的弱引用。为另一个 std::shared_ptr 所管理的对象构造一个 std::shared_ptr ，将不会考虑内部存储的弱引用，从而将导致未定义行为(undefined behavior)。
  * **只允许在先前已被std::shared_ptr 管理的对象上调用 shared_from_this** 。否则调用行为未定义 (C++17 前)抛出 std::bad_weak_ptr 异常（通过 shared_ptr 从默认构造的 weak_this 的构造函数） (自C++17 起)。
  * enable_shared_from_this 提供安全的替用方案，以替代 std::shared_ptr(this) 这样的表达式（这种不安全的表达式可能会导致 this 被多个互不知晓的所有者析构）

# STL

* 请你讲讲STL有什么基本组成
  * STL主要包含六大部件：
    * 容器
    * 迭代器
    * 仿函数
    * 算法
    * 分配器
    * 配接器(适配器)
  * 他们之间的关系：分配器给容器分配存储空间，算法通过迭代器获取容器中的内容，仿函数可以协助算法完成各种操作，配接器用来套接适配仿函数

* 请你回答一下STL里vector的resize和reserve的区别
  * resize()：改变当前容器内含有元素的数量size，eg: vector\<int\>v；v.resize(len)；v的size变为len，**如果原来v的size小于len，那么容器新增（len-size）个元素，元素的值为默认为0**。当v.push_back(3);之后，则是3是放在了v的末尾，即下标为len，此时容器是size为len+1；**如果原来v的size大于len，resize会移除那些超出len的元素同时销毁他们**
  * reserve()：改变当前容器的最大容量（capacity），**它不会生成元素**，只是确定这个容器允许放入多少对象，如果reserve(len)的len值大于当前的capacity，那么会重新分配一块能存len个对象的空间，然后把之前v.size()个对象通过copy construtor复制过来，销毁之前的内存。len值小于当前capacity，不做处理
  * **resize既分配了空间，也创建了对象，可以通过下标访问。resize既修改capacity大小，也修改size大小**
  * **reserve只修改capacity大小，不创建对象，push或insert时才创建，不修改size大小**
* 请你来说一下map和set有什么区别，分别又是怎么实现的？

  * map和set都是C++的关联容器，其底层实现都是红黑树（RB-Tree）。由于 map 和set所开放的各种操作接口，RB-tree 也都提供了，所以几乎所有的 map 和set的操作行为，都只是转调 RB-tree 的操作行为。

  * map和set区别在于：

    * map中的元素是key-value（关键字—值）对：关键字起到索引的作用，值则表示与索引相关联的数据；set与之相对就是关键字的简单集合，set中每个元素只包含一个关键字。
    * **set的迭代器是const的，不允许修改元素的值；map允许修改value，但不允许修改key**。其原因是因为map和set是**根据关键字排序来保证其有序性**的，**如果允许修改key的话，那么首先需要删除该键，然后调节平衡，再插入修改后的键值，调节平衡，如此一来，严重破坏了map和set的结构，导致iterator失效，不知道应该指向改变前的位置，还是指向改变后的位置**。所以STL中将set的迭代器设置成const，不允许修改迭代器的值；而map的迭代器则不允许修改key值，允许修改value值。

    * map支持下标操作，set不支持下标操作。如果find能解决需要，尽可能用find

* functional头文件支持的基于模板的比较函数对象
  * equal_to<Type>、not_equal_to<Type>、greater<Type>、greater_equal<Type>、less<Type>、less_equal<Type>
  * 常用的有greater <Type>()从大到小排序，less <Type>()从小到大排序
* priority_queue自定义排序要点：
  * https://blog.csdn.net/imred/article/details/108478144