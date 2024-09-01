#include "minilogger.h"
#include<iostream>
#include<string>

using namespace std;

// #define LOG(fmt, args...)	do{\
// 			char _buf[1024] = {0};\
// 			snprintf(_buf, sizeof(_buf), "[%s:%s:%d][LOG_NORMAL]"fmt"\n",__FILE__,__FUNCTION__,__LINE__, ##args);\
// 			myLog.Log(string(_buf));\
// 		}while(false)
#define LOG(fmt, ...) do {\
    char _buf[1024] = {0}; \
    snprintf(_buf, sizeof(_buf), "[%s:%s:%d][LOG_NORMAL]" fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    myLog.Log(std::string(_buf)); \
} while (false)


//you can define your own TextDecorator and use it.
Logger<TextDecorator> myLog("myLogfile.txt", "this is title!", true, true);

void myFunction() {
    //test LOG in function
    //
    int a = 1;
    int b = 2;

    LOG("this is a log in function,a+b=%d", a + b);
}


//this is some example for using miniLogger
int main() {
    //log with no args.
    myLog.Log("this is log.");
    std::cout << "do something" << '\n';
    // log with args and function name and line number.
    LOG("test for LOG,args: number:[%d], string:[%s]", 1, "YoYo");

    myFunction();
    std::cin.get();
    return 0;

}
