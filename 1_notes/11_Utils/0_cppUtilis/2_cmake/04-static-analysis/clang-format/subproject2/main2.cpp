#include <iostream>

class TestClass {
public:
    TestClass();
};

TestClass::TestClass() {

}

int main(int argc, char* argv[])
{
    std::cout << "Hello Main2!" << '\n';
    int* x = NULL;
    std::cout << *x << '\n';
    return 0;
}
