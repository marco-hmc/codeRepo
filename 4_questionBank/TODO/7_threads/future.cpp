#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Foo {
    promise<void> pro1, pro2;

public:
    void first(function<void()> printFirst) {
        printFirst();
        pro1.set_value();
    }

    void second(function<void()> printSecond) {
        pro1.get_future().wait();
        printSecond();
        pro2.set_value();
    }

    void third(function<void()> printThird) {
        pro2.get_future().wait();
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