## smartPtr

### 1. concepts
#### 1.1 unique_ptr

#### 1.2 shared_ptr

#### 1.3 weak_ptr
https://www.bilibili.com/video/BV1RD4y1W7hf/?spm_id_from=333.337.search-card.all.click&vd_source=8215bf938da2fb524fa6ffc652bb3c53

#### 1.4 释放器
默认情况下,智能指针对象在析构时只会释放其持有的堆内存(调用 delete 或者 delete[]),但是假设这块堆内存代表的对象还对应一种需要回收的资源(如操作系统的套接字句柄/文件句柄等),我们可以通过自定义智能指针的资源释放函数.假设现在有一个 Socket 类,对应着操作系统的套接字句柄,在回收时需要关闭该对象,我们可以如下自定义智能指针对象的资源析构函数,这里以 **std::unique_ptr** 为例:

智能指针的释放器(Deleter)是一个函数或者函数对象,当智能指针不再需要其所管理的资源时,会调用这个释放器来释放资源.

在C++的`std::unique_ptr`和`std::shared_ptr`中,你可以自定义释放器.这在管理非内存资源时非常有用,例如文件句柄/数据库连接等.

例如,你可以为`std::unique_ptr`定义一个释放器,用于关闭文件:

```cpp
struct FileDeleter
{
    void operator()(FILE* ptr) const
    {
        if (ptr)
        {
            fclose(ptr);
        }
    }
};

std::unique_ptr<FILE, FileDeleter> smartFile(fopen("file.txt", "r"));
```

在这个例子中,当`smartFile`离开其作用域时,它会自动调用`FileDeleter`来关闭文件.

同样,你也可以为`std::shared_ptr`定义一个释放器:

```cpp
std::shared_ptr<FILE> smartFile(fopen("file.txt", "r"), [](FILE* ptr){
    if (ptr)
    {
        fclose(ptr);
    }
});
```

## 智能指针

### 1. concepts

1. 为什么要有智能指针？

   智能指针（Smart Pointer）是C++中的一种对象，它像原始指针一样可以指向堆上的对象，但是它们有一个额外的特性：当没有任何指针指向一个对象时，该对象会被自动删除。这样可以避免内存泄漏，使得内存管理更加方便，因此被称为“智能”指针。

   简单来说，就是通过RAII保证作用域外自动被析构。

2. 为什么auto_ptr被淘汰了？

   `auto_ptr`是C++98中的一种智能指针，但是它有一些问题。最大的问题是，`auto_ptr`在复制或赋值时会改变所有权，这意味着原始的`auto_ptr`会失去对对象的所有权，这通常不是预期的行为。因此，在C++11中，`auto_ptr`被`unique_ptr`替代，`unique_ptr`提供了更清晰的所有权语义。

   简单来说，`auto_ptr`对所有权没有管理。指针彼此之间赋值，或者像函数传递的时候，所有权的管理有问题。
   > 什么是指针的所有权？拥有指针所有权的实体负责在适当的时候释放（delete）该指针指向的内存。简单来说，就是谁拥有，谁释放。拥有指针所有权的，需要负责释放。

   > 具体所有权的管理，是类似于移动语义，原始对象会失去对对对象的所有权，但是`auto_ptr`是c98标准，又没有正式的移动语义。具体表现就不深究了。

3. 有什么智能指针，分别怎么用？
在C++中，有三种主要的智能指针：`std::unique_ptr`，`std::shared_ptr`和`std::weak_ptr`。

   1. `std::unique_ptr`：这是一种独占所有权的智能指针，也就是说，同一时间只能有一个`unique_ptr`指向给定的对象。当`unique_ptr`离开其作用域时，它会自动删除其所指向的对象。你可以使用`std::move`来转移所有权。例如：

   ```cpp
   std::unique_ptr<int> ptr1(new int(5));
   std::unique_ptr<int> ptr2 = std::move(ptr1); // 所有权从ptr1转移到ptr2
   ```

   2. `std::shared_ptr`：这是一种共享所有权的智能指针。可以有多个`shared_ptr`指向同一个对象，对象会在最后一个指向它的`shared_ptr`被销毁时自动删除。例如：

   ```cpp
   std::shared_ptr<int> ptr1(new int(5));
   std::shared_ptr<int> ptr2 = ptr1; // ptr1和ptr2都指向同一个对象
   ```

   3. `std::weak_ptr`：这是一种不拥有所有权的智能指针，它指向一个由`shared_ptr`管理的对象。`weak_ptr`主要用于防止`shared_ptr`的循环引用问题。例如，如果你有两个`shared_ptr`对象互相引用，那么它们都不会被删除，这会导致内存泄漏。`weak_ptr`可以打破这种循环引用。例如：

   ```cpp
   std::shared_ptr<int> ptr1(new int(5));
   std::weak_ptr<int> ptr2 = ptr1; // ptr2是一个weak_ptr，不会增加ptr1的引用计数
   ```

