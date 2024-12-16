#include <iostream>
#include <memory>

class Door {
  public:
    virtual ~Door() = default;
    virtual void open() const = 0;
    virtual void close() const = 0;
};

class LabDoor : public Door {
  public:
    void open() const override { std::cout << "打开实验室门" << std::endl; }

    void close() const override { std::cout << "关闭实验室门" << std::endl; }
};

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

    securedDoor.open("invalid");
    securedDoor.open("$ecr@t");
    securedDoor.close();

    return 0;
}
