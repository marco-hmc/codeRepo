#include <iostream>
#include <vector>

// Step 1: 创建Command接口
class Command {
public:
    virtual void execute() = 0;
};

// Step 2: 创建具体的命令类
class ConcreteCommand1 : public Command {
public:
    void execute() override {
        std::cout << "执行具体命令1" << std::endl;
    }
};

class ConcreteCommand2 : public Command {
public:
    void execute() override {
        std::cout << "执行具体命令2" << std::endl;
    }
};

// Step 3: 创建CommandDispatcher类
class CommandDispatcher {
private:
    std::vector<Command*> commands;

public:
    void registerCommand(Command* command) {
        commands.push_back(command);
    }

    void dispatchCommands() {
        for (Command* command : commands) {
            command->execute();
        }
    }
};

int main() {
    // Step 4: 创建命令对象和命令分发器对象,并将命令对象注册到命令分发器中
    Command* command1 = new ConcreteCommand1();
    Command* command2 = new ConcreteCommand2();

    CommandDispatcher dispatcher;
    dispatcher.registerCommand(command1);
    dispatcher.registerCommand(command2);

    // Step 5: 通过命令分发器对象执行命令
    dispatcher.dispatchCommands();

    // 清理内存
    delete command1;
    delete command2;

    return 0;
}
