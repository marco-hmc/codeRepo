
**37. 从各个方面使得std::threads unjoinable**

每一个std::thread类型的对象都处于两种状态：joinable和unjoinable

+ joinable：对应底层已运行、可运行或者运行结束的出于阻塞或者等待调度的线程
+ unjoinable： 默认构造的std::thread, 已move的std::thread, 已join的std::thread, 已经分离的std::thread
+ 如果某一个std::thread是joinable的，然后他被销毁了，会造成很严重的后果，（比如会造成隐式join（会造成难以调试的性能异常）和隐式detach（会造成难以调试的未定义行为）），所以我们要保证thread在所有路径上都是unjoinable的：
  
    class ThreadRAII{
    public:
        enum class DtorAction{join, detach};
        ThreadRAII(std::thread&& t, DtorAction a):action(a), t(std::move(t)){} //把线程交给ThreadRAII处理
        ~THreadRAII(){
            if(t.joinable()){
                if(action == DtorAction::join){
                    t.join();
                }
                else{
                    t.detach();                  //保证所有路径出去都是不可连接的
                }
            }
        }
    private:
        DtorAction action;
        std::thread t;    //成员变量最后声明thread
    }

**38. 知道不同线程句柄析构行为**

     _____           ___返回值___  std::promise _______
    |调用方|<--------|被调用方结果|<------------|被调用方|

因为被调用函数的返回值有可能在调用方执行get前就执行完毕了，所以被调用线程的返回值会保存在一个地方，所以会存在一个"共享状态"

所以在异步状态下启动的线程的共享状态的最后一个返回值是会保持阻塞的，知道该任务结束，返回值的析构函数在常规情况下，只会析构返回值的成员变量


#### 考虑对于单次事件通信使用

这段文本讨论了在多线程编程中，如何有效地进行单次事件通信。具体来说，它比较了使用标志位、线程锁和`std::promise`三种不同的方法来实现线程间的同步和通信。

1. **使用标志位(flag)**:
   - 代码示例中没有直接展示，但提到了一种常见的做法，即在一个线程中使用`while(!flag){}`循环等待另一个线程改变`flag`的值。这种方法简单，但它会导致忙等待（busy-waiting），浪费CPU资源，因为等待的线程会持续检查`flag`而不做任何有用的工作。

2. **使用线程锁**:
   - 文本提到可以使用线程锁来代替标志位，以避免忙等待。示例代码中，`std::lock_guard<std::mutex>`用于自动管理互斥锁，但示例似乎有误，因为它没有展示如何正确使用互斥锁来等待某个条件。正确的做法通常涉及到`std::condition_variable`，它可以与互斥锁一起使用，让线程在条件不满足时休眠，直到条件被另一个线程改变并通知。

3. **使用`std::promise`**:
   - 最后，文本推荐使用`std::promise`来进行单次事件通信。`std::promise`是一种同步机制，可以在一个线程中存储一个值或异常，然后在另一个线程中通过与之对应的`std::future`对象来检索这个值或异常。示例中，`detect`函数创建了一个线程`t`，这个线程会等待`std::promise`对象`p`的状态被设置。当`detect`函数调用`p.set_value()`时，`p`的状态被设置，`t`中的等待操作完成，`react`函数随后被执行。这种方法避免了忙等待，且只适用于一次性通信，但需要注意的是，它可能涉及到堆内存的使用。

总的来说，这段文本强调了在设计多线程程序时，应该避免使用忙等待策略，而应该考虑使用更高级的同步机制，如`std::promise`，来高效地进行线程间的单次事件通信。

## threads

