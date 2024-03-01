#include <iostream>
#include <string>
#include <memory>

class CowString {
public:
    CowString(const std::string& str) : data(new std::string(str)) {}

    void modify() {
        if (!data.unique()) {
            data.reset(new std::string(*data));
        }
        (*data)[0] = 'h';
    }

    const std::string& get() const {
        return *data;
    }

private:
    std::shared_ptr<std::string> data;
};

int main() {
    CowString str1("Hello, World!");
    CowString str2 = str1; // 共享相同的数据

    str1.modify(); // 进行实际的复制，因为需要修改数据

    std::cout << "str1: " << str1.get() << std::endl; // 输出: "hello, World!"
    std::cout << "str2: " << str2.get() << std::endl; // 输出: "Hello, World!"

    return 0;
}




