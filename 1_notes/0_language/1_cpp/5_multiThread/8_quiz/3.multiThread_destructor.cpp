k#include <iostream>
#include <memory>
#include <thread>

class MyClass {
public:
  MyClass() { std::cout << "MyClass constructor" << '\n'; }

  ~MyClass() { std::cout << "MyClass destructor" << '\n'; }
};

void threadFunc(std::shared_ptr<MyClass> ptr) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ptr.reset();
}

int main() {
  std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();

  std::thread t1(threadFunc, sharedPtr);
  std::thread t2(threadFunc, sharedPtr);

  t1.join();
  t2.join();

  return 0;
}