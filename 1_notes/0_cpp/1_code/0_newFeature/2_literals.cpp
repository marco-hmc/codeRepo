#include <cmath>
#include <iostream>
#include <string>

// 是使用字面量方式实现的.在C++中,字面量是表示固定值的文本形式.整数字面量可以加上后缀来指定其类型.
unsigned int x = 1u;
unsigned long y = 1ul; // 可以32位,一般64位
unsigned long z = 1LU;
unsigned long long w = 1ull; // 至少64位
unsigned long long v = 1LLU;
long a = 1l;
long b = 1L;
long long c = 1ll;
long long d = 1LL;

// `unsigned long long` parameter required for integer literal.
// Usage: 24_celsius; // == 75
long long operator"" _celsius(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}

// String to integer conversion:
// `const char*` and `std::size_t` required as parameters.
// Usage: "123"_int; // == 123, with type `int`
int operator"" _int(const char *str, std::size_t) { return std::stoi(str); }

int main() {
  // 使用_celsius字面量将摄氏温度转换为华氏温度
  long long tempFahrenheit = 24_celsius;
  std::cout << "24 degrees Celsius is " << tempFahrenheit
            << " degrees Fahrenheit.\n";

  // 使用_int字面量将字符串转换为整数
  int num = "123"_int;
  std::cout << "The integer value of the string \"123\" is " << num << ".\n";

  return 0;
}