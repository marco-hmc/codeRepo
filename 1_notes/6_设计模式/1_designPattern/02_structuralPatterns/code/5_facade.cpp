#include <iostream>
#include <memory>

// 计算机类，包含多个子系统方法
class Computer {
  public:
    void getElectricShock() const { std::cout << "哎哟！" << std::endl; }

    void makeSound() const { std::cout << "哔哔！" << std::endl; }

    void showLoadingScreen() const { std::cout << "加载中..." << std::endl; }

    void bam() const { std::cout << "准备就绪！" << std::endl; }

    void closeEverything() const {
        std::cout << "关闭所有程序..." << std::endl;
    }

    void pullCurrent() const { std::cout << "断开电源！" << std::endl; }

    void sooth() const { std::cout << "进入睡眠模式..." << std::endl; }
};

// 计算机外观类，简化计算机的启动和关闭操作
class ComputerFacade {
  public:
    ComputerFacade(std::shared_ptr<Computer> computer) : computer_(computer) {}

    void turnOn() const {
        computer_->getElectricShock();
        computer_->makeSound();
        computer_->showLoadingScreen();
        computer_->bam();
    }

    void turnOff() const {
        computer_->closeEverything();
        computer_->pullCurrent();
        computer_->sooth();
    }

  private:
    std::shared_ptr<Computer> computer_;
};

int main() {
    auto computer = std::make_shared<Computer>();
    ComputerFacade computerFacade(computer);

    computerFacade.turnOn();  // 输出: 哎哟！ 哔哔！ 加载中... 准备就绪！

    computerFacade
        .turnOff();  // 输出: 关闭所有程序... 断开电源！ 进入睡眠模式...

    return 0;
}
