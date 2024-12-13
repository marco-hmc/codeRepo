#include <iostream>
#include <memory>
#include <string>

// 产品接口
class Product {
  public:
    virtual ~Product() = default;
    virtual std::string Operation() const = 0;
};

// 具体产品类 A
class ConcreteProductA : public Product {
  public:
    std::string Operation() const override { return "ConcreteProductA"; }
};

// 具体产品类 B
class ConcreteProductB : public Product {
  public:
    std::string Operation() const override { return "ConcreteProductB"; }
};

// 工厂接口
class Creator {
  public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> FactoryMethod() const = 0;

    std::string SomeOperation() const {
        auto product = FactoryMethod();
        return "Creator: The same creator's code has just worked with " +
               product->Operation();
    }
};

// 具体工厂类 A
class ConcreteCreatorA : public Creator {
  public:
    std::unique_ptr<Product> FactoryMethod() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

// 具体工厂类 B
class ConcreteCreatorB : public Creator {
  public:
    std::unique_ptr<Product> FactoryMethod() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

// 客户端代码
void ClientCode(const Creator& creator) {
    std::cout
        << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << std::endl;
}

int main() {
    std::cout << "App: Launched with the ConcreteCreatorA.\n";
    ConcreteCreatorA creatorA;
    ClientCode(creatorA);

    std::cout << "\nApp: Launched with the ConcreteCreatorB.\n";
    ConcreteCreatorB creatorB;
    ClientCode(creatorB);

    return 0;
}

/*
1. **工厂方法模式（Factory Method Pattern）**：
   - 工厂方法模式定义了一个创建对象的接口，但由子类决定要实例化的类是哪一个。工厂方法使一个类的实例化延迟到其子类。
   - 主要用于创建单一产品对象。
   - 通过继承和重写工厂方法来创建具体产品。

2. **抽象工厂模式（Abstract Factory Pattern）**：
   - 抽象工厂模式提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。抽象工厂模式通常用于创建一组相关的产品对象，这些对象可以一起工作。
   - 主要用于创建一组相关或相互依赖的产品对象。
   - 通过实现抽象工厂接口来创建具体产品族。

*/
