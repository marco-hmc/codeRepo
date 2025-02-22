#include <iostream>
#include <string>
#include <unordered_map>

// 反射注册表
std::unordered_map<std::string, void*> reflectionRegistry;

// 反射函数
template <typename T>
void* Reflect(const std::string& identifier) {
    if (reflectionRegistry.count(identifier) > 0) {
        return reflectionRegistry[identifier];
    }
    return nullptr;
}

// 属性模板
template <typename T>
struct Property {
    T value;

    Property(const std::string& identifier) {
        reflectionRegistry[identifier] = &value;
    }
};

// 方法模板
template <typename... Args>
struct Method {
    void (*func)(Args...);

    Method(const std::string& identifier, void (*f)(Args...)) {
        reflectionRegistry[identifier] = reinterpret_cast<void*>(f);
    }
};

// 示例类
class MyClass {
  public:
    Property<int> myInt{"myInt"};
    Property<std::string> myString{"myString"};
    Method<> myMethod{"MyMethod", &MyClass::MyMethod};  // 添加Method成员变量

    static void MyMethod() { std::cout << "Hello from MyMethod!" << '\n'; }
};

int main() {
    MyClass obj;

    // 使用反射函数获取属性指针并修改属性值
    int* intPtr = static_cast<int*>(Reflect<int>("myInt"));
    if (intPtr) {
        *intPtr = 42;
    }

    std::string* stringPtr =
        static_cast<std::string*>(Reflect<std::string>("myString"));
    if (stringPtr) {
        *stringPtr = "Hello, reflection!";
    }

    // 使用反射函数调用方法
    void (*methodPtr)() =
        reinterpret_cast<void (*)()>(Reflect<void()>("MyMethod"));
    if (methodPtr) {
        methodPtr();
    }

    // 输出属性值以验证修改
    std::cout << "myInt: " << obj.myInt.value << '\n';
    std::cout << "myString: " << obj.myString.value << '\n';

    return 0;
}