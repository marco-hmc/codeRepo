// example for thread::joinable
#include <iostream>       // std::cout
#include <thread>         // std::thread

void mythread() 
{
  // do stuff...
}

int main() 
{
  std::thread foo;
  std::thread bar(mythread);

  std::cout << "Joinable after construction:\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';
  std::cout << "bar: " << bar.joinable() << '\n';

  if (foo.joinable()) foo.join();
  if (bar.joinable()) bar.join();

  std::cout << "Joinable after joining:\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';
  std::cout << "bar: " << bar.joinable() << '\n';

  return 0;
}
/*
1. `joinable()`是什么？

   `joinable()`是`std::thread`类的一个成员函数，用于检查一个`std::thread`对象是否关联一个活动的线程。

2. 线程对象什么时候开始运行？

    当你创建一个`std::thread`对象并传递一个函数给它时，这个函数会在一个新的线程中立即开始运行。
    例如，如果你写`std::thread t(func);`
    那么`func`会在新的线程`t`中立即开始运行。

3. `joinable()`什么时候返回true，什么时候返回false？

   `std::thread::joinable()`会在以下情况返回true：
      - 当线程对象已经关联到一个线程（即，它已经开始运行一个函数）
        并且还没有被分离或连接时。

   `std::thread::joinable()`会在以下情况返回false：
      - 当线程对象刚被默认构造，还没有关联到任何线程时。
      - 当线程对象已经被移动，不再关联到原来的线程时。
      - 当线程已经被连接（通过`join()`）或分离（通过`detach()`）时

4. 什么时候需要判断`joinable()`？

   在你尝试连接（join）或分离（detach）一个线程之前，你应该先检查它是否可以被连接或分离，这可以通过`std::thread::joinable()`来做。
   如果一个线程不是joinable的，那么尝试连接或分离它会导致程序行为未定义。
   此外，如果你在析构一个线程对象时，它仍然是joinable的，那么程序会终止。
   因此，你应该在析构线程对象之前，确保它不是joinable的，或者连接或分离它。

*/