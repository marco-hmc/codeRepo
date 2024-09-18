#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable_any cv;

int cargo = 0;
bool shipment_available() { return cargo != 0; }

void consume(int n) {
  for (int i = 0; i < n; ++i) {
    mtx.lock();
    cv.wait(mtx, shipment_available);

    std::cout << cargo << '\n';
    cargo = 0;
    mtx.unlock();
  }
}

int main() {
  std::thread consumer_thread(consume, 10);

  for (int i = 0; i < 10; ++i) {
    while (shipment_available()) {
      std::this_thread::yield();
    }
    mtx.lock();
    cargo = i + 1;
    cv.notify_one();
    mtx.unlock();
  }

  consumer_thread.join();

  return 0;
}

/*
1. yield怎么用？
  用于让出当前线程的执行权。它的作用是提示操作系统当前线程愿意让出CPU时间片，从而允许其他线程运行。

2. 和wait相比，yield有什么优点？
  - yield不需要锁，wait需要锁。
  - yield不会阻塞当前线程，wait会阻塞当前线程。
  - yield只是让出CPU时间片，不会释放锁，wait会释放锁。

3. 也就是说yield让出cpu，但不进入阻塞状态，而wait让出cpu，进入阻塞状态。

4. 怎么理解让出cpu，但不进入阻塞状态？
  - 让出 CPU
    当一个线程调用std::this_thread::yield()时，
    它会提示操作系统当前线程愿意让出CPU时间片。
    这意味着当前线程主动放弃继续执行的机会，让操作系统调度其他线程运行。这对于提高系统的响应性和公平性非常有用，尤其是在多线程竞争资源的情况下。

  - 不进入阻塞状态
    调用 std::this_thread::yield()后，线程不会进入阻塞状态。
    这意味着线程仍然处于可运行状态，只是暂时放弃了当前的CPU时间片。
    操作系统会将该线程放回就绪队列中，等待下一个调度周期。
    这与进入阻塞状态（例如等待I/O操作或条件变量）不同，阻塞状态下线程会被挂起，直到满足特定条件或事件。

*/