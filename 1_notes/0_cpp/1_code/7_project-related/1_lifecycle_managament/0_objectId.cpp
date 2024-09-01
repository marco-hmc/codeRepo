#include <iostream>
#include <string>
#include <memory>

class objectId {
private:
    std::string id;

public:
    objectId() {
        // 生成唯一的对象标识符
        id = generateUniqueId();
    }

    std::string getId() {
        // 获取对象标识符
        return id;
    }

    void setId(const std::string& newId) {
        // 设置对象标识符
        id = newId;
    }

private:
    std::string generateUniqueId() {
        // 生成唯一的标识符的逻辑
        // 这里使用简单的递增数字作为示例
        static int counter = 0;
        return std::to_string(counter++);
    }
};

class ObjectPointer {
private:
    std::shared_ptr<objectId> objectIdPtr;
    void* objectPtr;

public:
    ObjectPointer(void* ptr) : objectPtr(ptr) {
        // 创建一个新的objectId并存储在指针中
        objectIdPtr = std::make_shared<objectId>();
    }

    void* getObjectPtr() {
        // 获取对象指针
        return objectPtr;
    }

    std::string getObjectId() {
        // 获取对象标识符
        return objectIdPtr->getId();
    }
};

int main() {
    // 创建一个对象指针
    int* obj = new int(42);
    ObjectPointer objPtr(obj);

    // 获取对象指针和标识符并打印
    std::cout << "Object Pointer: " << objPtr.getObjectPtr() << '\n';
    std::cout << "Object ID: " << objPtr.getObjectId() << '\n';

    // 释放对象指针
    delete obj;

    return 0;
}
