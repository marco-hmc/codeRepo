

#include <iostream>
#include <memory>
#include <string>

// 咖啡接口
class Coffee {
  public:
    virtual ~Coffee() = default;
    virtual double getCost() const = 0;
    virtual std::string getDescription() const = 0;
};

// 简单咖啡类
class SimpleCoffee : public Coffee {
  public:
    double getCost() const override { return 10.0; }

    std::string getDescription() const override { return "简单咖啡"; }
};

// 装饰器基类
class CoffeeDecorator : public Coffee {
  public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee) : coffee_(coffee) {}

    double getCost() const override { return coffee_->getCost(); }

    std::string getDescription() const override {
        return coffee_->getDescription();
    }

  protected:
    std::shared_ptr<Coffee> coffee_;
};

// 牛奶咖啡装饰器
class MilkCoffee : public CoffeeDecorator {
  public:
    MilkCoffee(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    double getCost() const override { return coffee_->getCost() + 2.0; }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", 牛奶";
    }
};

// 奶油咖啡装饰器
class WhipCoffee : public CoffeeDecorator {
  public:
    WhipCoffee(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    double getCost() const override { return coffee_->getCost() + 5.0; }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", 奶油";
    }
};

// 香草咖啡装饰器
class VanillaCoffee : public CoffeeDecorator {
  public:
    VanillaCoffee(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    double getCost() const override { return coffee_->getCost() + 3.0; }

    std::string getDescription() const override {
        return coffee_->getDescription() + ", 香草";
    }
};

int main() {
    std::shared_ptr<Coffee> someCoffee = std::make_shared<SimpleCoffee>();
    std::cout << someCoffee->getCost() << std::endl;         // 输出: 10
    std::cout << someCoffee->getDescription() << std::endl;  // 输出: 简单咖啡

    someCoffee = std::make_shared<MilkCoffee>(someCoffee);
    std::cout << someCoffee->getCost() << std::endl;  // 输出: 12
    std::cout << someCoffee->getDescription()
              << std::endl;  // 输出: 简单咖啡, 牛奶

    someCoffee = std::make_shared<WhipCoffee>(someCoffee);
    std::cout << someCoffee->getCost() << std::endl;  // 输出: 17
    std::cout << someCoffee->getDescription()
              << std::endl;  // 输出: 简单咖啡, 牛奶, 奶油

    someCoffee = std::make_shared<VanillaCoffee>(someCoffee);
    std::cout << someCoffee->getCost() << std::endl;  // 输出: 20
    std::cout << someCoffee->getDescription()
              << std::endl;  // 输出: 简单咖啡, 牛奶, 奶油, 香草

    return 0;
}
