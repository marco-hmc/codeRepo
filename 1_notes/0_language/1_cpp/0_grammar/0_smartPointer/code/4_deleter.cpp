#include <iostream>
#include <memory>

struct CustomDeleter {
    void operator()(int *ptr) {
        std::cout << "Custom deleter is called\n";
        delete ptr;
    }
};

int main() {
    std::unique_ptr<int, CustomDeleter> ptr(new int(42));
    std::cout << *ptr << '\n';

    return 0;
}