#include <bits/stdc++.h>
#include <mutex>
#include <semaphore.h>

using namespace std;

class Foo {
private:
    sem_t sem_1, sem_2;

public:
    Foo() {
        sem_init(&sem_1, 0, 0), sem_init(&sem_2, 0, 0);
    }

    void first(function<void()> printFirst) {
        printFirst();
        sem_post(&sem_1);
    }

    void second(function<void()> printSecond) {
        sem_wait(&sem_1);
        printSecond();
        sem_post(&sem_2);
    }

    void third(function<void()> printThird) {
        sem_wait(&sem_2);
        printThird();
    }
};

void printFirst(){
    for (int i = 0; i < 5; i++)
        cout << "first" << endl;
}
void printSecond(){
    for (int i = 0; i < 5; i++)
        cout << "second" << endl;   
}
void printThird(){
    for (int i = 0; i < 5; i++)
        cout << "third" << endl;
}

int main() {
    Foo f;
    thread t1(&Foo::first, &f, printFirst);
    thread t2(&Foo::second, &f, printSecond);
    thread t3(&Foo::third, &f, printThird);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}