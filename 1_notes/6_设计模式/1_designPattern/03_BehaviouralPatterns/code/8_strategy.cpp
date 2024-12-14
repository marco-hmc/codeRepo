#include <iostream>
#include <memory>

// Strategy Interface
class Strategy {
  public:
    virtual ~Strategy() = default;
    virtual void execute() const = 0;
};

// Concrete Strategies
class ConcreteStrategyA : public Strategy {
  public:
    void execute() const override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
  public:
    void execute() const override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

// Context
class Context {
  private:
    std::unique_ptr<Strategy> strategy_;

  public:
    explicit Context(std::unique_ptr<Strategy> strategy = nullptr)
        : strategy_(std::move(strategy)) {}

    void set_strategy(std::unique_ptr<Strategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void execute_strategy() const {
        if (strategy_) {
            strategy_->execute();
        } else {
            std::cout << "No strategy set" << std::endl;
        }
    }
};

int main() {
    Context context;

    context.set_strategy(std::make_unique<ConcreteStrategyA>());
    context.execute_strategy();

    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.execute_strategy();

    return 0;
}