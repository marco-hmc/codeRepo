#include <iostream>
#include <mutex>
#include <thread>

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
  while (!mtx_t.try_lock_for(std::chrono::milliseconds(200))) {
    std::cout << "-";
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

/*
1. `mutex.try_lock()`

   `mutex.try_lock()`是一个尝试获取互斥锁的函数。如果互斥锁当前没有被其他线程持有，那么这个函数会立即获取锁并返回`true`。如果互斥锁已经被其他线程持有，那么这个函数不会阻塞，而是立即返回`false`。这个函数没有形参。

    在test_1()中，代码尝试在10个线程中各自增加1000次一个共享的全局计数器`counter`。每个线程在增加计数器之前都会尝试获取一个互斥锁`mtx`，如果获取成功，那么它会增加计数器并释放锁。

    然而，这里的关键字是"尝试"。`std::mutex::try_lock()`函数会尝试获取锁，如果锁当前被其他线程持有，那么它会立即返回`false`，并且不会阻塞。这意味着如果一个线程尝试获取锁但失败了，那么它会直接跳过增加计数器的步骤，继续下一次循环。

    因此，尽管每个线程都尝试了1000次增加计数器，但并不是所有的尝试都成功。如果在一个线程尝试获取锁的时候，锁被其他线程持有，那么这个尝试就会失败，计数器的值就不会增加。这就是为什么最后输出的计数器的值可能会小于10000的原因。

2. `mutex.try_lock_for()`

   `mutex.try_lock_for()`是一个在指定的时间段内尝试获取互斥锁的函数。如果在这个时间段内互斥锁变得可用，那么这个函数会获取锁并返回`true`。如果时间段结束时互斥锁仍然不可用，那么这个函数会返回`false`。这个函数的形参是一个`std::chrono::duration`，表示等待的时间段。

   在test_2()中，有十颗烟花，烟花能够释放的时候就是*，不然就等待，输出-

3. `mutex.try_lock_until()`

   `mutex.try_lock_until()`是一个在指定的时间点之前尝试获取互斥锁的函数。如果在这个时间点之前互斥锁变得可用，那么这个函数会获取锁并返回`true`。如果时间点到达时互斥锁仍然不可用，那么这个函数会返回`false`。这个函数的形参是一个`std::chrono::time_point`，表示等待的截止时间。

*/