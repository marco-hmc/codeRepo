

#include <iostream>
#include <memory>

// 门接口
class Door {
  public:
    virtual ~Door() = default;
    virtual void open() const = 0;
    virtual void close() const = 0;
};

// 实验室门类
class LabDoor : public Door {
  public:
    void open() const override { std::cout << "打开实验室门" << std::endl; }

    void close() const override { std::cout << "关闭实验室门" << std::endl; }
};

// 安全门代理类
class SecuredDoor : public Door {
  public:
    SecuredDoor(std::shared_ptr<Door> door) : door_(door) {}

    void open() const override {
        std::cout << "请提供密码来打开门。" << std::endl;
    }

    void open(const std::string& password) const {
        if (authenticate(password)) {
            door_->open();
        } else {
            std::cout << "不行！这是不可能的。" << std::endl;
        }
    }

    void close() const override { door_->close(); }

  private:
    bool authenticate(const std::string& password) const {
        return password == "$ecr@t";
    }

    std::shared_ptr<Door> door_;
};

int main() {
    auto labDoor = std::make_shared<LabDoor>();
    SecuredDoor securedDoor(labDoor);

    securedDoor.open("invalid");  // 输出: 不行！这是不可能的。
    securedDoor.open("$ecr@t");   // 输出: 打开实验室门
    securedDoor.close();          // 输出: 关闭实验室门

    return 0;
}
