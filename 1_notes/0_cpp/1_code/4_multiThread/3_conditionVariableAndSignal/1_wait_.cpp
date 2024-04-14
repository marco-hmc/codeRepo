#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Foo {
public:
  void first(function<void()> printFirst) {
    printFirst();
    k = 1;
    cv.notify_all(); // 通知其他所有在等待唤醒队列中的线程
  }

  void second(function<void()> printSecond) {
    unique_lock<mutex> lock(mtx); // lock mtx
    cv.wait(lock, [this]() {
      return k == 1;
    }); // unlock mtx，并阻塞等待唤醒通知，需要满足 k == 1 才能继续运行
    printSecond();
    k = 2;
    cv.notify_one(); // 随机通知一个（unspecified）在等待唤醒队列中的线程
  }

  void third(function<void()> printThird) {
    unique_lock<mutex> lock(mtx); // lock mtx
    cv.wait(lock, [this]() {
      return k == 2;
    }); // unlock mtx，并阻塞等待唤醒通知，需要满足 k == 2 才能继续运行
    printThird();
  }

private:
  condition_variable cv;
  mutex mtx;
  int k = 0;
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