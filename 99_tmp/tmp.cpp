#include <iostream>

template <int A, int B, int C, int D>
struct Determinant2x2 {
    static constexpr int value = A * D - B * C;
};

int main() {
    // 定义一个 3x3 矩阵
    constexpr int a = 1, b = 2;
    constexpr int c = 4, d = 5;

    // 使用模板元编程计算行列式
    constexpr int determinant = Determinant2x2<a, b, c, d>::value;

    // 输出结果
    std::cout << "Determinant of the matrix:\n"
              << "| " << a << " " << b << " |\n"
              << "| " << c << " " << d << " |\n"
              << "is: " << determinant << std::endl;

    return 0;
}