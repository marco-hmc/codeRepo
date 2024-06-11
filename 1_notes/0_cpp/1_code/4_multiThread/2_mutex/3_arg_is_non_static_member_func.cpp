#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Foo {
  mutex mtx1, mtx2;
  unique_lock<mutex> lock_1, lock_2;

public:
  Foo() : lock_1(mtx1, try_to_lock), lock_2(mtx2, try_to_lock) {}

  void first(function<void()> printFirst) {
    printFirst();
    lock_1.unlock();
  }
  void second(function<void()> printSecond) {
    lock_guard<mutex> guard(mtx1);
    printSecond();
    lock_2.unlock();
  }
  void third(function<void()> printThird) {
    lock_guard<mutex> guard(mtx2);
    printThird();
  }
};

void printFirst() {
  for (int i = 0; i < 5; i++)
    cout << "first" << endl;
}
void printSecond() {
  for (int i = 0; i < 5; i++)
    cout << "second" << endl;
}
void printThird() {
  for (int i = 0; i < 5; i++)
    cout << "third" << endl;
}

int main() {
  Foo f;
  thread t1(&Foo::first, &f, printFirst);
  thread t2(&Foo::second, &f, printSecond);
  thread t3(&Foo::third, &f, printThird);
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