#include <boost/any.hpp>
#include <iostream>

int main() {
    boost::any a = 42;  // 存储一个整数
    try {
        int x = boost::any_cast<int>(a);
        std::cout << "Value: " << x << std::endl;
    } catch (const boost::bad_any_cast& e) {
        std::cout << "Bad cast!" << std::endl;
    }
}