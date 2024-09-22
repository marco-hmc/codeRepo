### 建造者模式（Builder Pattern）

建造者模式是一种创建型设计模式，它允许你一步一步地构建复杂对象。与其他创建型模式不同，建造者模式不仅关注对象的创建，还关注对象的组装过程。

### 代码示例

以下是一个完整的建造者模式的实例代码，展示了如何使用建造者模式创建复杂对象。

#### 代码结构

1. **产品类**：表示要创建的复杂对象。
2. **建造者接口**：定义创建产品各部分的方法。
3. **具体建造者类**：实现建造者接口，构建和组装产品的各个部分。
4. **指挥者类**：控制建造过程。
5. **客户端代码**：使用指挥者和建造者创建产品对象。

#### 代码示例

```cpp
#include <iostream>
#include <memory>
#include <string>

// 产品类
class Product {
public:
    void AddPart(const std::string& part) {
        parts_ += part + " ";
    }

    void Show() const {
        std::cout << "Product parts: " << parts_ << std::endl;
    }

private:
    std::string parts_;
};

// 建造者接口
class Builder {
public:
    virtual ~Builder() = default;
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual std::unique_ptr<Product> GetResult() = 0;
};

// 具体建造者类
class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() {
        Reset();
    }

    void BuildPartA() override {
        product_->AddPart("PartA");
    }

    void BuildPartB() override {
        product_->AddPart("PartB");
    }

    void BuildPartC() override {
        product_->AddPart("PartC");
    }

    std::unique_ptr<Product> GetResult() override {
        auto result = std::move(product_);
        Reset();
        return result;
    }

private:
    void Reset() {
        product_ = std::make_unique<Product>();
    }

    std::unique_ptr<Product> product_;
};

// 指挥者类
class Director {
public:
    void SetBuilder(Builder* builder) {
        builder_ = builder;
    }

    void BuildMinimalViableProduct() {
        builder_->BuildPartA();
    }

    void BuildFullFeaturedProduct() {
        builder_->BuildPartA();
        builder_->BuildPartB();
        builder_->BuildPartC();
    }

private:
    Builder* builder_;
};

// 客户端代码
void ClientCode(Director& director) {
    ConcreteBuilder builder;
    director.SetBuilder(&builder);

    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();
    auto product = builder.GetResult();
    product->Show();

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();
    product = builder.GetResult();
    product->Show();

    // 自定义产品
    std::cout << "Custom product:\n";
    builder.BuildPartA();
    builder.BuildPartC();
    product = builder.GetResult();
    product->Show();
}

int main() {
    Director director;
    ClientCode(director);
    return 0;
}
```

### 建造者模式的意义

1. **分离复杂对象的构建和表示**：
   - 建造者模式将复杂对象的构建过程与其表示分离，使得同样的构建过程可以创建不同的表示。
   - 这有助于提高代码的可读性和可维护性。

2. **逐步构建对象**：
   - 建造者模式允许逐步构建对象，可以在构建过程中灵活地添加、修改或删除部件。
   - 这使得构建过程更加灵活和可控。

3. **控制对象的创建过程**：
   - 通过指挥者类，可以控制对象的创建过程，确保创建过程的一致性和完整性。
   - 指挥者类可以根据需要构建不同的产品，满足不同的需求。

4. **简化客户端代码**：
   - 客户端代码只需要与建造者和指挥者交互，而不需要关心具体的构建过程。
   - 这简化了客户端代码，提高了代码的可维护性。

### 总结

建造者模式通过将复杂对象的构建过程与其表示分离，实现了对象的逐步构建和灵活组装。它适用于需要创建复杂对象的场景，特别是当对象的创建过程需要灵活控制时。建造者模式提高了代码的可读性、可维护性和灵活性。