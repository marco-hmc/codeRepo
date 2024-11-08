#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

class Variant {
   public:
    // 枚举类型，用于表示存储的值类型
    enum class Type { INT, DOUBLE, STRING, NONE };

    // 默认构造函数
    Variant() : type(Type::NONE) {}

    // 构造函数，用于存储 int 类型的值
    Variant(int value) : type(Type::INT) { data.intValue = value; }

    // 构造函数，用于存储 double 类型的值
    Variant(double value) : type(Type::DOUBLE) { data.doubleValue = value; }

    // 构造函数，用于存储 std::string 类型的值
    Variant(const std::string& value) : type(Type::STRING) {
        new (&data.stringValue) std::string(value);
    }

    // 析构函数
    ~Variant() { clear(); }

    // 拷贝构造函数
    Variant(const Variant& other) : type(other.type) { copyUnion(other); }

    // 移动构造函数
    Variant(Variant&& other) noexcept : type(other.type) {
        moveUnion(std::move(other));
        other.type = Type::NONE;
    }

    // 拷贝赋值运算符
    Variant& operator=(const Variant& other) {
        if (this != &other) {
            clear();
            type = other.type;
            copyUnion(other);
        }
        return *this;
    }

    // 移动赋值运算符
    Variant& operator=(Variant&& other) noexcept {
        if (this != &other) {
            clear();
            type = other.type;
            moveUnion(std::move(other));
            other.type = Type::NONE;
        }
        return *this;
    }

    // 获取存储的值类型
    Type getType() const { return type; }

    // 获取 int 类型的值
    int getInt() const {
        checkType(Type::INT);
        return data.intValue;
    }

    // 获取 double 类型的值
    double getDouble() const {
        checkType(Type::DOUBLE);
        return data.doubleValue;
    }

    // 获取 std::string 类型的值
    const std::string& getString() const {
        checkType(Type::STRING);
        return data.stringValue;
    }

   private:
    // 联合体，用于存储不同类型的值
    union Data {
        int intValue;
        double doubleValue;
        std::string stringValue;

        Data() {}
        ~Data() {}
    } data;

    Type type;

    // 清除存储的值
    void clear() {
        if (type == Type::STRING) {
            data.stringValue.~std::string();
        }
        type = Type::NONE;
    }

    // 检查存储的值类型
    void checkType(Type expected) const {
        if (type != expected) {
            throw std::runtime_error("Variant type mismatch");
        }
    }

    // 拷贝联合体数据
    void copyUnion(const Variant& other) {
        switch (other.type) {
            case Type::INT:
                data.intValue = other.data.intValue;
                break;
            case Type::DOUBLE:
                data.doubleValue = other.data.doubleValue;
                break;
            case Type::STRING:
                new (&data.stringValue) std::string(other.data.stringValue);
                break;
            case Type::NONE:
                break;
        }
    }

    // 移动联合体数据
    void moveUnion(Variant&& other) {
        switch (other.type) {
            case Type::INT:
                data.intValue = other.data.intValue;
                break;
            case Type::DOUBLE:
                data.doubleValue = other.data.doubleValue;
                break;
            case Type::STRING:
                new (&data.stringValue)
                    std::string(std::move(other.data.stringValue));
                break;
            case Type::NONE:
                break;
        }
    }
};

int main() {
    Variant v1 = 42;
    Variant v2 = 3.14;
    Variant v3 = std::string("Hello, Variant!");

    std::cout << "v1: " << v1.getInt() << std::endl;
    std::cout << "v2: " << v2.getDouble() << std::endl;
    std::cout << "v3: " << v3.getString() << std::endl;

    v1 = std::string("New value");
    std::cout << "v1: " << v1.getString() << std::endl;

    return 0;
}