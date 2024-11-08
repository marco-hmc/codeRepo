#include <iostream>
#include <memory>

class Top {
public:
  virtual ~Top() = default; // 确保使用虚析构函数
  virtual void doSomething() { std::cout << "Top's implementation.\n"; }
};

class Bottom : public Top {
public:
  void doSomething() override { std::cout << "Bottom's implementation.\n"; }
};

int main() {
  {
    std::shared_ptr<Bottom> bottomPtr = std::make_shared<Bottom>();
    // 将std::shared_ptr<Bottom>隐式转换为std::shared_ptr<Top>
    std::shared_ptr<Top> topPtr = bottomPtr;

    // 调用Bottom的doSomething，因为topPtr实际上指向Bottom对象
    topPtr->doSomething();
  }
  {
    Bottom *bottomPtr = new Bottom();
    // 将Bottom*隐式转换为Top*
    Top *topPtr = bottomPtr;

    // 调用Bottom的doSomething，因为topPtr实际上指向Bottom对象
    topPtr->doSomething();
    // 释放内存
    delete bottomPtr;
  }
  return 0;
}