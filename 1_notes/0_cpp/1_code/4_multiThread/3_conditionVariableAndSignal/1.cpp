#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex g_mutex;
void threadTask1()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Method 1 thread: " << i << std::endl;
    }
}

void threadTask2()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Method 2 thread: " << i << std::endl;
    }
}

void safethreadTask1()
{
    for (int i = 0; i < 10; i++)
    {   
        g_mutex.lock();
        std::cout << "safe Method 1 thread: " << i << std::endl;
        g_mutex.unlock();
    }
}

void test_1(){
    std::thread t1(threadTask1);
    std::thread t2(threadTask2);
    t1.join();t2.join();
    cout << "cout in mess" << endl;
}

void test_2(){
    std::thread t1(safethreadTask1);
    std::thread t2(threadTask1);
    t1.join();t2.join();
    cout << "cout in mess" << endl;
}

int main()
{
    test_1();
    test_2();
    return 0;
}