#include <iostream>

class GrandParent {
public:
    virtual void myFunction() {
        std::cout << "GrandParent's function" << std::endl;
    }
};

class Parent : public GrandParent {
public:
    virtual void myFunction() override {
        std::cout << "Parent's function" << std::endl;
    }
};

class Child : public Parent {
public:
    virtual void myFunctions() {
        std::cout << "Child's function" << std::endl;
    }
};

int main() {
    GrandParent* gp = new GrandParent();
    Parent* p = new Parent();
    Child* c = new Child();

    gp->myFunction(); // 输出 "GrandParent's function"
    p->myFunction();  // 输出 "Parent's function"
    c->myFunction();  // ?

    delete gp;
    delete p;
    delete c;

    return 0;
}