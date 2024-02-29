#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Foo {
    std::atomic<bool> a{ false };
    std::atomic<bool> b{ false };
public:
    void first(function<void()> printFirst) {
        printFirst();
        a = true;
    }

    void second(function<void()> printSecond) {
        while (!a)
            this_thread::sleep_for(chrono::milliseconds(1));
        printSecond();
        b = true;
    }

    void third(function<void()> printThird) {
        while (!b)
            this_thread::sleep_for(chrono::milliseconds(1));
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