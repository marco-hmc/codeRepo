#include <iostream>
#include <memory>

class Command {
  public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
  public:
    void execute() override { std::cout << "执行具体命令" << std::endl; }
};

class CommandFactory {
  public:
    static std::unique_ptr<Command> createCommand() {
        return std::make_unique<ConcreteCommand>();
    }
};

int main() {
    auto command = CommandFactory::createCommand();
    command->execute();
    return 0;
}