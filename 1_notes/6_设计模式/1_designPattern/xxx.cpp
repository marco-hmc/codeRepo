#include <iostream>

// 接收者
class Bulb {
  public:
    void turnOn() const { std::cout << "灯泡已点亮" << std::endl; }

    void turnOff() const { std::cout << "黑暗！" << std::endl; }
};

// 命令接口
class Command {
  public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
    virtual void undo() const = 0;
    virtual void redo() const = 0;
};

// 打开灯命令
class TurnOn : public Command {
  public:
    TurnOn(const Bulb& bulb) : bulb_(bulb) {}

    void execute() const override { bulb_.turnOn(); }

    void undo() const override { bulb_.turnOff(); }

    void redo() const override { execute(); }

  private:
    const Bulb& bulb_;
};

// 关闭灯命令
class TurnOff : public Command {
  public:
    TurnOff(const Bulb& bulb) : bulb_(bulb) {}

    void execute() const override { bulb_.turnOff(); }

    void undo() const override { bulb_.turnOn(); }

    void redo() const override { execute(); }

  private:
    const Bulb& bulb_;
};

// 调用者
class RemoteControl {
  public:
    void submit(const Command& command) const { command.execute(); }
};

int main() {
    Bulb bulb;

    TurnOn turnOn(bulb);
    TurnOff turnOff(bulb);

    RemoteControl remote;
    remote.submit(turnOn);   // 输出: 灯泡已点亮
    remote.submit(turnOff);  // 输出: 黑暗！

    return 0;
}
