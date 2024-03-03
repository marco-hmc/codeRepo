#include <iostream>

class Mutex {
public:
  void lock() {
    // 实现互斥锁的逻辑
    std::cout << "Lock acquired" << std::endl;
  }

  void unlock() {
    // 实现互斥锁的逻辑
    std::cout << "Lock released" << std::endl;
  }
};

class Guard {
public:
  Guard(Mutex &mutex) : m_mutex(mutex), m_locked(true) { m_mutex.lock(); }

  ~Guard() {
    if (m_locked) {
      m_mutex.unlock();
    }
  }

private:
  Mutex &m_mutex;
  bool m_locked;
};

int main() {
  Mutex mutex;

  {
    Guard guard(mutex);
    // 在这个作用域内,互斥锁已经被获取
    // 执行需要保护的代码
    std::cout << "Protected code" << std::endl;
  }

  // 在这个作用域外,互斥锁已经被释放

  return 0;
}
