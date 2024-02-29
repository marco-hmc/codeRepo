#include <iostream>
#include <thread>
#include <functional>

// 类
class TestClass {
public:
    void func1() {
    }

    void func2(int i) {
        std::cout << "fun2: " << i << std::endl;
    }

    void func3(int i, int j) {
        std::cout << "fun3: " << i+j << std::endl;
    }
};

int main() {
    // 使用std::function存储类成员函数
    TestClass classObj;
    std::function<void()> f1 = std::bind(&TestClass::func1, classObj);
    std::function<void(int)> f2 = std::bind(&TestClass::func2, classObj, std::placeholders::_1);
    std::function<void(int, int)> f3 = std::bind(&TestClass::func3, classObj, std::placeholders::_1, std::placeholders::_2);

    // 构建线程
    std::thread t1(f1);
    std::thread t2(f2, 1);
    std::thread t3(f3, 1, 2);
    t1.join();
    t2.join();
    t3.join();

	return 0;
}