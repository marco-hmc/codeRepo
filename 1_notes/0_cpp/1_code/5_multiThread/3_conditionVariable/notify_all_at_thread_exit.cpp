#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready)
    cv.wait(lck);

  std::cout << "thread " << id << '\n';
}

// void go() {
//  mtx.lock();
//  ready = true;
//  cv.notify_all();
//  mtx.unlock();
// }

void go() {
  std::unique_lock<std::mutex> lck(mtx);
  std::notify_all_at_thread_exit(cv, std::move(lck));
  ready = true;
}

int main() {
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(print_id, i);
  }
  std::cout << "10 threads ready to race...\n";

  std::thread(go).detach();

  for (auto &th : threads)
    th.join();

  return 0;
}