4. 为什么要有weak_ptr？

   `weak_ptr`是一种特殊的智能指针，它可以指向`shared_ptr`所管理的对象，但是它不会增加该对象的引用计数。这意味着`weak_ptr`不会阻止对象被删除。`weak_ptr`主要用于解决`shared_ptr`的循环引用问题。例如，如果两个`shared_ptr`对象互相引用，那么它们都不会被删除，这会导致内存泄漏。通过使用`weak_ptr`，我们可以打破这种循环引用，避免内存泄漏。

---

### 2. unique_ptr

#### 2.1 unique_ptr是怎么保证所有权唯一的？
`std::unique_ptr`通过以下几种方式保证所有权的唯一性：

1. **禁止复制**：`std::unique_ptr`禁止复制构造和复制赋值，这意味着你不能将一个`unique_ptr`直接赋值给另一个`unique_ptr`。这样可以防止有两个`unique_ptr`同时拥有同一个对象的所有权。
2. **允许移动**：虽然`unique_ptr`禁止复制，但是它允许移动。这意味着你可以将一个`unique_ptr`的所有权转移给另一个`unique_ptr`。在所有权转移之后，原始的`unique_ptr`不再拥有任何对象，这样可以确保任何时候都只有一个`unique_ptr`拥有对象的所有权。
3. **自动删除**：当`unique_ptr`被销毁（例如离开其作用域）时，它会自动删除其所拥有的对象。这意味着你不需要手动删除对象，可以防止因忘记删除对象而导致的内存泄漏。

通过这三种方式，`std::unique_ptr`可以保证所有权的唯一性，从而避免内存泄漏和悬挂指针等问题。

---

### 3. shared_ptr

#### 3.1 shared_ptr是怎么控制所有权的？

`shared_ptr`是C++中的一种智能指针，它通过引用计数来控制所有权。每当一个新的`shared_ptr`指向某个对象，这个对象的引用计数就会增加。当`shared_ptr`被销毁或者重新指向其他对象时，原对象的引用计数就会减少。当引用计数变为0时，`shared_ptr`就会自动删除所指向的对象。

#### 3.2 多线程下的shared_ptr需要注意什么？
需要在复制构造函数和赋值运算符中正确地增加引用计数。
需要在析构函数中正确地减少引用计数，并在引用计数为0时删除原始指针。
需要处理自我赋值的情况。如果一个对象赋值给它自己，那么在减少引用计数并删除原始指针之前，必须先增加引用计数。
这个简单的实现不是线程安全的。在多线程环境中，可能需要使用互斥锁或原子操作来保证线程安全。
在多线程环境下使用`shared_ptr`时，需要注意的主要问题是线程安全。虽然`shared_ptr`的引用计数操作是线程安全的，但是这并不意味着使用`shared_ptr`的所有操作都是线程安全的。

例如，两个线程可能同时读取同一个`shared_ptr`，然后试图修改它所指向的对象。这种情况下，就需要额外的同步机制（如互斥锁）来保证操作的原子性。

另外，如果一个线程正在读取`shared_ptr`，而另一个线程正在修改`shared_ptr`（例如，使其指向另一个对象），那么也可能会出现问题。为了避免这种情况，可以使用`std::atomic_load`和`std::atomic_store`等函数。

简单来说，`std::shared_ptr`在C++标准库中的实现确实提供了线程安全的引用计数。这是通过原子操作实现的。

但是外部使用的时候，还是外部需要上锁。

#### 3.3 如何实现一个引用计数指针,以及其中要注意的点?

1. 需要在复制构造函数和赋值运算符中正确地增加引用计数。
2. 需要在析构函数中正确地减少引用计数，并在引用计数为0时删除原始指针。
3. 需要处理自我赋值的情况。如果一个对象赋值给它自己，那么在减少引用计数并删除原始指针之前，必须先增加引用计数。
4. 在多线程环境中，可能需要使用互斥锁或原子操作来保证线程安全。

