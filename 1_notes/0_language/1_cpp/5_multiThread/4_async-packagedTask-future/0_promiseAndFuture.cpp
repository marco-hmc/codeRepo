#include <future>
#include <iostream>
#include <thread>

/*
  1. promise怎么用？讲解一下用法。
    std::promise是C++11引入的一个类模板，它可以用于在一个线程中存储一个值或异常，然后在另一个线程中获取这个值或异常。
    这样可以实现线程间的同步。

    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    prom.set_value(10);
    int x = fut.get();

  2. std::future
    是一个类模板，它表示一个异步操作的结果。你可以调用std::future::get来获取异步操作的结果。
    如果异步操作还没有完成，std::future::get会阻塞，直到异步操作完成。

  3. std::future的设计意图是什么？
    可以看成是线程之间的通信。
    1. 如果要从子线程获取变量到主线程,可以通过互斥锁和状态变量的形式。
        若子线程计算完毕则notify_all,唤醒主进程
    2. 还可以通过future实现.

*/
int factorial(std::future<int> &f) {
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; i--) {
        res *= i;
    }

    std::cout << "Result is: " << res << '\n';
    return res;
}

void test_1() {
    int x = 0;
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::future<int> fu =
        std::async(std::launch::async, factorial, std::ref(f));

    p.set_value(4);
    x = fu.get();
    std::cout << "Result from Child: " << x << '\n';
}

//////////////////////////////////////////

void print_int(std::future<int> &fut) {
    int x = fut.get();
    std::cout << "value: " << x << '\n';
}

void test_has_function() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread th1(print_int, std::ref(fut));
    prom.set_value(10);
    th1.join();
}

int main() {
    test_1();
    test_has_function();
    return 0;
}
