# 打造异常安全的共享锁——std::unique_lock和std::shared_lock

由于对于线程的操作严重依赖于操作系统，所以STL提供与系统无关的接口是非常明智的，当然STL也会提供线程间的同步操作。这样就不仅是能够启动和停止线程，使用STL库也能完成线程的同步操作。

本节中，我们将了解到STL中的互斥量和RAII锁。我们使用这些工具对线程进行同步时，也会了解STL中更多同步辅助的方式。

## How to do it...

我们将使用`std::shared_mutex`在独占(exclusive)和共享(shared)模式下来完成一段程序，并且也会了解到这两种方式意味着什么。另外，我们将不会对手动的对程序进行上锁和解锁的操作，这些操作都交给RAII辅助函数来完成：

1. 包含必要的头文件，并声明所使用的命名空间：

   ```c++
   #include <iostream>
   #include <shared_mutex>
   #include <thread>
   #include <vector>
   
   using namespace std;
   using namespace chrono_literals;

   shared_mutex shared_mut;

   using shrd_lck = shared_lock<shared_mutex>;
   using uniq_lck = unique_lock<shared_mutex>;

   static void print_exclusive()
   {
       uniq_lck l {shared_mut, defer_lock};
       
       if (l.try_lock()) {
       	cout << "Got exclusive lock.\n";
       } else {
       	cout << "Unable to lock exclusively.\n";
       }
   }

   static void exclusive_throw()
   {
       uniq_lck l {shared_mut};
       throw 123;
   }

   int main()
   {
       {
           shrd_lck sl1 {shared_mut};
           
           cout << "shared lock once.\n";

           {
               shrd_lck sl2 {shared_mut};
   
               cout << "shared lock twice.\n";
   
               print_exclusive();
           }

           cout << "shared lock once again.\n";
   
           print_exclusive();
       }
       cout << "lock is free.\n";

       try {
      		exclusive_throw();
       } catch (int e) {
       	cout << "Got exception " << e << '\n';
       }
   
       print_exclusive();
   }
   ```

10. 编译并运行这段代码则会得到如下的输出。前两行展示的是两个共享锁实例。然后，`print_exclusive`函数无法使用独占模式对互斥量上锁。在离开内部代码段后，第二个共享锁解锁，`print_exclusive`函数依旧会失败。在离开这个代码段后，将会对互斥量所持有的锁进行释放，这样`exclusive_throw`和`print_exclusive`最终才能对互斥量进行上锁：

   ```c++
   $ ./shared_lock
   shared lock once.
   shared lock twice.
   Unable to lock exclusively.
   shared lock once again.
   Unable to lock exclusively.
   lock is free.
   Got exception 123
   Got exclusive lock.
   ```

## How it works...

查阅C++文档时，我们会对不同的互斥量和RAII辅助锁有些困惑。在我们回看这节的代码之前，让我们来对STL的这两个部分进行总结。

**互斥量**

其为**mutual exclusion**的缩写。并发时不同的线程对于相关的共享数据同时进行修改时，可能会造成结果错误，我们在这里就可以使用互斥量对象来避免这种情况的发生，STL提供了不同特性的互斥量。不过，这些互斥量的共同点就是具有`lock`和`unlock`两个成员函数。

一个互斥量在解锁状态下时，当有线程对其使用`lock()`时，这个线程就获取了互斥量，并对互斥量进行上锁。这样，但其他线程要对这互斥量进行上锁时，就会处于阻塞状态，知道第一个线程对该互斥量进行释放。`std::mutex`就可以做到。

这里将STL一些不同的互斥量进行对比：