### 4. weak_ptr
#### 4.1 weak_ptr是怎么解决循环引用计数问题的？
`std::weak_ptr`是一种特殊的智能指针，它被设计用来解决`std::shared_ptr`的循环引用问题。

循环引用发生在两个或更多的`std::shared_ptr`实例互相引用，形成一个闭环。在这种情况下，即使没有任何外部的`std::shared_ptr`指向这些对象，它们的引用计数也永远不会变为0，因此这些对象永远不会被删除，导致内存泄露。

`std::weak_ptr`可以打破这个循环。它是一种弱引用，不会增加引用计数。你可以将`std::weak_ptr`看作是一种安全的观察者，它可以观察`std::shared_ptr`所管理的对象，但不会阻止这个对象被删除。

当你需要使用`std::weak_ptr`所观察的对象时，可以调用`std::weak_ptr::lock`方法。这个方法会返回一个新的`std::shared_ptr`实例，如果对象还存在的话。如果对象已经被删除，`lock`方法就会返回一个空的`std::shared_ptr`。

通过这种方式，`std::weak_ptr`可以安全地解决`std::shared_ptr`的循环引用问题。

#### 4.2 weak_ptr的特点

**std::weak_ptr** 是一个不控制资源生命周期的智能指针,是对对象的一种弱引用,只是提供了对其管理的资源的一个访问手段,引入它的目的为协助 **std::shared_ptr** 工作.
**std::weak_ptr** 可以从一个 **std::shared_ptr** 或另一个 **std::weak_ptr** 对象构造,**std::shared_ptr** 可以直接赋值给 **std::weak_ptr** ,也可以通过 **std::weak_ptr** 的 **lock()** 函数来获得 **std::shared_ptr**.它的构造和析构不会引起引用计数的增加或减少.**std::weak_ptr** 可用来解决 **std::shared_ptr** 相互引用时的死锁问题(即两个**std::shared_ptr** 相互引用,那么这两个指针的引用计数永远不可能下降为 0, 资源永远不会释放).

### 5. `std::enable_share_from_this`
c11特性
* 为什么要用 `enable_shared_from_this`？

  * **需要在类对象的内部中获得一个指向当前对象的 shared_ptr 对象**
  * 如果在一个程序中，对象内存的生命周期全部由智能指针来管理。在这种情况下，**要在一个类的成员函数中，对外部返回this指针就成了一个很棘手的问题**

* 什么时候用？

  - 当一个类被 `share_ptr` 管理，且在**类的成员函数里需要把当前类对象作为参数传给其他函数时**，这时就需要传递一个指向自身的 `share_ptr`

* 如何安全地将 this 指针返回给调用者?

  - **一般来说，我们不能直接将this指针返回**。**如果函数将 this 指针返回到外部某个变量保存，然后这个对象自身已经析构了，但外部变量并不知道，此时如果外部变量再使用这个指针，就会使得程序崩溃**

### 99. quiz

#### 1. C++垃圾回收,shared_ptr的引用计数出现循环引用怎么办

在C++中，`std::shared_ptr`通过引用计数来管理内存，但是如果出现循环引用，就会导致内存泄漏。循环引用是指两个或更多的`std::shared_ptr`互相引用，形成一个闭环，这样每个`std::shared_ptr`的引用计数永远不会降到0，导致内存无法被释放。

解决循环引用的一种方法是使用`std::weak_ptr`。`std::weak_ptr`是一种不控制所指向对象生命周期的智能指针，它指向一个由`std::shared_ptr`管理的对象。将循环引用中的一部分引用改为`std::weak_ptr`，可以打破循环引用，解决内存泄漏问题。

以下是一个例子：

```c++
#include <memory>

class B;

class A {
public:
    std::shared_ptr<B> b_ptr;
};

class B {
public:
    std::weak_ptr<A> a_ptr;  // 使用weak_ptr打破循环引用
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a;
}
```

在这个例子中，`A`和`B`互相引用，但是`B`到`A`的引用是一个`std::weak_ptr`，这样就打破了循环引用，当`A`和`B`的生命周期结束时，内存可以被正确释放。

#### 2. 智能指针如何变为常量形式的？

```cpp
struct MyClass {
    int value;
};

std::shared_ptr<const MyClass> ptr = std::make_shared<MyClass>();

// 下面的代码将无法编译，因为ptr指向一个常量对象
// ptr->value = 42;
```


**28. 智能(smart)指针**

auto_ptr：会把值给传出去，原来的指针作废掉
实现dereference（取出指针所指东西的内容）：
    template<class T>
    T& SmartPtr<T>::operaotr*()const{
        return *pointee;
    }

    template<class T>
    T* SmartPtr<T>::operator->()const{
        return pointee;
    }

