#include <iostream>
#include <memory>
#include <string>

// Forward declaration of State class
class State;

// Context class
class Context {
  public:
  Context();
  void setState(std::shared_ptr<State> state);
  void request();

private:
  std::shared_ptr<State> state_;
};

// Abstract State class
class State {
  public:
    virtual void handle(Context& context) = 0;
};

// Concrete State classes
class ConcreteStateA : public State {
  public:
  void handle(Context& context) override;
};

class ConcreteStateB : public State {
  public:
    void handle(Context& context) override;
};

// Implementation of Context methods
Context::Context() : state_(std::make_shared<ConcreteStateA>()) {}

void Context::setState(std::shared_ptr<State> state) { state_ = state; }

void Context::request() { state_->handle(*this); }

// Implementation of ConcreteStateA methods
void ConcreteStateA::handle(Context& context) {
    std::cout << "ConcreteStateA handling request and changing state to "
                 "ConcreteStateB"
              << std::endl;
    context.setState(std::make_shared<ConcreteStateB>());
}

// Implementation of ConcreteStateB methods
void ConcreteStateB::handle(Context& context) {
    std::cout << "ConcreteStateB handling request and changing state to "
                 "ConcreteStateA"
              << std::endl;
    context.setState(std::make_shared<ConcreteStateA>());
}

// Main function
int main() {
    Context context;
    context.request();
    context.request();
    context.request();
    return 0;
}