#include <future>
#include <iostream>
#include <thread>

/*
    1. 有了async, 有了thread，为什么还要有packaged_task？packaged_task有什么能力？

*/

namespace identifier {
    void test_1() {
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

    void test_2() {
        std::packaged_task<int(int)> tsk([](int x) { return x * 2; });
        std::future<int> fut = launcher(tsk, 25);
        std::cout << "The double of 25 is " << fut.get() << ".\n";
    }
}  // namespace identifier2

//////////////////////////////////////////////////////////////////////////////

namespace identifier3 {

    int triple(int x) { return x * 3; }

    void test_3() {
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
    identifier::test_1();
    identifier2::test_2();
    identifier3::test_3();
    return 0;
}
