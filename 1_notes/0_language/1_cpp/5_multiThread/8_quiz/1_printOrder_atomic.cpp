#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

class Foo {
    std::atomic<bool> a{false};
    std::atomic<bool> b{false};

  public:
    void first(std::function<void()>& printFirst) {
        printFirst();
        a = true;
    }

    void second(std::function<void()>& printSecond) {
        while (!a) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        printSecond();
        b = true;
    }

    void third(std::function<void()>& printThird) {
        while (!b) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        printThird();
    }
};

void printFirst() {
    for (int i = 0; i < 5; i++) {
        std::cout << "first" << '\n';
    }
}
void printSecond() {
    for (int i = 0; i < 5; i++) {
        std::cout << "second" << '\n';
    }
}
void printThird() {
    for (int i = 0; i < 5; i++) {
        std::cout << "third" << '\n';
    }
}

int main() {
    Foo f;
    std::thread t1(&Foo::first, &f, printFirst);
    std::thread t2(&Foo::second, &f, printSecond);
    std::thread t3(&Foo::third, &f, printThird);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}