#include <iostream>
#include <thread>
#include <unistd.h>

void function_1() {
    int i = 5;
    while(i>0){
        i--;
        sleep(1);
        std::cout << "1111" << std::endl;
    }
}

void function_2() {
    int i = 5;
    while(i>0){
        i--;
        sleep(1);
        std::cout << "2222" << std::endl;
    }
}
void function_3() {
    int i = 5;
    while(i>0){
        i--;
        sleep(1);
        std::cout << "3333" << std::endl;
    }
}

void test_1() {
    std::thread t1(function_1);
    function_2();
    function_3();
}

void test_2() {
    std::thread t1(function_1);
    function_2();
    t1.detach();
    function_3();
}

void test_3() {
    std::thread t1(function_1);
    function_2();
    t1.join();
    function_3();
}

int main() {
    // test_1(); 异常 参考链接 https://blog.csdn.net/xp178171640/article/details/118548150
    test_2(); //
    test_3(); //
    std::cout << "finish" << std::endl;
    return 0;
}

