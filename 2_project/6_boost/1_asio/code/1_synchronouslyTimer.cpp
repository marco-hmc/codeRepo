#include <boost/asio.hpp>
#include <iostream>

int main() {
  boost::asio::io_context io;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
  t.wait();
  std::cout << "Hello, world!" << '\n';
  return 0;
}

/*
1. io_context有什么用？
  io_context是asio的核心类，它提供了事件循环机制，用于处理异步操作。io_context的作用是管理异步操作，包括事件处理、事件分发、事件调度等。

2. steady_timer是什么？
  steady_timer是asio提供的定时器类，它用于定时触发事件。steady_timer的构造函数需要传入io_context对象和时间间隔，表示在多长时间后触发定时器。

3. wait()函数是什么？
  wait()函数是steady_timer类的成员函数，用于等待定时器触发。当定时器到期时，wait()函数返回，程序继续执行。

4. 具体说明io_context怎么用
* 怎么构造？
* 怎么运行？
* 怎么停止？
*/