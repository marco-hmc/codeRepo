#include <iostream>
#include <utility>

class Base {
   public:
    int* data;

    Base() : data(new int(42)) {
        std::cout << "Base default constructor called" << std::endl;
    }

    Base(Base&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Base move constructor called" << std::endl;
    }

    virtual ~Base() {
        delete data;
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
   public:
    int* extraData;

    Derived() : extraData(new int(84)) {
        std::cout << "Derived default constructor called" << std::endl;
    }

    Derived(Derived&& other) noexcept
        : Base(std::move(other)), extraData(other.extraData) {
        other.extraData = nullptr;
        std::cout << "Derived move constructor called" << std::endl;
    }

    ~Derived() {
        delete extraData;
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    Derived d1;
    Derived d2 = std::move(d1);

    // 尝试使用被移动的对象 d1
    if (d1.data == nullptr) {
        std::cout << "d1's data has been moved" << std::endl;
    }
    if (d1.extraData == nullptr) {
        std::cout << "d1's extraData has been moved" << std::endl;
    }

    return 0;
}