

#include <iostream>
#include <sstream>
#include <string>

void test_1() {
    std::string str1 = std::to_string(123456);
    auto v1 = std::stoi("123");
    auto v2 = std::stol("111");
}

void test_2() {
    std::string s;
    std::getline(std::cin, s);
    int a = 0;
    std::cin >> a;
    std::cin.ignore();
    std::string s1;
    std::getline(std::cin, s1);
}

void test_3() {
    std::string s1 = "abcdefg";
    std::string s2 = "fg";

    if (s1.find(s2) != std::string::npos) {
        int pos = s1.find(s2);
        std::cout << s1.substr(pos, s2.size()) << std::endl;
    }
}

void test_4() {
    std::cout << "done" << std::endl;
    std::string str;
    std::getline(std::cin, str, '\n');
    while (!str.empty()) {
        std::getline(std::cin, str, '\n');
    }

    str = "1, 2, 3, 4";
    std::istringstream out(str);
    int num = 0;
    while (out >> num) {
        std::cout << num << std::endl;
    }
}

int main() {
    test_1();
    test_2();
    test_3();
    test_4();
    return 0;
}
