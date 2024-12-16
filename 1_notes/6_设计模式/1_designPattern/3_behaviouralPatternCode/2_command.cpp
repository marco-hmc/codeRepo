#include <iostream>
#include <memory>

// 命令接口
class Command {
  public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void undo() const = 0;
};

// 灯类
class Light {
  public:
    void on() const { std::cout << "灯已打开" << std::endl; }

    void off() const { std::cout << "灯已关闭" << std::endl; }
};

// 打开灯命令
class LightOnCommand : public Command {
  public:
    LightOnCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() const override { light_->on(); }

    void undo() const override { light_->off(); }

  private:
    std::shared_ptr<Light> light_;
};

// 关闭灯命令
class LightOffCommand : public Command {
  public:
    LightOffCommand(std::shared_ptr<Light> light) : light_(light) {}

    void execute() const override { light_->off(); }

    void undo() const override { light_->on(); }

  private:
    std::shared_ptr<Light> light_;
};

// 遥控器类
class RemoteControl {
  public:
    void setCommand(std::shared_ptr<Command> command) { command_ = command; }

    void pressButton() const {
        if (command_) {
            command_->execute();
        }
    }

    void pressUndo() const {
        if (command_) {
            command_->undo();
        }
    }

  private:
    std::shared_ptr<Command> command_;
};

int main() {
    auto light = std::make_shared<Light>();
    auto lightOnCommand = std::make_shared<LightOnCommand>(light);
    auto lightOffCommand = std::make_shared<LightOffCommand>(light);

    RemoteControl remote;
    remote.setCommand(lightOnCommand);
    remote.pressButton();  // 输出: 灯已打开
    remote.pressUndo();    // 输出: 灯已关闭

    remote.setCommand(lightOffCommand);
    remote.pressButton();  // 输出: 灯已关闭
    remote.pressUndo();    // 输出: 灯已打开

    return 0;
}