测试smart pointer是否是NULL：
如果直接使用下面的代码是错误的：
    
    SmartPtr<TreeNode> ptn;
    if(ptn == 0)... //error
    if(ptn)... //error
    if(!ptn)... //error
所以需要进行隐式类型转换操作符，才能够进行上面的操作
    
    template<class T>
    class SmartPtr{
    public:
        operator void*();
    };
    SmartPtr<TreeNode> ptn;
    if(ptn == 0) //现在正确
    if(ptn) //现在正确
    if(!ptn) //现在正确

smart pointer 和继承类/基类的类型转换:

    class MusicProduct{....};
    class Cassette:public MusicProduct{....};
    class CD:public MusicProduct{....};
    displayAndPlay(const SmartPtr<MusicProduct>& pmp, int numTimes);
    
    SmartPtr<Cassette> funMusic(new Cassette("1234"));
    SmartPtr<CD> nightmareMusic(new CD("143"));
    displayAndPlay(funMusic, 10); // 错误!
    displayAndPlay(nightmareMusic, 0); // 错误!
我们可以看到的是，如果没有隐式转换操作符的话，是没有办法进行转换的，那么解决方法就是添加一个操作符,：
    
    class SmartPtr<Cassette>{//或者用模板来代替
    public:
        operator SmartPtr<MusicProduct>(){
            return SmartPtr<MusicProduct>(pointee);
        }
    };
smart pointer 和 const：
    
    SmartPtr<CD> p; //non-const 对象 non-const 指针
    SmartPtr<const CD> p; //const 对象 non-const 指针
    const SmartPtr<CD> p = &goodCD; //non-const 对象 const 指针
    const SmartPtr<const CD> p = &goodCD; //const 对象 const 指针
    
    template<class T>      // 指向const对象的
    class SmartPtrToConst{ //灵巧指针
        ...                // 灵巧指针通常的成员函数
    protected:
        union {
            const T* constPointee; // 让 SmartPtrToConst 访问
            T* pointee; // 让 SmartPtr 访问
        };
    };
    
    template<class T> // 指向 non-const 对象的灵巧指针
    class SmartPtr: public SmartPtrToConst<T> {
        ... // 没有数据成员
    };


**20. 对于类似于std::shared_ptr的指针使用std::weak_ptr可能造成悬置**

weak_ptr通常由一个std::shared_ptr来创建，他们指向相同的地方，但是weak_ptr并不会影响到shared_ptr的引用计数：
    
    auto spw = std::make_shared<Widget>();//spw 被构造之后被指向的Widget对象的引用计数为1(欲了解std::make_shared详情，请看Item21)
    std::weak_ptr<Widget> wpw(spw);//wpw和spw指向了同一个Widget,但是RC(这里指引用计数，下同)仍旧是1
    spw = nullptr;//RC变成了0，Widget也被析构，wpw现在处于悬挂状态
    if(wpw.expired())... //如果wpw悬挂...
那么虽然weak_ptr看起来没什么用，但是他其实也有一个应用场合（用来做缓存）：
    
    std::unique_ptr<const Widget> loadWidget(WidgetID id); //假设loadWidget是一个很繁重的方法，需要对这个方法进行缓存的话，就需要用到weak_ptr了：
    
    std::shared_ptr<const Widget> fastLoadWidget(WidgetId id){
        static std::unordered_map<WidgetID,
        std::weak_ptr<const Widget>> cache;
        auto objPtr = cache[id].lock();//objPtr是std::shared_ptr类型指向了被缓存的对象(如果对象不在缓存中则是null)
        if(!objPtr){
            objPtr = loadWidget(id);
            cache[id] = objPtr;
        }   //如果不在缓存中，载入并且缓存它
        return objPtr;
    }
+ std::weak_ptr 用来模仿类似std::shared_ptr的可悬挂指针
+ 潜在的使用 std::weak_ptr 的场景包括缓存，观察者列表，以及阻止 std::shared_ptr 形成的环


#### 3. 异常安全

#### 4. weak_ptr

- 分清楚场合应该使用哪种类型的智能指针;

  通常情况下,如果你的资源不需要在其他地方共享,那么应该优先使用 **std::unique_ptr**,反之使用 **std::shared_ptr**,当然这是在该智能指针需要管理资源的生命周期的情况下;如果不需要管理对象的生命周期,请使用 **std::weak_ptr**.

