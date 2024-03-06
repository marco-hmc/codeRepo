#include <iostream>
#include <numeric>
#include <stdarg.h>
#include <stdio.h>

// --1. fold expression
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

// --2. variadic template
int sum2() {
    return 0;
}
template<typename T, typename... Args>
T sum2(T first, Args... args) {
    return first + sum(args...);
}

// --3. others
template <typename First, typename... Args>
auto sum3(const First first, const Args... args) -> decltype(first) {
  const auto values = {first, args...};
  return std::accumulate(values.begin(), values.end(), First{0});
}

void test_sum() {
  {
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
  }
  {
    int result = sum2(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
  }
  {
    int result = sum3(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;
  }
}

// 1. recursive parameter unpack
template <typename T0> void printf1(T0 value) {
  std::cout << value << std::endl;
}
template <typename T, typename... Ts> void printf1(T value, Ts... args) {
  std::cout << value << std::endl;
  printf1(args...);
}

// 2. variadic template parameter unfold
template <typename T0, typename... T> void printf2(T0 t0, T... t) {
  std::cout << t0 << std::endl;
  if constexpr (sizeof...(t) > 0)
    printf2(t...);
}

// 3. parameter unpack using initializer_list
template <typename T, typename... Ts> auto printf3(T value, Ts... args) {
  std::cout << value << std::endl;
  (void)std::initializer_list<T>{
      ([&args] { std::cout << args << std::endl; }(), value)...};
}

// 4. args
void printNumbers(int count, ...)
{
// 下面三个都是和va_list搭配使用的宏
// `va_start`: 该宏用于初始化`va_list`类型的变量,以便访问不定长参数列表中的参数.
//             它接受两个参数,第一个参数是一个`va_list`类型的变量,第二个参数是最后一个已知的固定参数.这个宏必须在访问不定长参数之前调用.
// `va_arg`: 该宏用于从不定长参数列表中获取下一个参数的值.
//             它接受两个参数,第一个参数是一个`va_list`类型的变量,第二个参数是要获取的参数的类型.这个宏可以多次调用,每次调用都会返回下一个参数的值.
// `va_end`: 该宏用于清理`va_list`类型的变量.
//             它接受一个参数,即要清理的`va_list`类型的变量.这个宏必须在不定长参数处理完毕后调用.

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        printf("%d ", num);
    }

    va_end(args);
}

void test_print() {
  printf1(3, 1, 2, 3);
  printf2(3, 1, 2, 3);
  printf3(3, 1, 2, 3);
  printNumbers(3, 1, 2, 3);
}

// sizeof...
template <typename... Ts> void magic(Ts... args) {
  std::cout << sizeof...(args) << std::endl;
}

void test_magic() {
  magic();
  magic(1);
  magic(1, "");
}

int main() {
  test_sum();
  test_print();
  test_magic();
  return 0;
}
