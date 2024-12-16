#include <iostream>
#include <memory>
#include <string>

class User;

class ChatRoomMediator {
  public:
    virtual ~ChatRoomMediator() = default;
    virtual void showMessage(const std::shared_ptr<User>& user,
                             const std::string& message) const = 0;
};

class User : public std::enable_shared_from_this<User> {
  public:
    User(const std::string& name, std::shared_ptr<ChatRoomMediator> mediator)
        : name_(name), mediator_(mediator) {}

    void sendMessage(const std::string& message) {
        mediator_->showMessage(shared_from_this(), message);
    }

    std::string getName() const { return name_; }

  private:
    std::string name_;
    std::shared_ptr<ChatRoomMediator> mediator_;
};

class ChatRoom : public ChatRoomMediator {
  public:
    void showMessage(const std::shared_ptr<User>& user,
                     const std::string& message) const override {
        std::cout << user->getName() << ": " << message << std::endl;
    }
};

int main() {
    auto chatRoom = std::make_shared<ChatRoom>();
    auto user1 = std::make_shared<User>("Alice", chatRoom);
    auto user2 = std::make_shared<User>("Bob", chatRoom);

    user1->sendMessage("你好，Bob!");
    user2->sendMessage("你好，Alice!");
    return 0;
}