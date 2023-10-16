#include <iostream>

namespace MyNamespace {
    struct MyType {};

    void someFunction(MyType myArg) {
        std::cout << "Function in MyNamespace called" << std::endl;
    }
}

template <typename T>
void myTemplateFunction(T arg) {
    someFunction(arg); // 依赖于ADL查找someFunction
}

int main() {
    MyNamespace::MyType obj;
    myTemplateFunction(obj); // 调用myTemplateFunction
    return 0;
}