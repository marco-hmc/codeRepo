#include <future>
#include <iostream>
#include <thread>

/*
    1. 有了async, 有了thread，为什么还要有packaged_task？packaged_task有什么能力？
        * async 的特点与局限：
            async 主要用于异步编程，它基于协程的概念，通过 async/await 关键字让程序可以在等待某些耗时操作（比如 I/O 操作）时暂停执行，
            去执行其他任务，从而提高程序的并发效率。
            但它本质上是在单线程内通过协作式的调度来实现异步，适合处理大量 I/O 密集型任务场景。
            然而，对于那些需要真正并行执行的计算密集型任务，比如复杂的数学计算等，仅靠 async 并不能充分利用多核 CPU 的优势来实现真正的并行加速。
        * thread 的特点与局限：
            thread（线程）是操作系统层面提供的一种并发执行机制，通过创建多个线程可以实现真正的并行执行，能充分利用多核 CPU 资源来提升计算密集型任务的执行速度。
            不过，线程的使用相对复杂，需要考虑线程安全问题，比如多个线程访问共享资源时可能出现的数据竞争、死锁等情况，并且线程的创建、销毁等操作也有一定开销。
            另外，在一些场景下如果只是简单地想要执行一个可调用对象并获取其返回结果，用线程来处理略显繁琐，需要额外的机制来传递返回值等。
        * packaged_task 的独特作用
            packaged_task 则提供了一种更方便的方式来处理异步任务以及获取任务的返回结果，它可以将一个可调用对象（比如函数、函数对象、lambda 表达式等）包装起来，
            使得这个可调用对象可以被异步地执行（比如放到线程池中或者配合其他异步执行机制），并且能够方便地获取其返回值。
            它在一定程度上弥补了 async 和 thread 在特定任务处理场景下不够便捷的地方，提供了一种相对简洁且功能聚焦的任务包装和结果获取机制。

    2. 怎么理解packaged_task？
        * packaged_task 是一个模板类，它的模板参数是一个可调用对象的类型，比如函数指针、函数对象、lambda 表达式等。
        * packaged_task 的主要作用是将一个可调用对象包装起来，使得这个可调用对象可以被异步地执行，并且能够方便地获取其返回值。
        * packaged_task 的构造函数接受一个可调用对象作为参数，然后可以通过调用其 operator() 方法来执行这个可调用对象。
        * packaged_task 的 operator() 方法可以通过调用 get_future() 方法来获取一个 std::future 对象，通过这个 std::future 对象可以获取异步任务的返回值。
        * packaged_task 本身并不具备执行异步任务的能力，它需要配合其他机制（比如线程、线程池等）来实现异步执行。

    3. 注意事项
        * packaged_task 对象只能被移动，不能被复制。
        * packaged_task 对象只能被调用一次，即只能执行一次包装的可调用对象。
        * packaged_task 对象在执行完包装的可调用对象后，会自动释放资源，不需要手动释放。
        * packaged_task 对象的 operator() 方法可以被多次调用，但只有第一次调用会执行包装的可调用对象，后续调用会直接返回之前的结果。
        * 顺序一定是先packaged_task，再future，再thread，最后get()。
*/

namespace identifier {
    void test() {
        std::packaged_task<int()> task([]() { return 7; });
        std::future<int> result = task.get_future();  // run task in a thread
        std::thread(std::move(task)).detach();

        std::cout << "waiting...";
        result.wait();

        std::cout << "done!" << std::endl
                  << "future result is " << result.get() << '\n';
    }
}  // namespace identifier

///////////////////////////////////////////////////////////////////////

namespace identifier2 {
    std::future<int> launcher(std::packaged_task<int(int)> &tsk, int arg) {
        if (tsk.valid()) {
            std::future<int> ret = tsk.get_future();
            std::thread(std::move(tsk), arg).detach();
            return ret;
        }
        return std::future<int>();
    }

    void test() {
        std::packaged_task<int(int)> tsk([](int x) { return x * 2; });
        std::future<int> fut = launcher(tsk, 25);
        std::cout << "The double of 25 is " << fut.get() << ".\n";
    }
}  // namespace identifier2

//////////////////////////////////////////////////////////////////////////////

namespace identifier3 {

    int triple(int x) { return x * 3; }

    void test() {
        std::packaged_task<int(int)> tsk(triple);
        std::future<int> fut = tsk.get_future();
        tsk(33);
        std::cout << "The triple of 33 is " << fut.get() << ".\n";

        tsk.reset();
        fut = tsk.get_future();
        tsk(55);
        std::cout << "The triple of 33 is " << fut.get() << ".\n";

        tsk.reset();
        fut = tsk.get_future();
        std::thread(std::move(tsk), 99).detach();
        std::cout << "The triple of 99 is " << fut.get() << ".\n";
    }

}  // namespace identifier3

int main() {
    identifier::test();
    identifier2::test();
    identifier3::test();
    return 0;
}
