#include <iostream>
#include <thread>

/*
   1. `joinable()`是什么？
      `joinable()`是`std::thread`类的一个成员函数。
      返回值表示是否可以调用`join`，只有在绑定函数后，且未调用`detach()`和`join()`之前返回true。
      用于检查一个`std::thread`对象是否关联一个活动的线程。

   2. 线程对象什么时候开始运行？
      当你创建一个`std::thread`对象并传递一个函数给它时，这个函数会在一个新的线程中立即开始运行。
      例如，如果你写`std::thread t(func);`
      那么`func`会在新的线程`t`中立即开始运行。

   3. 什么时候需要判断`joinable()`？
      在你尝试连接（join）或分离（detach）一个线程之前，你应该先检查它是否可以被连接或分离，这可以通过`std::thread::joinable()`来做。
      如果一个线程不是joinable的，那么尝试连接或分离它会导致程序行为未定义。
      此外，如果你在析构一个线程对象时，它仍然是joinable的，那么程序会终止。
      因此，你应该在析构线程对象之前，确保它不是joinable的，或者连接或分离它。

   4. 为什么对于线程一定要调用.join()或者.detach()?
      如果不调用.join()或者.detach()，那么程序会抛出异常，因为线程对象会在析构时调用join()，而此时线程已经结束了。
      而声明.join()模式为默认的，肯定是不符合预期的；声明.detach()模式为默认的，容易不安全。
      其他语言，其实是没有.detach()概念的。相对应地，他们区分了不同线程的概念。
      能够.detach()的概念一般就是守护线程，因此创建的时候就是detach的。
*/

void myThread() {
    // do stuff...
}

int main() {
    std::thread foo;
    std::thread bar(myThread);

    std::cout << "Joinable after construction:\n" << std::boolalpha;
    std::cout << "foo: " << foo.joinable() << '\n';
    std::cout << "bar: " << bar.joinable() << '\n';

    if (foo.joinable()) {
        foo.join();
    }
    if (bar.joinable()) {
        bar.join();
    }

    std::cout << "Joinable after joining:\n" << std::boolalpha;
    std::cout << "foo: " << foo.joinable() << '\n';
    std::cout << "bar: " << bar.joinable() << '\n';

    return 0;
}
