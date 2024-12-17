#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class MessageCenter {
  public:
    using Callback = std::function<void(const std::string&)>;

    void subscribe(const std::string& messageType, Callback callback) {
        subscribers[messageType].push_back(std::move(callback));
    }

    void publish(const std::string& messageType, const std::string& message) {
        if (subscribers.find(messageType) != subscribers.end()) {
            for (const auto& callback : subscribers[messageType]) {
                callback(message);
            }
        }
    }

  private:
    std::unordered_map<std::string, std::vector<Callback>> subscribers;
};

class Subscriber : public std::enable_shared_from_this<Subscriber> {
  public:
    explicit Subscriber(const std::string& name) : name(name) {}

    void handleMessage(const std::string& message) {
        std::cout << name << " received message: " << message << std::endl;
    }

    std::shared_ptr<Subscriber> getPtr() { return shared_from_this(); }

  private:
    std::string name;
};

int main() {
    auto messageCenter = std::make_shared<MessageCenter>();
    auto subscriber1 = std::make_shared<Subscriber>("Subscriber1");
    auto subscriber2 = std::make_shared<Subscriber>("Subscriber2");

    messageCenter->subscribe("news", [subscriber1](const std::string& message) {
        subscriber1->handleMessage(message);
    });

    messageCenter->subscribe("weather",
                             [subscriber2](const std::string& message) {
                                 subscriber2->handleMessage(message);
                             });

    messageCenter->publish("news",
                           "Breaking News: New AI technology released!");
    messageCenter->publish("weather", "Weather Update: It's sunny today!");
    return 0;
}