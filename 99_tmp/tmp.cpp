#include <iostream>

namespace _nmsp2 {
    class A {
      public:
        A() { std::cout << "A::A()构造函数被执行" << std::endl; }
        A(const A& tmpobj) {
            std::cout << "A::A()拷贝构造函数被执行" << std::endl;
        }

        A& operator=(const A& tmpaobj) {
            std::cout << "A::operator=()拷贝赋值运算符被执行" << std::endl;
            printf("拷贝赋值运算符中tmpaobj的地址为%p\n", &tmpaobj);
            return *this;
        }

        ~A() { std::cout << "A::~A()析构函数被执行" << std::endl; }
    };

    A operator+(const A& obj1, const A& obj2) {
        A tmpobj;
        printf("tmpobj的地址为%p\n", &tmpobj);
        return tmpobj;  // 编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数拷贝给这个临时对象；
                        // 然后返回的是这个临时对象；
    }

    void func() {
        A myobj1;
        printf("myobj1的地址为%p\n", &myobj1);

        A myobj2;
        printf("myobj2的地址为%p\n", &myobj2);

        A resultobj;
        resultobj = myobj1 + myobj2;  // 拷贝赋值运算符

        // A resultobj = myobj1 + myobj2; // 拷贝构造函数

        printf("resultobj的地址为%p\n", &resultobj);
        return;
    }
}  // namespace _nmsp2

int main() {
    _nmsp2::func();
    return 0;
}