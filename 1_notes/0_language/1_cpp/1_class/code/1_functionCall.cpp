#include <iostream>

class A {
  public:
    void myfunc1(int tempvalue1) {
        std::cout << "tempvalue1 = " << tempvalue1 << std::endl;
    }

    void myfunc2(int tempvalue2) {
        std::cout << "tempvalue2 = " << tempvalue2 << std::endl;
    }

    static void mysfunc(int tempvalue) {
        std::cout << "A::mysfunc() 静态成员函数 -- tempvalue = " << tempvalue
                  << std::endl;
    }
};

void func() {
    A mya;
    // 定义一个成员函数指针并给初值
    void (A::*pmypoint)(int tempvalue) = &A::myfunc1;
    // 给成员函数指针赋值
    pmypoint = &A::myfunc2;

    // 通过成员函数指针来调用成员函数，必须要通过对象的介入才能调用
    (mya.*pmypoint)(15);

    A *pmya = new A();
    (pmya->*pmypoint)(20);  // 用对象指针介入来使用成员函数指针来调用成员函数

    // 编译器视角
    // pmypoint(&mya, 15);
    // pmypoint(pmya, 20);

    // 一个普通的函数指针，而不是成员函数指针
    void (*pmyspoint)(int tempvalue) = &A::mysfunc;
    pmyspoint(80);

    delete pmya;
}

int main() {
    func();
    return 0;
}