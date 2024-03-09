## threads

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

#### 2.1 args
#### 2.2 lock_guard
#### 2.3 unique_lock
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

### 3. mutex
mutex

Critical Section(临界区)是指一段代码或一段程序,其中包含对共享资源的访问或修改.在多线程或并发编程中,由于多个线程同时访问共享数据,为了防止竞争条件(Race Condition)和确保数据的一致性,需要通过同步机制将临界区保护起来.


### 4. cv
`std::condition_variable` 是 C++ 中的一个类,它用于同步线程.特别是在某些情况下,一个线程需要等待另一个线程完成特定操作时,可以使用 `std::condition_variable`.

使用 `std::condition_variable` 的基本步骤如下:

1. **创建一个 `std::condition_variable` 对象**:这个对象将被用来同步线程.

2. **在等待线程中,使用 `std::condition_variable::wait` 方法**:这个方法会阻塞当前线程,直到另一个线程通知 `std::condition_variable` 对象.

3. **在通知线程中,使用 `std::condition_variable::notify_one` 或 `std::condition_variable::notify_all` 方法**:这些方法会唤醒一个或所有等待 `std::condition_variable` 对象的线程.

下面是一个简单的示例:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void printMessage() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{return ready;}); // 等待 ready 变为 true
    std::cout << "Hello, world!" << std::endl;
}

void setReady() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all(); // 通知所有等待的线程
}

int main() {
    std::thread t1(printMessage);
    std::thread t2(setReady);

    t1.join();
    t2.join();

    return 0;
}
```

在这个示例中,线程 `t1` 会等待 [`ready`](command:_github.copilot.openSymbolInFile?%5B%22codeRepo%2F1_notes%2F0_cpp%2F1_code%2F4_multiThread%2F3_conditionVariableAndSignal%2Fexample1.cpp%22%2C%22ready%22%5D "codeRepo/1_notes/0_cpp/1_code/4_multiThread/3_conditionVariableAndSignal/example1.cpp") 变为 `true`.线程 `t2` 会设置 [`ready`](command:_github.copilot.openSymbolInFile?%5B%22codeRepo%2F1_notes%2F0_cpp%2F1_code%2F4_multiThread%2F3_conditionVariableAndSignal%2Fexample1.cpp%22%2C%22ready%22%5D "codeRepo/1_notes/0_cpp/1_code/4_multiThread/3_conditionVariableAndSignal/example1.cpp") 为 `true`,然后通知所有等待 [`cv`](command:_github.copilot.openSymbolInFile?%5B%22codeRepo%2F1_notes%2F0_cpp%2F1_code%2F4_multiThread%2F3_conditionVariableAndSignal%2Fexample1.cpp%22%2C%22cv%22%5D "codeRepo/1_notes/0_cpp/1_code/4_multiThread/3_conditionVariableAndSignal/example1.cpp") 的线程.

`std::condition_variable::wait` 方法有两种形式,一种接受一个 `std::unique_lock` 参数,另一种接受一个 `std::unique_lock` 和一个谓词(即返回 `bool` 的函数或者 lambda 表达式).

1. `void wait (std::unique_lock<std::mutex>& lck);`:这个版本的 `wait` 方法会阻塞当前线程,直到另一个线程调用了 `notify_one` 或 `notify_all` 方法.`lck` 是一个已经锁定的 `std::unique_lock` 对象,`wait` 方法会在开始等待前解锁它,然后在被通知后重新锁定它.

2. `template <class Predicate> void wait (std::unique_lock<std::mutex>& lck, Predicate pred);`:这个版本的 `wait` 方法接受一个谓词作为第二个参数.这个谓词是一个返回 `bool` 的函数或者 lambda 表达式.`wait` 方法会一直阻塞当前线程,直到谓词返回 `true`.这个版本的 `wait` 方法在被通知后,会检查谓词的返回值.如果谓词返回 `false`,则 `wait` 方法会继续阻塞当前线程.这样可以避免虚假唤醒的问题.

在你给出的代码中:

```cpp
while (!ready) cv.wait(lck);
```

`cv.wait(lck)` 的参数 `lck` 是一个 `std::unique_lock` 对象,`wait` 方法会在开始等待前解锁它,然后在被通知后重新锁定它.`while (!ready)` 是一个谓词,只有当 `ready` 变为 `true` 时,`wait` 方法才会停止阻塞当前线程.

### 5. future

`std::future` 和 `std::async` 是 C++ 中用于异步编程的工具.

`std::future` 是一个模板类,它表示一个异步操作的结果.你可以使用 `std::future::get` 方法来获取异步操作的结果.如果异步操作还没有完成,`get` 方法会阻塞当前线程,直到异步操作完成.

`std::async` 是一个函数,它用于启动一个异步操作,并返回一个 `std::future` 对象.你可以传递一个函数或者 lambda 表达式给 `std::async`,这个函数或者 lambda 表达式就是异步操作的内容.

下面是一个简单的例子:

```cpp
#include <future>
#include <iostream>

int compute() {
    // 这里是一些耗时的计算...
    return 42;
}

int main() {
    // 启动异步操作
    std::future<int> fut = std::async(compute);

    // 在这里,你可以做一些其他的事情...

    // 获取异步操作的结果
    int result = fut.get();

    std::cout << "The result is " << result << std::endl;

    return 0;
}
```

在这个例子中,`std::async(compute)` 启动了一个异步操作,这个操作会在一个单独的线程中执行 `compute` 函数.然后,`std::async` 返回一个 `std::future` 对象,你可以使用这个对象来获取异步操作的结果.

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

#### 5.2 promise
