#include <iostream>
#include <memory>
#include <string>

class CowString {
  public:
    CowString(const std::string& str) : data(new std::string(str)) {}

    void modify() {
        if (!data.unique()) {
            data.reset(new std::string(*data));
        }
        (*data)[0] = 'h';
    }

    const std::string& get() const { return *data; }

  private:
    std::shared_ptr<std::string> data;
};

int main() {
    CowString str1("Hello, World!");
    CowString str2 = str1;

    str1.modify();

    std::cout << "str1: " << str1.get() << '\n';
    std::cout << "str2: " << str2.get() << '\n';

    return 0;
}
