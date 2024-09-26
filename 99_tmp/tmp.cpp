#include <iostream>

// 前向声明类 Outer
class Outer;

// 前向声明类 Outer 内的嵌套类 Inner
class Outer {
   public:
 class Inner;
};

class Outer {
   public:
    class Inner {
       public:
     void display() { std::cout << "Inner class method called" << std::endl; }
    };

    void callInnerMethod(Inner& inner) { inner.display(); }
};

int main() {
    Outer::Inner innerObj;
    Outer outerObj;
    outerObj.callInnerMethod(innerObj);
    return 0;
}