#include <functional>
#include <iostream>
#include <vector>

class Reactor {
  public:
    void register_event(std::function<void()> event_handler) {
        event_handlers.push_back(event_handler);
    }

    void run() {
        for (auto& handler : event_handlers) {
            handler();  // 调用每个事件处理器
        }
    }

  private:
    std::vector<std::function<void()>> event_handlers;
};

int main() {
    Reactor reactor;
    reactor.register_event([]() { std::cout << "Event 1 handled\n"; });
    reactor.register_event([]() { std::cout << "Event 2 handled\n"; });

    reactor.run();  // 触发事件
}