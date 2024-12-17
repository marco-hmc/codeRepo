#include <iostream>
#include <memory>
#include <vector>

class Command {
  public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class ConcreteCommand1 : public Command {
  public:
    void execute() override { std::cout << "执行具体命令1" << '\n'; }
};

class ConcreteCommand2 : public Command {
  public:
    void execute() override { std::cout << "执行具体命令2" << '\n'; }
};

class CommandDispatcher {
  private:
    std::vector<std::unique_ptr<Command>> commands;

  public:
    void registerCommand(std::unique_ptr<Command> command) {
        commands.push_back(std::move(command));
    }

    void dispatchCommands() {
        for (const auto& command : commands) {
            command->execute();
        }
    }
};

int main() {
    auto command1 = std::make_unique<ConcreteCommand1>();
    auto command2 = std::make_unique<ConcreteCommand2>();

    CommandDispatcher dispatcher;
    dispatcher.registerCommand(std::move(command1));
    dispatcher.registerCommand(std::move(command2));

    dispatcher.dispatchCommands();

    return 0;
}