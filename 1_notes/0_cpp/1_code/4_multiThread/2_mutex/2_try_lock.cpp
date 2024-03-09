// mutex::try_lock example
#include <iostream> // std::cout
#include <mutex>    // std::mutex
#include <thread>   // std::thread

volatile int counter(0); // non-atomic counter
std::mutex mtx;          // locks access to counter

void attempt_10k_increases() {
  for (int i = 0; i < 10000; ++i) {
    if (mtx.try_lock()) { // only increase if currently not locked:
      ++counter;
      mtx.unlock();
    }
  }
}

void test_1() {
  std::thread threads[10];
  // spawn 10 threads:
  for (int i = 0; i < 10; ++i)
    threads[i] = std::thread(attempt_10k_increases);

  for (auto &th : threads)
    th.join();
  std::cout << counter << " successful increases of the counter.\n";
}

/////////////////////////////////////////////
std::timed_mutex mtx_t;

void fireworks() {
  // waiting to get a lock: each thread prints "-" every 200ms:
  while (!mtx_t.try_lock_for(std::chrono::milliseconds(2))) {
    std::cout << "-";
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  std::cout << "*\n";
  mtx_t.unlock();
}

void test_2() {
  std::thread threads[10];
  // spawn 10 threads:
  for (int i = 0; i < 10; ++i) {
    threads[i] = std::thread(fireworks);
  }
  for (auto &th : threads)
    th.join();
}

//////////////////////////////////////////////

std::timed_mutex cinderella;

// gets time_point for next midnight:
std::chrono::time_point<std::chrono::system_clock> midnight() {
  using std::chrono::system_clock;
  std::time_t tt = system_clock::to_time_t(system_clock::now());
  struct std::tm *ptm = std::localtime(&tt);
  ++ptm->tm_mday;
  ptm->tm_hour = 0;
  ptm->tm_min = 0;
  ptm->tm_sec = 0;
  return system_clock::from_time_t(mktime(ptm));
}

void carriage() {
  if (cinderella.try_lock_until(midnight())) {
    std::cout << "ride back home on carriage\n";
    cinderella.unlock();
  } else
    std::cout << "carriage reverts to pumpkin\n";
}

void ball() {
  cinderella.lock();
  std::cout << "at the ball...\n";
  cinderella.unlock();
}

void test_3() {
  std::thread th1(ball);
  std::thread th2(carriage);
  th1.join();
  th2.join();
}

int main() {
  test_1();
  test_2();
  test_3();
  return 0;
}
