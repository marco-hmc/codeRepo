#include <iostream>

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

// --4. 
#include <stdio.h>
#include <stdarg.h>

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

int main() {
    int result = sum(1, 2, 3, 4, 5);
    printNumbers(3, 1, 2, 3); // 输出:1 2 3
    std::cout << "Sum: " << result << std::endl;
    return 0;
}
