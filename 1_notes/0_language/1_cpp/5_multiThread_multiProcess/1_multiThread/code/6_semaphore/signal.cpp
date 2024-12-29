#include <bits/stdc++.h>
#include <semaphore.h>

class Foo {
  private:
    sem_t sem_1{}, sem_2{};

  public:
    Foo() { sem_init(&sem_1, 0, 0), sem_init(&sem_2, 0, 0); }

    void first(std::function<void()>& printFirst) {
        printFirst();
        sem_post(&sem_1);
    }

    void second(std::function<void()>& printSecond) {
        sem_wait(&sem_1);
        printSecond();
        sem_post(&sem_2);
    }

    void third(std::function<void()>& printThird) {
        sem_wait(&sem_2);
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