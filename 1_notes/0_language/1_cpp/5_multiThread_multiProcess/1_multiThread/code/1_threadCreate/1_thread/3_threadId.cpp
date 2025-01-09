#include <iostream>
#include <thread>

/*
  1. 线程ID什么时候用？
    线程ID是一个唯一标识线程的值，通常在以下情况中使用：
    - 调试：当程序的行为出现问题，需要确定是哪个线程导致的问题时，线程ID可以帮助我们追踪线程的行为。
    - 日志记录：在多线程程序中，使用线程ID可以帮助我们在日志中区分来自不同线程的消息。
    - 线程同步：在某些情况下，我们可能需要知道哪个线程拥有某个资源，或者哪个线程正在执行某个任务。在这种情况下，线程ID可以作为线程的唯一标识。

  2. 线程ID如何保证唯一的？
    线程ID的唯一性是由操作系统和C++运行时系统保证的。当创建一个新线程时，系统会分配一个唯一的线程ID。
    这个ID在线程的整个生命周期中都是唯一的。当线程结束时，它的ID可以被回收并在未来重新使用。
    但是，任何时候，系统中的每个活动线程都有一个唯一的ID。
*/

namespace identifier1 {
    std::thread::id main_thread_id = std::this_thread::get_id();

    void is_main_thread() {
        if (main_thread_id == std::this_thread::get_id()) {
            std::cout << "This is the main thread.\n";
        } else {
            std::cout << "This is not the main thread.\n";
        }
    }

    void test_1() {
        is_main_thread();
        std::thread th(is_main_thread);
        th.join();
    }
}  // namespace identifier1

namespace identifier2 {

    thread_local int threadId;

    void printThreadId() { std::cout << "Thread ID: " << threadId << '\n'; }

    void test_1() {
        std::thread t1([] {
            threadId = 1;
            printThreadId();
        });

        std::thread t2([] {
            threadId = 2;
            printThreadId();
        });

        t1.join();
        t2.join();
    }
}  // namespace identifier2

int main() {
    identifier1::test_1();
    identifier2::test_1();
    return 0;
}
