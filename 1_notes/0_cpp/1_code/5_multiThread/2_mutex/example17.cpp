#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int winner;
void set_winner(int x) { winner = x; }
std::once_flag winner_flag;

void wait_1000ms(int id) {
  for (int i = 0; i < 1000; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::call_once(winner_flag, set_winner, id);
}

int main() {
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(wait_1000ms, i + 1);
  }
  std::cout << "waiting for the first among 10 threads to count 1000ms...\n";

  for (auto &th : threads) {
    th.join();
  }
  std::cout << "winner thread: " << winner << '\n';
  return 0;
}
