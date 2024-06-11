#include <iostream>
#include <thread>
#include <future>

int main() {
  std::packaged_task<int()> task([]() { return 7; });

  std::future<int> result = task.get_future(); // run task in a thread
  std::thread(std::move(task)).detach();
  std::cout << "waiting...";
  result.wait();

  std::cout << "done!" << std::endl
            << "future result is " << result.get() << std::endl;
  return 0;
}