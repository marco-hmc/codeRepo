#include <iostream>

class Animal1 {
   public:
    virtual void eat() { std::cout << "Animal1 eats" << std::endl; }
};

class Dog1 : public Animal1 {
   public:
    virtual void bark() { std::cout << "Dog1 barks" << std::endl; }
};

class Animal2 {
   public:
    void eat() { std::cout << "Animal2 eats" << std::endl; }
};

class Dog2 : public Animal2 {
   public:
    virtual void bark() { std::cout << "Dog2 barks" << std::endl; }
};

int main() {
    Animal1 a1;
    Dog1 d1;
    Animal2 a2;
    Dog2 d2;

    std::cout << "Size of Animal1: " << sizeof(a1) << std::endl;
    std::cout << "Size of Dog1: " << sizeof(d1) << std::endl;
    std::cout << "Size of Animal2: " << sizeof(a2) << std::endl;
    std::cout << "Size of Dog2: " << sizeof(d2) << std::endl;

    return 0;
}