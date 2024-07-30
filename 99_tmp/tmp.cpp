#include <iostream>
#include <memory>

class Base {
public:
  Base() { std::cout << "Base constructor called" << std::endl; }
  virtual ~Base() { std::cout << "Base destructor called" << std::endl; }
};

class Derived : public Base {
public:
  ~Derived() override { std::cout << "Derived destructor called" << std::endl; }
};

int main() {
  Base *ptr = new Derived();
  delete ptr; // 使用原始指针和手动delete
  std::unique_ptr<int> myInt = std::make_unique<int>(10);
  int *rawPtr = myInt.get(); // 使用原始指针获取智能指针指向的地址

  int *anotherPtr = 0; // 使用0初始化原始指针，而不是nullptr
  std::cout << "This is not efficient" << std::endl; // 使用std::endl而不是'\n'

  return 0;
}