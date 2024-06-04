 _tags: c++, constructing

_notDone
* ***UniquePtr(const UniquePtr &) = delete;禁用拷贝构造***
    拷贝构造函数的参数通常是常量引用(const reference),而不是值(value),主要有以下两个原因:

1. **性能**:当参数是值时,会创建该对象的一个新的副本,这涉及到对象的复制操作,可能会消耗大量的时间和内存.特别是当对象较大时,复制的代价会非常高.而当参数是常量引用时,只需要传递引用,不需要复制对象,因此性能更高.

2. **避免无限递归**:如果拷贝构造函数的参数是值,那么在调用拷贝构造函数时,需要先创建一个新的对象,这又需要调用拷贝构造函数,从而形成无限递归,导致程序崩溃.而当参数是常量引用时,不会触发拷贝构造函数,因此可以避免无限递归.

所以,拷贝构造函数的参数通常是常量引用,而不是值.


* 如何实现一个引用计数指针,以及其中要注意的点?
* enable_share_from_this是做什么的
考察一下对于深拷贝,浅拷贝的思考.
* shared_ptr的引用计数是怎么存储的?    多线程场景怎么解决
* shared ptr<T>怎么实现一个普通指针的const T*效果?
* shared ptr修改指向的时候,分析一下过程,性能开销如何?
* 
**std::weak_ptr** 是一个不控制资源生命周期的智能指针,是对对象的一种弱引用,只是提供了对其管理的资源的一个访问手段,引入它的目的为协助 **std::shared_ptr** 工作.
**std::weak_ptr** 可以从一个 **std::shared_ptr** 或另一个 **std::weak_ptr** 对象构造,**std::shared_ptr** 可以直接赋值给 **std::weak_ptr** ,也可以通过 **std::weak_ptr** 的 **lock()** 函数来获得 **std::shared_ptr**.它的构造和析构不会引起引用计数的增加或减少.**std::weak_ptr** 可用来解决 **std::shared_ptr** 相互引用时的死锁问题(即两个**std::shared_ptr** 相互引用,那么这两个指针的引用计数永远不可能下降为 0, 资源永远不会释放).

## C++垃圾回收,shared_ptr的引用计数出现循环引用怎么办


* unique_ptr是怎么实现的?为什么把形参为左值引用的禁了,只放开了形参为右值引用的?

* shared_ptr是怎么实现的?为什么refCount要是指针?


1. 智能指针实现
     * weak_ptr是用于解决什么问题的
     * 智能指针的实际使用

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


## enable_share_from_this

* C++11开始时支持 `enable_shared_from_this`，它一个模板类，定义在头文件 `<memory>`，其原型为： 

  ```c++
  // <memory>
  
  template< class T > 
  class enable_shared_from_this;
  ```

* std::enable_shared_from_this 能让其一个对象（假设其名为 t ，且已被一个 std::shared_ptr 对象 pt 管理）**安全地生成其他额外的** std::shared_ptr 实例（假设名为 pt1, pt2, … ） ，**它们与 pt 共享对象 t 的所有权**

* 若一个类 T **继承** std::enable_shared_from_this ，**则会为该类 T 提供成员函数**： shared_from_this 。 当 T 类型对象 t 被一个为名为 pt 的 std::shared_ptr 类对象管理时，调用 T::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr 对象，它**与 pt 共享 t 的所有权**
