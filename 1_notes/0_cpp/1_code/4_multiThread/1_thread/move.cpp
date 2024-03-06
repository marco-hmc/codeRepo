//线程对象之间是不能复制的，只能移动，移动的意思是，将线程的所有权在std::thread实例间进行转移。
#include <iostream>
#include <thread>

void some_function() {}
void some_other_function() {}

int main() {
    std::thread t1(some_function);
    // std::thread t2 = t1; // 编译错误
    std::thread t2 = std::move(t1); // 只能移动 t1内部已经没有线程了
    t1 = std::thread(some_other_function); // 临时对象赋值 默认就是移动操作

    t1.join();
    t2.join();

    return 0;
}