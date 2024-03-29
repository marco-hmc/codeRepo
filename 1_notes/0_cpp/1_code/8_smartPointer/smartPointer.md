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
### 2. quiz

#### 2. 异常安全
#### 3. weak_ptr

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

#### 智能指针使用注意事项

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
