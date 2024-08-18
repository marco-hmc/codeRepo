#include <boost/coroutine2/all.hpp>
#include <iostream>

int main() {
  boost::coroutines2::coroutine<int>::pull_type apull(
      [](boost::coroutines2::coroutine<int>::push_type &apush) {
        for (int i = 0; i < 10; i++) {
          std::cout << "---------------------"
                    << "coroutine 1" << std::endl;
          apush(1);
        }
      });

  boost::coroutines2::coroutine<int>::pull_type apull2(
      [](boost::coroutines2::coroutine<int>::push_type &apush) {
        for (int i = 0; i < 10; i++) {
          std::cout << "---------------------"
                    << "coroutine 2" << std::endl;
          apush(2);
        }
      });

  for (int i = 0; i < 10; ++i) {
    std::cout << apull.get() << std::endl;
    apull();
    std::cout << apull2.get() << std::endl;
    apull2();
  }
  std::cout << "continue>>>" << std::endl;

  return 0;
}
