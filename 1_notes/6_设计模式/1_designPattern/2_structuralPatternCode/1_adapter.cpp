#include <iostream>

// 狮子接口
class Lion {
  public:
    virtual ~Lion() = default;
    virtual void roar() const = 0;
};

// 非洲狮类
class AfricanLion : public Lion {
  public:
    void roar() const override { std::cout << "非洲狮吼叫" << std::endl; }
};

// 亚洲狮类
class AsianLion : public Lion {
  public:
    void roar() const override { std::cout << "亚洲狮吼叫" << std::endl; }
};

// 猎人类
class Hunter {
  public:
    void hunt(const Lion& lion) const { lion.roar(); }
};

// 需要添加到游戏中的野狗类
class WildDog {
  public:
    void bark() const { std::cout << "野狗吠叫" << std::endl; }
};

// 野狗适配器，使其与我们的游戏兼容
class WildDogAdapter : public Lion {
  public:
    WildDogAdapter(WildDog* dog) : dog_(dog) {}

    void roar() const override { dog_->bark(); }

  private:
    WildDog* dog_;
};

int main() {
    WildDog wildDog;
    WildDogAdapter wildDogAdapter(&wildDog);

    Hunter hunter;
    hunter.hunt(wildDogAdapter);  // 输出: 野狗吠叫
    return 0;
}
