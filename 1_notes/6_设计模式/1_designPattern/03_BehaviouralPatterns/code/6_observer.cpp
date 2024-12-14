#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Observer interface
class Observer {
  public:
    virtual ~Observer() = default;
    virtual void update(const std::string &message) = 0;
};

// Subject class
class Subject {
  public:
    virtual ~Subject() = default;
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    void detach(std::shared_ptr<Observer> observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end());
    }
    void notify(const std::string &message) {
        for (const auto &observer : observers) {
            observer->update(message);
        }
    }

  private:
    std::vector<std::shared_ptr<Observer>> observers;
};

// Concrete Observer
class ConcreteObserver : public Observer {
  public:
    ConcreteObserver(const std::string &name) : name(name) {}
    void update(const std::string &message) override {
        std::cout << "Observer " << name << " received message: " << message
                  << std::endl;
    }

  private:
    std::string name;
};

// Concrete Subject
class ConcreteSubject : public Subject {
  public:
    void createMessage(const std::string &message) { notify(message); }
};

int main() {
    auto subject = std::make_shared<ConcreteSubject>();

    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");

    subject->attach(observer1);
    subject->attach(observer2);

    subject->createMessage("Hello, Observers!");

    subject->detach(observer1);

    subject->createMessage("Observer1 has been detached.");

    return 0;
}
