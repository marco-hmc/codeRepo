
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

std::mutex mut_a;
std::mutex mut_b;

namespace identifier2 {
static void deadlock_func_1() {
  std::cout << "bad f1 acquiring mutex A..." << '\n';
  std::lock_guard<std::mutex> la{mut_a};
  std::this_thread::sleep_for(100ms);
  std::cout << "bad f1 acquiring mutex B..." << '\n';
  std::lock_guard<std::mutex> lb{mut_b};
  std::cout << "bad f1 got both mutexes." << '\n';
}

static void deadlock_func_2() {
  std::cout << "bad f2 acquiring mutex B..." << '\n';
  std::lock_guard<std::mutex> lb{mut_b};
  std::this_thread::sleep_for(100ms);
  std::cout << "bad f2 acquiring mutex A..." << '\n';
  std::lock_guard<std::mutex> la{mut_a};
  std::cout << "bad f2 got both mutexes." << '\n';
}
void test2() {
  {
    std::thread t1{deadlock_func_1};
    std::thread t2{deadlock_func_2};

    t1.join();
    t2.join();
  }
}
} // namespace identifier2

namespace identifier1 {
static void sane_func_1() {
  std::scoped_lock l{mut_a, mut_b};
  std::cout << "sane f1 got both mutexes." << '\n';
}

static void sane_func_2() {
  std::scoped_lock l{mut_b, mut_a};
  std::cout << "sane f2 got both mutexes." << '\n';
}

void test() {
  {
    std::thread t1{sane_func_1};
    std::thread t2{sane_func_2};

    t1.join();
    t2.join();
  }
}
} // namespace identifier1

std::mutex foo, bar;

namespace identifier3 {
void task_a() {
  std::lock(foo, bar); // foo.lock(); bar.lock(); // replaced by:
  std::cout << "task a\n";
  foo.unlock();
  bar.unlock();
}

void task_b() {
  std::lock(bar, foo); // bar.lock(); foo.lock(); // replaced by:
  std::cout << "task b\n";
  bar.unlock();
  foo.unlock();
}

void test3() {
  std::thread th1(task_a);
  std::thread th2(task_b);

  th1.join();
  th2.join();
}
} // namespace identifier3

int main() {
  identifier1::test();
  identifier2::test2();
  identifier3::test3();
}

/*
1. `std::scoped_lock`是什么，有什么用？
   `std::scoped_lock`是C++17引入的一个新特性，它是一个RAII风格的锁，用于管理一个或多个互斥锁的生命周期。当你创建一个`std::scoped_lock`对象时，它会自动以死锁避免的顺序锁定所有提供的互斥锁。当`std::scoped_lock`对象离开作用域时，它的析构函数会自动解锁所有的互斥锁。这样可以确保在发生异常或提前返回时，互斥锁总是被正确地解锁。

2. `std::scoped_lock`和`std::mutex`的区别是什么？
   `std::mutex`是一个互斥锁对象，它提供了基本的锁定和解锁操作。你需要手动调用`std::mutex::lock`和`std::mutex::unlock`来锁定和解锁互斥锁。如果你忘记解锁互斥锁，或者在异常发生时没有正确地解锁互斥锁，那么可能会导致死锁。
   `std::scoped_lock`是一个锁的包装器，它在构造时自动锁定互斥锁，在析构时自动解锁互斥锁。这样可以确保互斥锁总是被正确地解锁，即使在发生异常或提前返回的情况下。此外，`std::scoped_lock`还可以同时管理多个互斥锁，以避免死锁。
   总的来说，`std::mutex`提供了基本的锁定和解锁操作，而`std::scoped_lock`提供了自动的和安全的锁管理。

3. 简单来说，std::scoped_lock可以一次性锁定多个互斥锁。
    并且在锁定过程中，如果无法立即锁定所有互斥锁，它会自动释放已经锁定的互斥锁，然后重试，直到所有互斥锁都被锁定。这种行为可以避免死锁。
*/