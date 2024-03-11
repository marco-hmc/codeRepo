#include <iostream>
using namespace std;

// lazy
class Singleton {
private:
  Singleton(){};
  ~Singleton(){};
  Singleton(const Singleton &);
  Singleton &operator=(const Singleton &);

public:
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }
};

///////////////////////////////////////////
// hungry
class Singleton2 {
private:
  static Singleton2 instance;

private:
  Singleton2();
  ~Singleton2();
  Singleton2(const Singleton2 &);
  Singleton2 &operator=(const Singleton2 &);

public:
  static Singleton2 &getInstance() { return instance; }
};

// initialize defaultly
Singleton2 Singleton2::instance;

int main() {}