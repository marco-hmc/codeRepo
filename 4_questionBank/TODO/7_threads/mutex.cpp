/*
 * @Author: your name
 * @Date: 2022-09-23 16:35:00
 * @LastEditTime: 2022-09-23 16:52:18
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Exam\thread\mutex.cpp
 */

#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Foo {
    mutex mtx1, mtx2;
    unique_lock<mutex> lock_1, lock_2;

public:
    Foo(): lock_1(mtx1, try_to_lock), lock_2(mtx2, try_to_lock) {}

    void first(function<void()> printFirst){
        printFirst();
        lock_1.unlock();
    }
    void second(function<void()> printSecond) {
        lock_guard<mutex> guard(mtx1);
        printSecond();
        lock_2.unlock();
    }
    void third(function<void()> printThird) {
        lock_guard<mutex> guard(mtx2);
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