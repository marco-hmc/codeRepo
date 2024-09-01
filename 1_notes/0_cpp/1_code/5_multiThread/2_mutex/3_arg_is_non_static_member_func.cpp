#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class Foo {
  std::mutex mtx1, mtx2;
  std::unique_lock<std::mutex> lock_1, lock_2;

public:
  Foo() : lock_1(mtx1, std::try_to_lock), lock_2(mtx2, std::try_to_lock) {}

  void first(const std::function<void()> &printFirst) {
    printFirst();
    lock_1.unlock();
  }
  void second(const std::function<void()> &printSecond) {
    std::lock_guard<std::mutex> guard(mtx1);
    printSecond();
    lock_2.unlock();
  }
  void third(const std::function<void()> &printThird) {
    std::lock_guard<std::mutex> guard(mtx2);
    printThird();
  }
};

void printFirst() {
  for (int i = 0; i < 5; i++) {
    std::cout << "first" << '\n';
  }
}
void printSecond() {
  for (int i = 0; i < 5; i++) {
    std::cout << "second" << '\n';
  }
}
void printThird() {
  for (int i = 0; i < 5; i++) {
    std::cout << "third" << '\n';
  }
}

int main() {
  Foo f;
  std::thread t1(&Foo::first, &f, printFirst);
  std::thread t2(&Foo::second, &f, printSecond);
  std::thread t3(&Foo::third, &f, printThird);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}

/*
1. 线程传入的函数是成员函数时，需要传入对象指针和成员函数指针。
2.
  其实成员函数和普通函数没有什么不同的，只是成员函数会有一个默认的`this`指针，指向调用它的对象。所以补上这个就好了。
*/