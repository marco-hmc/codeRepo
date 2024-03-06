#include <iostream>
#include <vector>

// 订阅者接口
class Subscriber {
public:
    virtual void update(const std::string& message) = 0;
};

// 具体的订阅者
class ConcreteSubscriber : public Subscriber {
public:
    void update(const std::string& message) override {
        std::cout << "收到消息: " << message << std::endl;
    }
};

// 发布者
class Publisher {
private:
    std::vector<Subscriber*> subscribers;

public:
    void subscribe(Subscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void unsubscribe(Subscriber* subscriber) {
        // 在实际应用中可能需要更复杂的逻辑来取消订阅
        auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notify(const std::string& message) {
        for (auto subscriber : subscribers) {
            subscriber->update(message);
        }
    }
};

int main() {
    // 创建发布者和订阅者
    Publisher publisher;
    ConcreteSubscriber subscriber1;
    ConcreteSubscriber subscriber2;

    // 订阅者订阅发布者
    publisher.subscribe(&subscriber1);
    publisher.subscribe(&subscriber2);

    // 发布者发布消息
    publisher.notify("Hello, World!");

    // 订阅者取消订阅
    publisher.unsubscribe(&subscriber2);

    // 发布者再次发布消息
    publisher.notify("Goodbye!");

    return 0;
}
