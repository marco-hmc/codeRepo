#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct person {
  string name;
  size_t age;

  person(string n, size_t a) : name{move(n)}, age{a} {
    cout << "CTOR " << name << '\n';
  }

  ~person() { cout << "DTOR " << name << '\n'; }
};

int main() {
  int x = 12;
  auto lambda = [&x]() {
    x = 1;
    return x;
  }; // 使用mutable关键字
}