- 作者以[NonRecurisiveMutest.cc](https://github.com/chenshuo/recipes/tree/master/thread/test)这个为例子,如果mutex是递归的话,push_back()可能(但不总是)导致迭代器失效,程序偶尔会crash,这种错误不好debug.
- 而这种偶发的crash,发生在调用函数和被调用函数都以为自己拿到了锁,如果恰好都在修改一个对象的时候,这时候就容易crash.
- 而如果使用非递归锁,这种错误就会提前暴露出来,死锁比偶发的crash总归是好debug.

- 线程同步的四项原则,尽量用高层同步方法(线程池/队列/倒计时等),mutex和cv都是非常底层的同步原语,在开发中往往都用更高级的工具.但是使用mutex和cv有一个好处就是,分析工具更便于分析;
- 种种优化方法在没有数据支持的情况下,是靠不住的.很多人误认为用锁会让程序变慢,但实际上影响性能的不是锁,而是锁争用.要学会在程序的复杂度和性能之间取得平衡,并考虑机器扩容的可能.
- 多机的可扩展能力比单机的性能优化更重要,更值得投入精力.
- 
对比过很多资料,最后的多线程入门资料还是在[leetcode](https://leetcode-cn.com/problems/print-in-order/solution/c-hu-chi-suo-tiao-jian-bian-liang-xin-hao-liang-yi/)



- ***什么是析构竞态?***

  ​	与其他面向对象语言不同,C++ 要求程序员自己管理对象的生命期,这在多线程环境下显得尤为困难.当一个对象能被多个线程同时看到,那么对象的销毁时机就会变得模糊不清,可能出现多种竞态条件:

  - 在即将析构一个对象时,从何而知是否有另外的线程正在执行该对象的成员函数?
  - 如何保证在执行成员函数期间,对象不会在另一个线程被析构?
  - 在调用某个对象的成员函数之前,如何得知这个对象还活着?它的析构函数会不会刚执行到一半?

  ​	解决这些 race condition 是 C++ 多线程编程面临的基本问题.本文试图以 shared_ptr 一劳永逸地解决这些问题,减轻 C++ 多线程编程的精神负担.

- ***什么是线程安全?***

  ​	依据<Java 并发编程实践>/<Java Concurrency in Practice>一书,一个线程安全的 class 应当满足三个条件:

  - 从多个线程访问时,其表现出正确的行为
  - 无论操作系统如何调度这些线程,无论这些线程的执行顺序如何交织
  - 调用端代码无需额外的同步或其他协调动作

  ​	依据这个定义,C++ 标准库里的大多数类都不是线程安全的,无论 std::string 还是 std::vector 或 std::map,因为这些类通常需要在外部加锁.

### 2. 实战篇

- ***如何从构造函数,实现线程安全?***

  对象构造要做到线程安全,惟一的要求是在构造期间不要泄露 this 指针,即

  - 不要在构造函数中注册任何回调
  - 也不要在构造函数中把 this 传给跨线程的对象
  - 即便在构造函数的最后一行也不行

  之所以这样规定,是因为在构造函数执行期间对象还没有完成初始化,如果 this 被泄露 (escape) 给了其他对象(其自身创建的子对象除外),那么别的线程有可能访问这个半成品对象,这会造成难以预料的后果.

- ***为什么线程安全的,析构函数这么麻烦?***

  ​	因为一般线程安全方法都是依赖于互斥锁的,而析构函数会在析构的过程中把锁给销毁.

  确保所有线程都已经停止使用对象:在销毁对象之前,你需要确保没有任何线程还在使用或者可能会使用这个对象.这可能需要使用一些同步机制,例如条件变量或者future,来等待所有线程完成.

  使用智能指针管理资源:在C++中,你可以使用智能指针(例如std::unique_ptr或std::shared_ptr)来管理对象.当没有任何指针指向对象时,对象会被自动销毁.这可以避免手动管理内存和资源的复杂性.

### 1. thread

#### 1.1 join和detach
* join和detach
* join:
    当你调用 join 时,它会等待被调用线程执行完毕,然后再继续执行主线程.换句话说,join 使得主线程等待被调用线程的完成.
    使用 join 可以确保在主线程继续执行之前,被调用线程的任务已经完成.这对于需要等待线程执行结果的情况很有用

* detach:
    当你调用 detach 时,它使得被调用线程成为后台线程,与主线程分离.主线程不再等待被调用线程的完成.
    使用 detach 可以使得主线程在后台线程运行的同时继续执行,而不必等待后台线程完成.这对于一些异步任务或长时间运行的任务很有用.

* 不使用join也不使用detach:
    在主线程退出时,可能会导致一些未定义行为,因为线程对象将被销毁,但线程本身可能仍在运行.
    以下是可能发生的情况:
    1. 程序可能终止,但线程可能仍在运行:
        如果主线程退出,而被创建的线程仍在运行,可能导致程序终止,但线程继续执行.这可能导致线程无法正确完成其任务,因为主线程已经退出.
        程序可能崩溃:

    2. 程序可能会崩溃:
        这是由于线程对象的销毁可能涉及到一些资源的释放,而线程本身仍在访问这些资源,导致未定义行为.
    3. 资源泄漏:
        如果线程分配了一些资源(例如内存),但在线程执行完毕前这些资源没有被释放,可能会导致资源泄漏.

#### 1.2 threadID

#### 1.3 joinable

### 2. mutex
mutex

Critical Section(临界区)是指一段代码或一段程序,其中包含对共享资源的访问或修改.在多线程或并发编程中,由于多个线程同时访问共享数据,为了防止竞争条件(Race Condition)和确保数据的一致性,需要通过同步机制将临界区保护起来.


#### 2.1 args
#### 2.2 lock_guard 2.3 unique_lock
是的,你的理解是正确的.

`std::lock_guard`和`std::unique_lock`都是RAII(Resource Acquisition Is Initialization)风格的互斥锁包装器,它们在构造时自动锁定互斥锁,在析构时自动解锁互斥锁.这种设计可以确保在函数退出(正常或异常)时自动释放锁,从而避免了因忘记解锁而导致的死锁.

`std::lock_guard`和`std::unique_lock`的主要区别在于,`std::unique_lock`提供了更多的灵活性:

1. **延迟锁定**:`std::unique_lock`可以在创建时不立即锁定互斥锁,然后在需要的时候再锁定.`std::lock_guard`则在创建时必须立即锁定互斥锁.

2. **所有权传递**:`std::unique_lock`是可移动的,这意味着你可以将锁的所有权从一个`std::unique_lock`对象转移到另一个.`std::lock_guard`则不可移动.

3. **手动锁定和解锁**:`std::unique_lock`提供了`lock`和`unlock`方法,允许你在任何时候手动锁定和解锁互斥锁.`std::lock_guard`则不提供这些方法.

因此,如果你需要更多的控制,例如延迟锁定/所有权传递或手动锁定和解锁,那么应该使用`std::unique_lock`.如果你只需要简单地锁定和解锁互斥锁,那么`std::lock_guard`可能是更好的选择,因为它更简单,且开销更小.

`std::adopt_lock`/`std::defer_lock` 和 `std::try_to_lock` 都是 `std::unique_lock` 的构造函数可以接受的锁策略参数,它们的含义和使用场景如下:

1. **std::adopt_lock**:这个策略表示互斥锁在构造锁对象时已经被锁定.当你已经手动锁定了一个互斥锁,然后想要将它的管理权交给 `std::unique_lock` 时,可以使用 `std::adopt_lock`.这样,`std::unique_lock` 在构造时就不会再次尝试锁定互斥锁,而是直接接管已经被锁定的互斥锁.

2. **std::defer_lock**:这个策略表示在构造 `std::unique_lock` 时不锁定互斥锁.你可以稍后手动调用 `std::unique_lock::lock` 方法来锁定互斥锁.这个策略在你需要延迟锁定互斥锁的情况下很有用.

3. **std::try_to_lock**:这个策略表示在构造 `std::unique_lock` 时尝试锁定互斥锁,如果互斥锁已经被锁定,则立即返回,不会阻塞.你可以检查 `std::unique_lock::owns_lock` 方法的返回值,来判断是否成功锁定了互斥锁.

在你给出的代码中,`std::lock(foo, bar)` 会同时锁定 `foo` 和 `bar` 互斥锁,然后使用 `std::adopt_lock` 策略创建 `std::unique_lock` 对象,接管已经被锁定的互斥锁.在 `task_b` 函数中,使用 `std::defer_lock` 策略创建 `std::unique_lock` 对象,然后使用 `std::lock(lck1, lck2)` 同时锁定两个 `std::unique_lock` 对象管理的互斥锁.这样可以避免因为锁定顺序的问题导致死锁.



`std::unique_lock` 和 `std::lock_guard` 都是 C++ 中用于管理互斥锁的类,但它们之间存在一些重要的区别:

1. **灵活性**:`std::unique_lock` 比 `std::lock_guard` 更灵活.`std::unique_lock` 允许你延迟锁定,手动锁定和解锁,以及尝试锁定.而 `std::lock_guard` 在构造时自动锁定互斥锁,在析构时自动解锁,不支持手动控制.

2. **所有权转移**:`std::unique_lock` 支持所有权的转移,这意味着你可以将一个 `std::unique_lock` 对象移动到另一个 `std::unique_lock` 对象.而 `std::lock_guard` 不支持所有权的转移.

3. **条件变量支持**:`std::unique_lock` 可以与 `std::condition_variable` 一起使用,以实现线程间的同步和通信.而 `std::lock_guard` 不支持与 `std::condition_variable` 一起使用.

4. **性能开销**:由于 `std::unique_lock` 提供了更多的功能,所以它的性能开销可能会比 `std::lock_guard` 稍大一些.

总的来说,如果你需要更多的控制和灵活性,或者需要使用条件变量,那么 `std::unique_lock` 是一个好的选择.如果你只需要简单地锁定和解锁互斥锁,那么 `std::lock_guard` 可能是一个更好的选择,因为它更简单,性能开销也可能更小.

是的,C++中确实有`std::shared_lock`.这是一个类模板,用于管理`std::shared_mutex`或`std::shared_timed_mutex`类型的互斥锁.

`std::shared_lock`的主要特性是它支持共享所有权语义.这意味着多个`std::shared_lock`可以同时拥有同一个互斥锁的共享所有权.当一个`std::shared_lock`拥有互斥锁的共享所有权时,其他线程可以获取互斥锁的共享所有权,但不能获取互斥锁的独占所有权.这在某些需要多个读者和单个写者的情况下非常有用.

`std::shared_lock`的使用方式与`std::unique_lock`类似.你可以在创建`std::shared_lock`时锁定互斥锁,也可以稍后手动调用`std::shared_lock::lock`或`std::shared_lock::lock_shared`方法来锁定互斥锁.当`std::shared_lock`被销毁时,它会自动释放互斥锁.

需要注意的是,`std::shared_lock`只能用于支持共享所有权语义的互斥锁,如`std::shared_mutex`和`std::shared_timed_mutex`.对于不支持共享所有权语义的互斥锁,如`std::mutex`,你应该使用`std::unique_lock`或`std::lock_guard`.


### 3. condition variable
`std::condition_variable`是C++中的一种同步原语,它可以用来在多线程环境中实现复杂的同步模式.以下是一些常见的用法:

1. **等待通知**:一个线程可以使用`std::condition_variable::wait`或`wait_for`/`wait_until`方法来等待另一个线程的通知.当`wait`被调用时,当前线程将被阻塞,直到另一个线程调用`std::condition_variable::notify_one`或`notify_all`方法.

2. **条件等待**:`std::condition_variable::wait`方法还可以接受一个谓词(返回`bool`的函数或函数对象).只有当这个谓词返回`true`时,`wait`才会返回.这可以用来实现条件等待:线程等待某个条件成立.


3. **唤醒一个或多个线程**:可以使用`std::condition_variable::notify_one`方法唤醒一个等待的线程,或者使用`std::condition_variable::notify_all`方法唤醒所有等待的线程.

以下是一个简单的例子,展示了如何使用`std::condition_variable`实现生产者-消费者模式:

```cpp
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

std::queue<int> produced_nums;
std::mutex m;
std::condition_variable cond_var;

void producer() {
    for (int i = 0; ; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        std::lock_guard<std::mutex> lock(m);
        produced_nums.push(i);
        cond_var.notify_all();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(m);
        cond_var.wait(lock, []{ return !produced_nums.empty(); });
        std::cout << "consuming " << produced_nums.front() << '\n';
        produced_nums.pop();
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
```

在这个例子中,生产者线程生成数字并将其放入队列,然后通知所有等待的消费者线程.消费者线程等待队列非空,然后从队列中取出并消费数字.

### 5. future

future是表示未来能够得到的值,具体什么时候能够得到,依赖于承诺对象的实现;什么是承诺对象?
promise和packaged_task就是承诺对象,但这些承诺对象set_value的时候,就可以执行future.get()

#### 5.1 async的入参解释

std::async 是 C++11 中引入的一个用于启动异步任务的函数.它的原型如下:

```cpp
template <class Fn, class... Args>
std::future<typename std::result_of<Fn(Args...)>::type> 
    async(std::launch policy, Fn&& f, Args&&... args);
```

这里是 std::async 函数的主要参数及其意义:

policy: 异步任务的启动策略,它是一个 std::launch 类型的枚举值.可能的值有:

std::launch::async:异步执行任务,可能会在新的线程中执行.
std::launch::deferred:延迟执行任务,直到调用 std::future 对象的 get 或 wait 函数时执行,可能在当前线程执行.
std::launch::async | std::launch::deferred:由系统自行选择执行方式,可能异步也可能延迟.
f: 要异步执行的函数或可调用对象.

args...: 传递给函数 f 的参数列表.

std::async 返回一个 std::future 对象,通过这个对象可以获取异步任务的结果.std::future 是一个轻量级的异步结果管理器,它提供了对异步任务的状态查询(是否完成/是否有异常等)以及获取最终结果的功能.

使用 std::async 可以方便地在后台执行任务,而调用 get 函数时,如果任务尚未完成,主线程会等待直到任务完成.这有助于充分利用多核系统的性能,将计算密集型任务分配到不同的线程中执行.

注意:在使用 std::async 时,需要小心选择适当的启动策略,以避免不必要的线程创建和上下文切换.

#### 5.2 promise && packaged_task

关于future,promise,packaged_task,async的理解,以下表述对吗?
promise和packaged_task都是还没有给出具体值的承诺对象,当给出具体数值的时候,就表示承诺实现,可以用于计算.
而async是表示会开一个异步线程进行计算,返回的是一个future的值,如果future的值计算好之后,就可以通过future.get()得到.

所以说,在一个异步计算中,promise和packaged_task是输入端的,async是输出端的.

#### 5.3 shared_future
`std::future`对象的设计是唯一所有权的,也就是说,一旦你从一个`std::future`对象中获取了值,这个`std::future`对象就不能再被用来获取值.这是因为`std::future::get`方法会移动(而不是复制)值或异常,这样可以避免不必要的复制,但也意味着你只能从一个`std::future`对象中获取值一次.

因此,如果你需要在多个线程中共享同一个值,你不能直接使用`std::future`,而应该使用`std::shared_future`.`std::shared_future`对象可以被多次拷贝和读取,这意味着你可以在多个线程中共享同一个值.

在你的代码中,你创建了一个`std::shared_future<int> sf`对象,并将它传递给了三个异步操作.这三个异步操作都可以通过`sf.get()`获取到同一个值.如果你试图直接使用`std::future<int> f`来做同样的事情,你会得到一个编译错误,因为`std::future`对象不能被拷贝.

* shared_future可以直接对一个promise变量使用get_future方法吗

不可以.`std::promise`的`get_future`方法只能返回一个`std::future`对象,而不是`std::shared_future`对象.如果你想要一个`std::shared_future`对象,你需要首先从`std::promise`获取一个`std::future`对象,然后调用`std::future`的`share`方法来获取一个`std::shared_future`对象.例如:

```cpp
std::promise<int> p;
std::future<int> f = p.get_future();
std::shared_future<int> sf = f.share();
```

在这段代码中,`sf`是一个`std::shared_future`对象,它与`f`共享同一个状态,也就是说,它们都可以获取到同一个值.


#### 5.4 packaged_task


是的,你的理解是正确的.

在你的代码示例中,`std::async`用于异步执行`is_prime`函数并返回一个`std::future`对象.这个`std::future`对象可以用来获取`is_prime`函数的返回值.在等待`is_prime`函数完成的同时,主线程可以继续执行其他任务.

`std::async`是一个高级工具,它自动处理线程的创建和销毁,使得异步编程变得更简单.如果你只需要在后台运行一个任务并获取其结果,那么`std::async`通常是最好的选择.

相比之下,`std::packaged_task`提供了更多的灵活性,但也需要更多的管理工作.`std::packaged_task`只是将一个任务和一个`std::future`对象关联起来,它并不创建线程.你需要自己创建一个`std::thread`并将`std::packaged_task`对象传递给它.这使得你可以更精细地控制线程的创建和销毁,以及任务的调度.例如,你可以将任务提交给一个线程池,或者在特定的时间点启动线程.

所以,如果你只是在简单的场景中使用异步编程,那么`std::async`通常是最好的选择.如果你需要更精细的控制,或者你正在实现一个线程池,那么`std::packaged_task`可能是更好的选择.


### 6. others
#### 6.1 如果函数返回一个future,对这个future不调用get(),会发生什么
如果你调用`std::async`但不将返回值存储在一个`std::future`对象中,那么一个临时的`std::future`对象会被创建.这个临时对象会在表达式结束时被销毁,销毁时会阻塞等待异步任务完成.

这就是为什么如果你不想阻塞当前线程,你不能简单地忽略`std::async`的返回值.你需要将返回的`std::future`对象存储在某个地方,以便在适当的时候等待任务完成.

如果你创建了一个`std::future`对象,但是没有调用`get()`方法,那么在`std::future`对象被销毁时,如果关联的异步操作(例如`std::async`)还没有完成,那么程序会阻塞,直到异步操作完成.

这是因为`std::future`的析构函数会检查关联的异步操作是否已经完成.如果没有完成,析构函数会阻塞,直到异步操作完成.这是为了确保异步操作能够安全地完成,而不会在还没有完成的情况下被强制停止.

如果你不想在`std::future`对象被销毁时阻塞,你可以调用`std::future::detach()`方法.这将使`std::future`对象与其关联的异步操作分离,这样,即使`std::future`对象被销毁,异步操作也会继续运行.

需要注意的是,如果你没有调用`get()`方法,那么你将无法获取异步操作的结果.此外,`get()`方法只能被调用一次,因为调用`get()`方法后,`std::future`对象会变为无效状态.

函数的返回值哪怕没有用变量接着,其实也是存在的,在外部函数结束的时候会被析构.

而`future`的析构又要确保`get()`方法完成,所以如果不接着,就会产生阻塞.


### 99. quiz
#### 1. new操作是如何保证线程安全的?
new操作的线程安全性是通过内存管理器实现的.内存管理器会使用一种称为锁的机制来保证在同一时刻只有一个线程可以分配或释放内存.当一个线程正在进行new操作时,其他试图进行new操作的线程将会被阻塞,直到第一个线程完成new操作.

需要注意的是,虽然new操作本身是线程安全的,但是如果你在多线程环境中使用new操作创建的对象,你仍然需要确保对这些对象的访问是线程安全的.例如,如果两个线程同时访问和修改同一个对象,可能会导致数据竞争和未定义的行为,除非你使用了适当的同步机制(如互斥锁)来保护这个对象.

在C++中,`new`操作本身是线程安全的.C++标准库保证了在多线程环境中,不同线程可以同时进行`new`操作而不会发生冲突.

`new`操作的线程安全性是通过内存管理器实现的.内存管理器会使用一种称为锁的机制来保证在同一时刻只有一个线程可以分配或释放内存.当一个线程正在进行`new`操作时,其他试图进行`new`操作的线程将会被阻塞,直到第一个线程完成`new`操作.

需要注意的是,虽然`new`操作本身是线程安全的,但是如果你在多线程环境中使用`new`操作创建的对象,你仍然需要确保对这些对象的访问是线程安全的.例如,如果两个线程同时访问和修改同一个对象,可能会导致数据竞争和未定义的行为,除非你使用了适当的同步机制(如互斥锁)来保护这个对象.

#### 2. 为什么一定要用while循环,而不是if判断?

```c++
  muduo::MutextLock mutex;
  muduo::Condition cond(mutex);
  std:deque<int> queue;
  
  //消费者
  int dequeue(){
      // queue pop掉最后一个,并返回
      MutexLockGuard lock(mutex);
      while(queue.emtpy()){ // 不能用if,必须用while,避免虚假唤醒
          cond.wait(); // 这一步会unlock mutex,并进入等待,不会与其他线程产生死锁
      }
      int top = queue.front();
      queue.pop_front();
      return top;
  }
  ```

- 简单来说就是cv有可能会出现[虚假唤醒](https://www.zhihu.com/question/271521213)的情况,用while,不用if的话就可以多次检验.
- 给一个虚假唤醒的场景,一个线程A,一个线程B被notify,但是A还没有获得锁,B线程先获得了锁,并消费了队列中的数据(或者说notify的条件又变成不满足了),线程B结束后,A获得了锁,但这个时候条件已经不满足了.

- 当一个线程在条件变量上调用`.wait()`方法并进入等待状态时,如果后来被另一个线程通过`.notify()`或`.notify_all()`唤醒,那么它会从`.wait()`方法的下一行代码开始执行.

- 但是,需要注意的是,唤醒并不意味着条件已经满足.这就是为什么我们通常在一个`while`循环中调用`.wait()`方法,循环的条件就是我们等待的条件.这样,每次线程被唤醒时,它都会检查条件是否满足,如果条件不满足,它会再次调用`.wait()`方法进入等待状态.
-   - 这就是所谓的"虚假唤醒",即线程被唤醒,但是条件并未满足.使用`while`循环可以避免因虚假唤醒导致的问题.


#### 3. atomic实现原理
- 不同平台原子操作的实现不一样,但多线程导致的数据冲突都是因为多核cpu同时在跑一份数据,本质上都是保证这个数据在不同cpu的时候,有且只有一个在进行操作.下面是cacheline lock的实现方法

- 首先每个cpu核心都有其对应的高速cache

![在这里插入图片描述](https://s2.loli.net/2022/04/14/IxfwdV2vROmhnS8.png)

1. CPU1发出"Read Invalidate"消息,其他CPU将原子变量所在的缓存无效,并从Cache返回数据.CPU1将Cache line置成Exclusive状态.然后将该**cache line标记locked**
2. 然后CPU1读取原子变量,修改,最后写入cache line.
3. 将cache line置位unlocked.

在步骤(1)和(3)之间,如果其他CPU(例如CPU1)尝试执行一个原子递增操作,CPU1会发送一个"Read Invalidate"消息,CPU0收到消息后,检查对应的cache line的状态是locked,暂时不回复消息(CPU1会一直等待CPU0回复Invalidate Acknowledge消息).直到cache line变成unlocked.这样就可以实现原子操作.我们称这种方式为锁cache line.这种实现方式必须要求操作的变量位于一个cache line.

#### 4.多核cpu的缓存以及如何保持缓存一致性
    (https://blog.csdn.net/zhizhengguan/article/details/121275331)
- 如果对多核cpu还存疑,可以继续看这个.
