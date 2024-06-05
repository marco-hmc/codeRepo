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

// 当创建一个`std::thread`对象并传入一个函数时，这个对象就会关联一个新的线程，并开始运行这个函数。
// 在这种情况下，`joinable()`会返回`true`。

// 如果一个`std::thread`对象没有关联一个活动的线程（例如，它被默认构造，或者已经被join或detach）
// 那么`joinable()`会返回`false`。

// `join()`是`std::thread`类的另一个成员函数，它用于等待关联的线程结束。调用`join()`后，`std::thread`对象就不再关联一个活动的线程，因此`joinable()`会返回`false`。

// 在代码中，`foo`线程被默认构造，因此它没有关联一个活动的线程，`foo.joinable()`返回`false`。
// `bar`线程关联了`mythread`函数，因此`bar.joinable()`返回`true`。
// 当`foo`和`bar`线程被join后，它们都不再关联一个活动的线程，因此`foo.joinable()`和`bar.joinable()`都返回`false`。

// 你应该在调用`join()`或`detach()`之前，先检查一个线程是否joinable。如果一个线程不是joinable，但你仍然尝试join或detach它，那么程序就会终止。