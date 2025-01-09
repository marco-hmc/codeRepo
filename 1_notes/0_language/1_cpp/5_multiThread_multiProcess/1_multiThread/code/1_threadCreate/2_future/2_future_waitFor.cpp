#include <chrono>
#include <future>
#include <iostream>
#include <thread>

/*
    1. std::future::wait_for()怎么用？
        - `std::future`的`wait_for`函数用于等待`std::future`对象的状态变为`ready`，它的参数是一个`std::chrono::duration`对象，表示等待的时间。
        - 如果`std::future`对象的状态在指定的时间内变为`ready`，那么`wait_for`函数会返回`std::future_status::ready`。
        - 如果`std::future`对象的状态在指定的时间内没有变为`ready`，那么`wait_for`函数会返回`std::future_status::timeout`。
        - 如果`std::future`对象的状态在指定的时间内没有变为`ready`，并且在等待的过程中抛出了异常，那么`wait_for`函数会返回`std::future_status::deferred`。
        - `wait_for`函数的返回值是一个`std::future_status`枚举类型的值，表示`std::future`对象的状态。
*/
namespace identifier1 {
    bool is_prime(int x) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for (int i = 2; i < x; ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }

    void test() {
        std::future<bool> fut = std::async(is_prime, 3045348722);
        std::cout << "checking, please wait";
        std::chrono::milliseconds span(10);

        while (fut.wait_for(span) == std::future_status::timeout) {
            std::cout << '.' << std::flush;
        }

        bool x = fut.get();  // retrieve return value
        std::cout << "\n3 " << (x ? "is" : "is not") << " prime.\n";
    }
}  // namespace identifier1

namespace identifier2 {

    void worker(std::future<void>& output) {
        std::packaged_task<void(bool&)> my_task{
            [](bool& done) { done = true; }};

        auto result = my_task.get_future();
        bool done = false;

        my_task.make_ready_at_thread_exit(done);  // execute task right away
        std::cout << "worker: done = " << std::boolalpha << done << '\n';

        auto status = result.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::timeout) {
            std::cout << "worker: result is not ready yet" << '\n';
        }

        output = std::move(result);
    }

    void test() {
        std::future<void> result;
        std::thread{worker, std::ref(result)}.join();
        auto status = result.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::ready) {
            std::cout << "main: result is ready" << '\n';
        }
    }
}  // namespace identifier2

int main() {
    identifier1::test();
    identifier2::test();

    return 0;
}
