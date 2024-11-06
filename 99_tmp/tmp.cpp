#include <cstdint>
#include <iostream>

enum class MyEnum : uint8_t { Value1 = 1, Value2 = 2, Value3 = 3 };

void processEnum(uint8_t* enumPtr) {
    if (enumPtr) {
        std::cout << "Enum value: " << static_cast<int>(*enumPtr) << std::endl;
    } else {
        std::cout << "enumPtr is null" << std::endl;
    }
}

int main() {
    MyEnum myEnum = MyEnum::Value2;

    // 获取枚举值的地址并传递给函数
    // processEnum(reinterpret_cast<uint8_t*>(&myEnum));
    processEnum(static_cast<uint8_t*>(&myEnum));

    return 0;
}