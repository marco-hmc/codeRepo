#include <iostream>
#include <memory>

class MyClass {
   public:
    void setValue(int val) { value = val; }
    int getValue() const { return value; }

   private:
    int value = 0;
};

void modifyObject(MyClass*& ptr) {
    if (ptr) {
        ptr->setValue(42);
    }
}

int main() {
    std::unique_ptr<MyClass> ptr{nullptr};  // = std::make_unique<MyClass>();
    std::cout << "Value after modification: " << ptr->getValue() << std::endl;
    MyClass* rawPtr = ptr.get();
    (*rawPtr).setValue(44);
    std::cout << "Value after modification: " << ptr->getValue() << std::endl;

    return 0;
}