#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

int factorial(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << std::endl;

    return res;
}

int main() {
    int x;
    //如果要从子线程获取变量到主线程，可以通过互斥锁和状态变量的形式，如果子线程计算完毕则notify_all,唤醒主进程
    //而除了互斥锁，和主线程这种比较繁琐的实现之外，还可以通过future实现。
    //如果是defereed参数，表示是到了get()函数之后才开始算。
    //如果是async参数，则表示开一个线程去计算。
    //std::future<int> fu = std::async(std::launch::async|std::launch::deferred, factorial, 4);
    std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
    x = fu.get();//get()函数会等待子线程结束，然后将返回值传给x.并且future对象只能被调用一次

    return 0;
}

