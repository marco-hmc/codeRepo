#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

// 前向声明
class RxClass;
class RxObject;

// RxClass 类
class RxClass {
   public:
    RxClass(const std::string& name, RxClass* parent = nullptr)
        : className(name), parentClass(parent) {}

    const std::string& getName() const { return className; }

    void addMethod(const std::string& methodName, void (*method)(RxObject*)) {
        methods[methodName] = method;
    }

    void callMethod(RxObject* obj, const std::string& methodName) const {
        auto it = methods.find(methodName);
        if (it != methods.end()) {
            it->second(obj);
        } else {
            std::cerr << "Method " << methodName << " not found in class "
                      << className << std::endl;
        }
    }

    bool isSubclassOf(const RxClass* other) const {
        const RxClass* current = this;
        while (current != nullptr) {
            if (current == other) {
                return true;
            }
            current = current->parentClass;
        }
        return false;
    }

   private:
    std::string className;
    RxClass* parentClass;
    std::unordered_map<std::string, void (*)(RxObject*)> methods;
};

// RxObject 类
class RxObject {
   public:
    RxObject(RxClass* cls) : rxClass(cls) {}

    RxClass* getClass() const { return rxClass; }

    void callMethod(const std::string& methodName) {
        rxClass->callMethod(this, methodName);
    }

   private:
    RxClass* rxClass;
};

// 示例方法
void eatMethod(RxObject* obj) {
    std::cout << "Object of class " << obj->getClass()->getName()
              << " is eating." << std::endl;
}

void drinkMethod(RxObject* obj) {
    std::cout << "Object of class " << obj->getClass()->getName()
              << " is drinking." << std::endl;
}

// 使用 dynamic_cast 判断继承关系的示例类
class Animal {
   public:
    virtual ~Animal() = default;
};

class Dog : public Animal {};

int main() {
    // 使用自定义 RTTI 系统
    RxClass animalClass("Animal");
    RxClass dogClass("Dog", &animalClass);
    dogClass.addMethod("eat", eatMethod);
    dogClass.addMethod("drink", drinkMethod);

    RxObject dog(&dogClass);
    dog.callMethod("eat");
    dog.callMethod("drink");

    if (dogClass.isSubclassOf(&animalClass)) {
        std::cout << "Dog is a subclass of Animal." << std::endl;
    } else {
        std::cout << "Dog is not a subclass of Animal." << std::endl;
    }

    // 使用 dynamic_cast 判断继承关系
    Animal* animal = new Dog();
    if (dynamic_cast<Dog*>(animal)) {
        std::cout << "animal is a Dog." << std::endl;
    } else {
        std::cout << "animal is not a Dog." << std::endl;
    }

    delete animal;
    return 0;
}