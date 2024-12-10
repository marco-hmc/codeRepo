#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex myMutex;
std::condition_variable cv;
int flag = 0;

void printA() {
    std::unique_lock<std::mutex> lk(myMutex);
    int count = 0;
    while (count < 10) {
        while (flag != 0) {
            cv.wait(lk);
        }
        std::cout << "thread 1: a" << std::endl;
        flag = 1;
        cv.notify_all();
        count++;
    }
    std::cout << "my thread 1 finish" << std::endl;
}

void printB() {
    std::unique_lock<std::mutex> lk(myMutex);
    for (int i = 0; i < 10; i++) {
        while (flag != 1) {
            cv.wait(lk);
        }
        std::cout << "thread 2: b" << std::endl;
        flag = 2;
        cv.notify_all();
    }
    std::cout << "my thread 2 finish" << std::endl;
}

void printC() {
    std::unique_lock<std::mutex> lk(myMutex);
    for (int i = 0; i < 10; i++) {
        while (flag != 2) {
            cv.wait(lk);
        }
        std::cout << "thread 3: c" << std::endl;
        flag = 0;
        cv.notify_all();
    }
    std::cout << "my thread 3 finish" << std::endl;
}

int main() {
    std::thread th2(printA);
    std::thread th1(printB);
    std::thread th3(printC);

    th1.join();
    th2.join();
    th3.join();
    std::cout << " main thread " << std::endl;
}