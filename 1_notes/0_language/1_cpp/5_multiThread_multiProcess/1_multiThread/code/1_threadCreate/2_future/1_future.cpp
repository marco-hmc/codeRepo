#include <future>
#include <iostream>
#include <thread>

/*
    1. future是什么？
        future是一个异步任务的结果。当你启动一个异步任务时，你会得到一个future对象，这个对象可以用来获取异步任务的结果。
        你可以通过调用future的get()函数来获取异步任务的结果。get()函数会阻塞当前线程，直到异步任务完成并返回结果。

    2. future的get()函数是阻塞的吗？
        - `std::future`的`get`函数用于获取异步任务的结果，它会阻塞当前线程，直到异步任务完成并返回结果。
        - 如果异步任务抛出了异常，那么`get`函数会重新抛出这个异常。
        - 如果异步任务的结果已经被获取过了，那么`get`函数会立即返回结果，不会阻塞当前线程。

    3. future的wait()函数是干嘛的？
        - `std::future`的`wait`函数用于等待异步任务的完成。
        - 如果异步任务已经完成，那么`wait`函数会立即返回。
        - 如果异步任务还没有完成，那么`wait`函数会阻塞当前线程，直到异步任务完成。
    
    4. future有了get()，为什么还要wait()？
        - `std::future`的`get`函数用于获取异步任务的结果，它会阻塞当前线程，直到异步任务完成并返回结果。
        - `std::future`的`wait`函数用于等待异步任务的完成，它会阻塞当前线程，直到异步任务完成。
        - `get`函数会等待异步任务完成并返回结果，如果异步任务抛出了异常，那么`get`函数会重新抛出这个异常。
        - `wait`函数只会等待异步任务完成，不会获取结果，也不会重新抛出异常。
        - 如果你只是想等待异步任务的完成，而不需要获取结果，那么可以使用`wait`函数。
        - 简单来说就是一个用于有返回函数，一个用于无返回函数。
*/

int asyncFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}

int main() {
    std::future<int> result = std::async(std::launch::async, asyncFunction, 10);
    std::cout << "Doing some other work..." << std::endl;
    int value = result.get();
    std::cout << "The result is: " << value << std::endl;

    return 0;
}