#include <future>
#include <iostream>

int factorial(std::shared_future<int> f) {
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; i--)
        res *= i;
    std::cout << "Result is: " << res << '\n';

    return res;
}

int main() {
    std::promise<int> p; //想要从主线程中传入子线程的变量
    std::future<int> f = p.get_future();
    std::shared_future<int> sf = f.share();//shared_future可以被拷贝

    std::future<int> fu = std::async(std::launch::async,factorial, sf);
    std::future<int> fu2 = std::async(std::launch::async,factorial, sf);
    std::future<int> fu3 = std::async(std::launch::async,factorial, sf);

    p.set_value(4);

    return 0;
}

/*
1. `std::shared_future`的用途：
    `std::shared_future`是一个可以被多个线程共享的异步结果。
    它通常用于多个线程需要等待同一个任务完成的情况。
    当你有一个返回值的异步任务，并且你希望多个线程都能获取到这个返回值时，你可以使用`std::shared_future`。

2. `std::shared_future`和`std::future`的区别：
    主要的区别在于`std::future`只能被移动，而`std::shared_future`可以被复制。
    这意味着一个`std::future`的结果只能被一个线程获取，而一个`std::shared_future`的结果可以被多个线程获取。
    另外，`std::future::get`会移动结果，使得`std::future`变为无效状态，而`std::shared_future::get`则会复制结果，不会影响`std::shared_future`的状态。

3. `std::shared_future`的生命周期需要注意什么？
    `std::shared_future`的生命周期应该超过所有使用它的线程。
    如果一个线程还在等待`std::shared_future`的结果，而`std::shared_future`已经被销毁，那么这个线程将会遇到未定义的行为。
    因此，你需要确保`std::shared_future`在所有线程都获取到结果之后再销毁。
*/
