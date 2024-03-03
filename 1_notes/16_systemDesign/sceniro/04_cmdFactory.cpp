// 命令接口
class Command {
public:
    virtual void execute() = 0;
};

// 具体的命令类
class ConcreteCommand : public Command {
public:
    void execute() override {
        // 执行具体的命令逻辑
        // ...
    }
};

// 命令工厂类
class CommandFactory {
public:
    static Command* createCommand() {
        // 根据客户端的请求创建具体的命令对象
        return new ConcreteCommand();
    }
};

int main() {
    // 使用命令工厂创建命令对象
    Command* command = CommandFactory::createCommand();

    // 调用命令对象的执行方法
    command->execute();

    // 释放命令对象的内存
    delete command;

    return 0;
}
