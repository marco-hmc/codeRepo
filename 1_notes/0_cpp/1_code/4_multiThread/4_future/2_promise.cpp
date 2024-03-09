#include <fstream>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>


int factorial(std::future<int> &f) {
  int res = 1;
  int N = f.get();
  for (int i = N; i > 1; i--)
    res *= i;
  std::cout << "Result is: " << res << std::endl;

  return res;
}

void test_1() {
  int x;
  std::promise<int> p; // 想要从主线程中传入子线程的变量
  std::future<int> f = p.get_future();

  std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

  p.set_value(4);
  x = fu.get();
  std::cout << "Result from Child: " << x << std::endl;
}
//////////////////////////////////////////

void print_int(std::future<int> &fut) {
  int x = fut.get();
  std::cout << "value: " << x << '\n';
}

void test_2() {
  std::promise<int> prom; // create promise

  std::future<int> fut = prom.get_future(); // engagement with future

  std::thread th1(print_int, std::ref(fut)); // send future to new thread

  prom.set_value(10); // fulfill promise
                      // (synchronizes with getting the future)
  th1.join();
}

int main() {
  test_1();
  test_2();
  return 0;
}
