#include <iostream>

// Abstract class defining the template method and primitive operations
class AbstractClass {
  public:
    // Template method
    void TemplateMethod() {
        PrimitiveOperation1();
        PrimitiveOperation2();
        ConcreteOperation();
    }

    virtual ~AbstractClass() {}

  protected:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;

    void ConcreteOperation() {
        std::cout << "Concrete operation common to all subclasses."
                  << std::endl;
    }
};

// Concrete class implementing the primitive operations
class ConcreteClass : public AbstractClass {
  protected:
    void PrimitiveOperation1() override {
        std::cout << "Primitive Operation 1 implemented by ConcreteClass."
                  << std::endl;
    }

    void PrimitiveOperation2() override {
        std::cout << "Primitive Operation 2 implemented by ConcreteClass."
                  << std::endl;
    }
};

int main() {
    ConcreteClass concreteObject;
    concreteObject.TemplateMethod();

    return 0;
}