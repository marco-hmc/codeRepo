#include <iostream>
#include <memory>

// Forward declaration of the Context class
class Context;

// State interface
class State {
  public:
    virtual ~State() = default;
    virtual void handle(Context& context) = 0;
};

// Concrete states
class ConcreteStateA : public State {
  public:
    void handle(Context& context) override;
};

class ConcreteStateB : public State {
  public:
    void handle(Context& context) override;
};

// Context class
class Context {
  public:
    Context(std::unique_ptr<State> state) : state_(std::move(state)) {}

    void setState(std::unique_ptr<State> state) { state_ = std::move(state); }

    void request() { state_->handle(*this); }

  private:
    std::unique_ptr<State> state_;
};

// Implementations of state transitions
void ConcreteStateA::handle(Context& context) {
    std::cout << "State A handling request and transitioning to State B\n";
    context.setState(std::make_unique<ConcreteStateB>());
}

void ConcreteStateB::handle(Context& context) {
    std::cout << "State B handling request and transitioning to State A\n";
    context.setState(std::make_unique<ConcreteStateA>());
}

// Main function to demonstrate the State pattern
int main() {
    Context context(std::make_unique<ConcreteStateA>());
    context.request();
    context.request();
    context.request();
    context.request();
    return 0;
}