和 **std::unique_ptr** 一样,你应该优先使用 **std::make_shared** 去初始化一个 **std::shared_ptr** 对象.

**std::enable_shared_from_this**

实际开发中,有时候需要在类中返回包裹当前对象(this)的一个 **std::shared_ptr** 对象给外部使用,C++ 新标准也为我们考虑到了这一点,有如此需求的类只要继承自 **std::enable_shared_from_this** 模板对象即可.用法如下:


上述代码中,类 A 的继承 **std::enable_shared_from_this** 并提供一个 **getSelf()** 方法返回自身的 **std::shared_ptr** 对象,在 **getSelf()** 中调用 **shared_from_this()** 即可.

**std::enable_shared_from_this** 用起来比较方便,但是也存在很多不易察觉的陷阱.

**陷阱一:不应该共享栈对象的 this 给智能指针对象**

假设我们将上面代码 main 函数 **25** 行生成 A 对象的方式改成一个栈变量,即:

```
//其他相同代码省略...

int main()
{
    A a;

    std::shared_ptr<A> sp2 = a.getSelf();

    std::cout << "use count: " << sp2.use_count() << std::endl;

    return 0;
}
```

运行修改后的代码会发现程序在 `std::shared_ptr sp2 = a.getSelf();` 产生崩溃.这是因为,智能指针管理的是堆对象,栈对象会在函数调用结束后自行销毁,因此不能通过 **shared_from_this()** 将该对象交由智能指针对象管理.切记:**智能指针最初设计的目的就是为了管理堆对象的(即那些不会自动释放的资源)**.

**陷阱二:避免 std::enable_shared_from_this 的循环引用问题**

再来看另外一段代码:

```
// test_std_enable_shared_from_this.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A>
{
public:
    A()
    {
        m_i = 9;
        //注意:
        //比较好的做法是在构造函数里面调用shared_from_this()给m_SelfPtr赋值
        //但是很遗憾不能这么做,如果写在构造函数里面程序会直接崩溃

        std::cout << "A constructor" << std::endl;
    }

    ~A()
    {
        m_i = 0;

        std::cout << "A destructor" << std::endl;
    }

    void func()
    {
        m_SelfPtr = shared_from_this();
    }

public:
    int                 m_i;
    std::shared_ptr<A>  m_SelfPtr;

};

int main()
{
    {
        std::shared_ptr<A> spa(new A());
        spa->func();
    }

    return 0;
}
```

乍一看上面的代码好像看不出什么问题,让我们来实际运行一下看看输出结果:

```
[root@myaliyun testmybook]# g++ -g -o test_std_enable_shared_from_this_problem test_std_enable_shared_from_this_problem.cpp
[root@myaliyun testmybook]# ./test_std_enable_shared_from_this_problem
A constructor
```

```
#include <iostream>
#include <memory>

int main()
{
    //创建一个std::shared_ptr对象
    std::shared_ptr<int> sp1(new int(123));
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过构造函数得到一个std::weak_ptr对象
    std::weak_ptr<int> sp2(sp1);
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过赋值运算符得到一个std::weak_ptr对象
    std::weak_ptr<int> sp3 = sp1;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过一个std::weak_ptr对象得到另外一个std::weak_ptr对象
    std::weak_ptr<int> sp4 = sp2;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    return 0;
}
```

程序执行结果如下:

```
[root@myaliyun testmybook]# g++ -g -o test_weak_ptr test_weak_ptr.cpp 
[root@myaliyun testmybook]# ./test_weak_ptr
use count: 1
use count: 1
use count: 1
use count: 1
```

无论通过何种方式创建 **std::weak_ptr** 都不会增加资源的引用计数,因此每次输出引用计数的值都是 1.

既然,**std::weak_ptr** 不管理对象的生命周期,那么其引用的对象可能在某个时刻被销毁了,如何得知呢?**std::weak_ptr** 提供了一个 **expired()** 方法来做这一项检测,返回 true,说明其引用的资源已经不存在了;返回 false,说明该资源仍然存在,这个时候可以使用 **std::weak_ptr** 的 **lock()** 方法得到一个 **std::shared_ptr** 对象然后继续操作资源,以下代码演示了该用法:

```
//tmpConn_ 是一个 std::weak_ptr<TcpConnection> 对象
//tmpConn_引用的TcpConnection已经销毁,直接返回
if (tmpConn_.expired())
    return;

std::shared_ptr<TcpConnection> conn = tmpConn_.lock();
if (conn)
{
    //对conn进行操作,省略...
}
```

