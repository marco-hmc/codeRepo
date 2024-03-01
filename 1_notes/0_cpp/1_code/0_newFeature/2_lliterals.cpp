#include <iostream>
#include <cmath>

// `unsigned long long` parameter required for integer literal.
// Usage: 24_celsius; // == 75
long long operator"" _celsius(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}

// String to integer conversion:
// `const char*` and `std::size_t` required as parameters.
// Usage: "123"_int; // == 123, with type `int`
int operator"" _int(const char *str, std::size_t) {
  return std::stoi(str);
}

int main() {
    // 使用_celsius字面量将摄氏温度转换为华氏温度
    long long tempFahrenheit = 24_celsius;
    std::cout << "24 degrees Celsius is " << tempFahrenheit << " degrees Fahrenheit.\n";

    // 使用_int字面量将字符串转换为整数
    int num = "123"_int;
    std::cout << "The integer value of the string \"123\" is " << num << ".\n";

    return 0;
}