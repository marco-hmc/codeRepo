#include <iostream>
#include <thread>

/*
    通过使用 thread_local 关键字，可以在多线程环境中为每个线程创建独立的变量副本，避免了多线程之间的数据竞争。
    每个线程对 thread_local 变量的修改不会影响其他线程的副本，从而提高了多线程程序的安全性和可靠性。
*/

thread_local int tls_var = 0;

void worker(int id) {
    tls_var = id;
    std::cout << "Thread " << id << " has tls_var = " << tls_var << std::endl;
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();

    return 0;
}