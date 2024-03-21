## threads

#### (13)Linux中线程的同步方式有哪些?
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

