#include <future>
#include <iostream>
#include <thread>

class Foo {
    std::promise<void> pro1, pro2;

  public:
    void first(std::function<void()>& printFirst) {
        printFirst();
        pro1.set_value();
    }

    void second(std::function<void()>& printSecond) {
        pro1.get_future().wait();
        printSecond();
        pro2.set_value();
    }

    void third(std::function<void()>& printThird) {
        pro2.get_future().wait();
        printThird();
    }
};

void printFirst() {
    for (int i = 0; i < 5; i++) {
        std::cout << "first" << std::endl;
    }
}
void printSecond() {
    for (int i = 0; i < 5; i++) {
        std::cout << "second" << std::endl;
    }
}
void printThird() {
    for (int i = 0; i < 5; i++) {
        std::cout << "third" << std::endl;
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