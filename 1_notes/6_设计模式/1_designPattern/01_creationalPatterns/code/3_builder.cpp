#include <iostream>
#include <memory>
#include <string>

// 产品类
class Product {
  public:
    void AddPart(const std::string& part) { parts_ += part + " "; }
    void Show() const { std::cout << "Product parts: " << parts_ << std::endl; }

  private:
    std::string parts_;
};

// 抽象建造者类
class Builder {
  public:
    virtual ~Builder() = default;
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual std::unique_ptr<Product> GetProduct() = 0;
};

// 具体建造者类
class ConcreteBuilder : public Builder {
  public:
    ConcreteBuilder() { product_ = std::make_unique<Product>(); }
    void BuildPartA() override { product_->AddPart("PartA"); }
    void BuildPartB() override { product_->AddPart("PartB"); }
    void BuildPartC() override { product_->AddPart("PartC"); }
    std::unique_ptr<Product> GetProduct() override {
        return std::move(product_);
    }

  private:
    std::unique_ptr<Product> product_;
};

// 指导者类
class Director {
  public:
    void SetBuilder(std::shared_ptr<Builder> builder) { builder_ = builder; }
    void Construct() {
        builder_->BuildPartA();
        builder_->BuildPartB();
        builder_->BuildPartC();
    }

  private:
    std::shared_ptr<Builder> builder_;
};

// 客户端代码
int main() {
    auto builder = std::make_shared<ConcreteBuilder>();
    Director director;
    director.SetBuilder(builder);
    director.Construct();

    auto product = builder->GetProduct();
    product->Show();

    return 0;
}