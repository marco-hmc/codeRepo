#include <iostream>

// 模板编程通过类型可以找到对应的函数(如不同命名空间下的),这个就叫做ADL.
// 下面这个例子展示了如何通过模板编程和ADL，使得模板函数能够在不知道具体类型的情况下，利用参数的类型在相应的命名空间中查找相应的函数。

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