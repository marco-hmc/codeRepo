#include <exception>
#include <future>
#include <iostream>

/*
  1. 使用future的时候，什么时候会抛出异常？
    1. `std::future::get()`：
        如果与`std::future`对象关联的异步操作抛出了一个未捕获的异常，那么`std::future::get()`会重新抛出这个异常。这是最常见的情况。

    2. `std::future::get()`：
        如果`std::future::get()`被调用了多次，它会抛出`std::future_error`异常，异常的错误条件为`std::future_errc::no_state`。

    3. `std::future::get()`：
        如果`std::future`对象没有与任何异步操作关联，也就是它是默认构造的，那么`std::future::get()`会抛出`std::future_error`异常，异常的错误条件为`std::future_errc::no_state`。

    4. `std::future::wait_for()`和`std::future::wait_until()`：
        如果`std::future`对象没有与任何异步操作关联，那么这两个函数会抛出`std::future_error`异常，异常的错误条件为`std::future_errc::no_state`。

    5. `std::async`：
        如果`std::async`无法启动新的线程（例如，因为系统资源不足），那么它会抛出`std::system_error`异常。
*/

int get_int() {
    std::cin.exceptions(std::ios::failbit);
    int x = 0;
    std::cin >> x;
    return x;
}

void test_1() {
    std::future<int> fut = std::async(get_int);
    std::cout << "Please, enter an integer value: ";

    try {
        int x = fut.get();
        std::cout << "You entered: " << x << '\n';
    } catch (std::exception &) {
        std::cout << "[exception caught]";
    }
}

/////////////////////////////////////////////////////////////////////////

void test_2() {
    std::promise<int> prom;

    try {
        prom.get_future();
        prom.get_future();
    } catch (std::future_error &e) {
        std::cout << "future_error caught: " << e.what() << '\n';
        // std::cout << "future_error caught: " << e.code().message() << '\n';
    }
}

int main() {
    test_1();
    test_2();
    return 0;
}
