#include <iostream>
#include <memory>
#include <string>

// 抽象产品类 A
class AbstractProductA {
  public:
    virtual ~AbstractProductA() = default;
    virtual std::string UsefulFunctionA() const = 0;
};

// 具体产品类 A1
class ConcreteProductA1 : public AbstractProductA {
  public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A1.";
    }
};

// 具体产品类 A2
class ConcreteProductA2 : public AbstractProductA {
  public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A2.";
    }
};

// 抽象产品类 B
class AbstractProductB {
  public:
    virtual ~AbstractProductB() = default;
    virtual std::string UsefulFunctionB() const = 0;
    virtual std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const = 0;
};

// 具体产品类 B1
class ConcreteProductB1 : public AbstractProductB {
  public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B1.";
    }
    std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

// 具体产品类 B2
class ConcreteProductB2 : public AbstractProductB {
  public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B2.";
    }
    std::string AnotherUsefulFunctionB(
        const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

// 抽象工厂类
class AbstractFactory {
  public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<AbstractProductA> CreateProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> CreateProductB() const = 0;
};

// 具体工厂类 1
class ConcreteFactory1 : public AbstractFactory {
  public:
    std::unique_ptr<AbstractProductA> CreateProductA() const override {
        return std::make_unique<ConcreteProductA1>();
    }
    std::unique_ptr<AbstractProductB> CreateProductB() const override {
        return std::make_unique<ConcreteProductB1>();
    }
};

// 具体工厂类 2
class ConcreteFactory2 : public AbstractFactory {
  public:
    std::unique_ptr<AbstractProductA> CreateProductA() const override {
        return std::make_unique<ConcreteProductA2>();
    }
    std::unique_ptr<AbstractProductB> CreateProductB() const override {
        return std::make_unique<ConcreteProductB2>();
    }
};

// 客户端代码
void ClientCode(const AbstractFactory& factory) {
    auto productA = factory.CreateProductA();
    auto productB = factory.CreateProductB();
    std::cout << productB->UsefulFunctionB() << std::endl;
    std::cout << productB->AnotherUsefulFunctionB(*productA) << std::endl;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 factory1;
    ClientCode(factory1);

    std::cout << "\nClient: Testing the same client code with the second "
                 "factory type:\n";
    ConcreteFactory2 factory2;
    ClientCode(factory2);

    return 0;
}