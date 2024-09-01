#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class Foo {
public:
  void first(std::function<void()> printFirst) {
    printFirst();
    k = 1;
    cv.notify_all();
  }

  void second(std::function<void()> printSecond) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return k == 1; });
    printSecond();
    k = 2;
    cv.notify_one();
  }

  void third(std::function<void()> printThird) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return k == 2; });
    printThird();
  }

private:
  std::condition_variable cv;
  std::mutex mtx;
  int k = 0;
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