有读者可能对上述代码产生疑问,既然使用了 **std::weak_ptr** 的 **expired()** 方法判断了对象是否存在,为什么不直接使用 **std::weak_ptr** 对象对引用资源进行操作呢?实际上这是行不通的,**std::weak_ptr** 类没有重写 **operator->** 和 **operator*** 方法,因此不能像 **std::shared_ptr** 或 **std::unique_ptr** 一样直接操作对象,同时 **std::weak_ptr** 类也没有重写 **operator!** 操作,因此也不能通过 **std::weak_ptr** 对象直接判断其引用的资源是否存在:

```
#include <memory>

class A
{
public:
    void doSomething()
    {

    }
};

int main()
{    
    std::shared_ptr<A> sp1(new A());

    std::weak_ptr<A> sp2(sp1);

    //正确代码
    if (sp1)
    {
        //正确代码
        sp1->doSomething();
        (*sp1).doSomething();
    }

    //正确代码
    if (!sp1)
    {

    }

    //错误代码,无法编译通过
    //if (sp2)
    //{
    //    //错误代码,无法编译通过
    //    sp2->doSomething();
    //    (*sp2).doSomething();
    //}

    //错误代码,无法编译通过
    //if (!sp2)
    //{

    //}

    return 0;
}
```

之所以 **std::weak_ptr** 不增加引用资源的引用计数不管理资源的生命周期,是因为,即使它实现了以上说的几个方法,调用它们也是不安全的,因为在调用期间,引用的资源可能恰好被销毁了,这会造成棘手的错误和麻烦.

因此,**std::weak_ptr** 的正确使用场景是那些资源如果可能就使用,如果不可使用则不用的场景,它不参与资源的生命周期管理.例如,网络分层结构中,Session 对象(会话对象)利用 Connection 对象(连接对象)提供的服务工作,但是 Session 对象不管理 Connection 对象的生命周期,Session 管理 Connection 的生命周期是不合理的,因为网络底层出错会导致 Connection 对象被销毁,此时 Session 对象如果强行持有 Connection 对象与事实矛盾.

**std::weak_ptr** 的应用场景,经典的例子是订阅者模式或者观察者模式中.这里以订阅者为例来说明,消息发布器只有在某个订阅者存在的情况下才会向其发布消息,而不能管理订阅者的生命周期.

```
class Subscriber
{

};

class SubscribeManager
{
public:
    void publish()
    {
        for (const auto& iter : m_subscribers)
        {
            if (!iter.expired())
            {
                //TODO:给订阅者发送消息
            }
        }
    }

private:
    std::vector<std::weak_ptr<Subscriber>>   m_subscribers;
};
```

#### 5. 智能指针使用注意事项

- 一旦一个对象使用智能指针管理后,就不该再使用原始裸指针去操作;
  看一段代码:

记住,一旦智能指针对象接管了你的资源,所有对资源的操作都应该通过智能指针对象进行,不建议再通过原始指针进行操作了.当然,除了 **std::weak_ptr**,**std::unique_ptr** 和 **std::shared_ptr** 都提供了获取原始指针的方法__**get()** 函数.

  ```cpp
  int main()
  {    
    Subscriber* pSubscriber = new Subscriber();
  
    std::unique_ptr<Subscriber> spSubscriber(pSubscriber);
  
    //pTheSameSubscriber和pSubscriber指向同一个对象
    Subscriber* pTheSameSubscriber= spSubscriber.get();
  
    return 0;
  }
  ```

- 认真考虑,避免操作某个引用资源已经释放的智能指针;

  ```cpp
  //连接断开
  void MonitorServer::OnClose(const std::shared_ptr<TcpConnection>& conn)
  {    
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
    {
        //通过比对connection对象找到对应的session
        if ((*iter)->GetConnectionPtr() == conn)
        {
            m_sessions.erase(iter);
            //注意这里:程序在此处崩溃
            LOGI("monitor client disconnected: %s", conn->peerAddress().toIpPort().c_str());
            break;
        }
    }
  }
  ```
  崩溃原因是传入的 conn 对象和上一个例子中的 sp2 一样都是另外一个 **std::shared_ptr** 的引用,当连接断开时,对应的 TcpConnection 对象可能早已被销毁,而 conn 引用就会变成空指针(严格来说是不再拥有一个 TcpConnection 对象),此时调用 TcpConnection 的 peerAddress() 方法就会产生和上一个示例一样的错误.
