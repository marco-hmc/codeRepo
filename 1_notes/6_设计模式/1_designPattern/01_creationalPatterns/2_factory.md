### 工厂方法模式实例代码

以下是一个完整的工厂方法模式的实例代码，展示了如何使用工厂方法模式创建对象。

#### 代码结构

1. **产品接口**：定义产品的接口。
2. **具体产品类**：实现产品接口。
3. **工厂接口**：定义创建产品的方法。
4. **具体工厂类**：实现工厂接口，创建具体产品。
5. **客户端代码**：使用工厂创建产品对象。

#### 代码示例

```cpp
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
    std::string Operation() const override {
        return "Result of ConcreteProductA";
    }
};

// 具体产品类 B
class ConcreteProductB : public Product {
public:
    std::string Operation() const override {
        return "Result of ConcreteProductB";
    }
};

// 工厂接口
class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> FactoryMethod() const = 0;

    std::string SomeOperation() const {
        // 调用工厂方法创建产品对象
        std::unique_ptr<Product> product = this->FactoryMethod();
        return "Creator: The same creator's code has just worked with " + product->Operation();
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
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
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
```

### 抽象工厂模式的意义

抽象工厂模式与工厂方法模式不同，它提供了一种创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。以下是抽象工厂模式的意义：

1. **创建相关对象的接口**：
   - 抽象工厂模式提供了一种创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
   - 这使得客户端代码可以独立于具体的产品类进行编程，从而提高了代码的可扩展性和可维护性。

2. **分离具体类**：
   - 抽象工厂模式将具体类的创建过程封装在工厂类中，客户端代码只需要依赖抽象工厂接口，而不需要知道具体类的实现细节。
   - 这有助于减少代码的耦合度，提高代码的灵活性。

3. **支持产品族的扩展**：
   - 抽象工厂模式使得添加新的产品族变得容易。只需要添加新的具体工厂类和具体产品类，而不需要修改现有的客户端代码。
   - 这有助于应对需求变化和系统扩展。

4. **一致的产品接口**：
   - 抽象工厂模式确保创建的一系列相关对象具有一致的接口，保证了它们可以一起工作。
   - 这有助于维护系统的一致性和稳定性。

### 总结

抽象工厂模式通过提供创建一系列相关或相互依赖对象的接口，实现了客户端代码与具体产品类的解耦，提高了代码的可扩展性、可维护性和灵活性。它适用于需要创建一组相关对象的场景，特别是当这些对象需要一起工作时。