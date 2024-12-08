#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// 消息中心类
class MessageCenter {
   public:
    using Callback = std::function<void(const std::string&)>;

    // 订阅消息
    void subscribe(const std::string& messageType, Callback callback) {
        subscribers[messageType].push_back(callback);
    }

    // 发布消息
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

// 订阅者类
class Subscriber {
   public:
    Subscriber(const std::string& name) : name(name) {}

    // 处理消息
    void handleMessage(const std::string& message) {
        std::cout << name << " received message: " << message << std::endl;
    }

   private:
    std::string name;
};

int main() {
    MessageCenter messageCenter;

    // 创建订阅者
    Subscriber subscriber1("Subscriber1");
    Subscriber subscriber2("Subscriber2");

    // 订阅者1订阅 "news" 类型的消息
    messageCenter.subscribe("news", [&](const std::string& message) {
        subscriber1.handleMessage(message);
    });

    // 订阅者2订阅 "weather" 类型的消息
    messageCenter.subscribe("weather", [&](const std::string& message) {
        subscriber2.handleMessage(message);
    });

    // 发布 "news" 类型的消息
    messageCenter.publish("news", "Breaking News: New AI technology released!");

    // 发布 "weather" 类型的消息
    messageCenter.publish("weather", "Weather Update: It's sunny today!");

    return 0;
}