| 类型名                                                       | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [mutex](http://zh.cppreference.com/w/cpp/thread/mutex)       | 具有`lock`和`unlock`成员函数的标准互斥量。并提供非阻塞函数`try_lock`成员函数。 |
| [timed_mutex](http://zh.cppreference.com/w/cpp/thread/timed_mutex) | 与互斥量相同，并提供`try_lock_for`和`try_lock_until`成员函数，其能在某个时间段内对程序进行阻塞。 |
| [recursive_mutex](http://zh.cppreference.com/w/cpp/thread/recursive_mutex) | 与互斥量相同，不过当一个线程对实例进行上锁，其可以对同一个互斥量对象多次调用`lock`而不产生阻塞。持有线程可以多次调用`unlock`，不过需要和`lock`调用的次数匹配时，线程才不再拥有这个互斥量。 |
| [recursive_timed_mutex](http://zh.cppreference.com/w/cpp/thread/recursive_timed_mutex) | 提供与`timed_mutex`和`recursive_mutex`的特性。               |
| [shared_mutex](http://zh.cppreference.com/w/cpp/thread/shared_mutex) | 这个互斥量在这方面比较特殊，它可以被锁定为独占模式或共享模式。独占模式时，其与标准互斥量的行为一样。共享模式时，其他线程也可能在共享模式下对其进行上锁。其会在最后一个处于共享模式下的锁拥有者进行解锁时，整个互斥量才会解锁。其行为有些类似于`shared_ptr`，只不过互斥量不对内存进行管理，而是对锁的所有权进行管理。 |
| [shared_timed_mutex](http://zh.cppreference.com/w/cpp/thread/shared_timed_mutex) | 同时具有`shared_mutex`和`timed_mutex`两种互斥量独占模式和共享模式的特性。 |

**锁**

线程对互斥量上锁之后，很多事情都变的非常简单，我们只需要上锁、访问、解锁三步就能完成我们想要做的工作。不过对于有些比较健忘的开发者来说，在上锁之后，很容易忘记对其进行解锁，或是互斥量在上锁状态下抛出一个异常，如果要对这个异常进行处理，那么代码就会变得很难看。最优的方式就是程序能够自动来处理这种事情。这种问题很类似与内存泄漏，开发者在分配内存之后，忘记使用`delete`操作进行内存释放。

内存管理部分，我们有`unique_ptr`，`shared_ptr`和`weak_ptr`。这些辅助类可以很完美帮我们避免内存泄漏。互斥量也有类似的帮手，最简单的一个就是`std::lock_guard`。使用方式如下：

```c++
void critical_function()
{
    lock_guard<mutex> l {some_mutex};
    
    // critical section
}
```

`lock_guard`的构造函数能接受一个互斥量，其会立即自动调用`lock`，构造函数会直到获取互斥锁为止。当实例进行销毁时，其会对互斥量再次进行解锁。这样互斥量就很难陷入到`lock/unlock`循环错误中。

C++17 STL提供了如下的RAII辅助锁。其都能接受一个模板参数，其与互斥量的类型相同(在C++17中，编译器可以自动推断出相应的类型)：

| 名称                                                         | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [lock_guard](http://zh.cppreference.com/w/cpp/thread/lock_guard) | 这个类没有什么其他的，构造函数中调用`lock`，析构函数中调用`unlock`。 |
| [scoped_lock](http://zh.cppreference.com/w/cpp/thread/scoped_lock) | 与`lock_guard`类似，构造函数支持多个互斥量。析构函数中会以相反的顺序进行解锁。 |
| [unique_lock](http://zh.cppreference.com/w/cpp/thread/unique_lock) | 使用独占模式对互斥量进行上锁。构造函数也能接受一个参数用于表示超时到的时间，并不会让锁一直处于上锁的状态。其也可能不对互斥量进行上锁，或是假设互斥量已经锁定，或是尝试对互斥量进行上锁。另外，函数可以在`unique_lock`锁的声明周期中，对互斥量进行上锁或解锁。 |
| [shared_lock](http://zh.cppreference.com/w/cpp/thread/shared_lock) | 与`unique_lock`类似，不过所有操作都是在互斥量的共享模式下进行操作。 |

`lock_guard`和`scoped_lock`只拥有构造和析构函数，`unique_lock`和`shared_lock`就比较复杂了，但也更为通用。我们将在本章的后续章节中了解到，这些类型如何用于更加复杂的情况。

现在我们来回看一下本节的代码。虽然，只在单线程的上下文中运行程序，但是我们可以了解到如何对辅助锁进行使用。`shrd_lck`类型为`shared_lock<shared_mutex>`的缩写，并且其允许我们在共享模式下对一个实例多次上锁。当`sl1`和`sl2`存在的情况下，`print_exclusive`无法使用独占模式对互斥量进行上锁。

现在来看看处于独占模式的上锁函数：

```c++
int main()
{
    {
    	shrd_lck sl1 {shared_mut};
    	{
    		shrd_lck sl2 {shared_mut};
    		print_exclusive();
    	}
    	print_exclusive();
    }
    
    try {
    	exclusive_throw();
    } catch (int e) {
    	cout << "Got exception " << e << '\n';
    }
    
    print_exclusive();
}
```

`exclusive_throw`的返回也比较重要，即便是抛出异常退出，`exclusive_throw`函数依旧会让互斥量再度锁上。

因为`print_exclusive`使用了一个奇怪的构造函数，我们就再来看一下这个函数：

```c++
void print_exclusive()
{
    uniq_lck l {shared_mut, defer_lock};
    
    if (l.try_lock()) {
    	// ...
    }
}	
```

这里我们不仅提供了`shared_mut`，还有`defer_lock`作为`unique_lock`构造函数的参数。`defer_lock`是一个空的全局对象，其不会对互斥量立即上锁，所以我们可以通过这个参数对`unique_lock`不同的构造函数进行选择。这样做之后，我们可以调用`l.try_lock()`，其会告诉我们有没有上锁。在互斥量上锁的情况下，就可以做些别的事情了。如果的确有机会获取锁，依旧需要析构函数对互斥量进行清理。