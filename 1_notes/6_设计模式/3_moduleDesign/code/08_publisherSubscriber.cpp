#include <algorithm>
#include <iostream>
#include <vector>

class Subscriber {
  public:
    virtual void update(const std::string& message) = 0;
};

class ConcreteSubscriber : public Subscriber {
  public:
    void update(const std::string& message) override {
        std::cout << "收到消息: " << message << '\n';
    }
};

class Publisher {
  private:
    std::vector<Subscriber*> subscribers;

  public:
    void subscribe(Subscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void unsubscribe(Subscriber* subscriber) {
        auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notify(const std::string& message) {
        for (auto* subscriber : subscribers) {
            subscriber->update(message);
        }
    }
};

int main() {
    Publisher publisher;
    ConcreteSubscriber subscriber1;
    ConcreteSubscriber subscriber2;

    publisher.subscribe(&subscriber1);
    publisher.subscribe(&subscriber2);
    publisher.notify("Hello, World!");
    publisher.unsubscribe(&subscriber2);
    publisher.notify("Goodbye!");
    return 0;
}
