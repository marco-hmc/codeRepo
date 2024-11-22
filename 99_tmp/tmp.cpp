#include <functional>
#include <iostream>

class Base {
  public:
    virtual int getDefaultX() const { return 0; }  // 动态默认值
    virtual void func(
        std::function<int(const Base*)> x = &Base::getDefaultX) const {
        std::cout << "Base: " << x(this) << std::endl;
    }
};

class Derived : public Base {
  public:
    int getDefaultX() const override { return 10; }  // 动态默认值

    void func(std::function<int(const Base*)> x) const override {
        std::cout << "Derived: " << x(this) << std::endl;
    }
};

int main() {
    Base* pDer = new Derived;
    pDer->func();
    return 0;
}