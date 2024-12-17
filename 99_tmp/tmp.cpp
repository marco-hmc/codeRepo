#include <iostream>

template <typename T>
class Base {
  public:
    virtual void compileSuccess() = 0;

    template <typename T2>
    virtual void compileSuccess(T2 a) = 0;
};

template <typename T>
class Derived : public Base<T> {
  public:
    void compileSuccess() override {
        std::cout << "Derived::compileSuccess()" << std::endl;
    }
};

int main() {
    Derived<int> d;
    d.compileSuccess();
    return 0;
}