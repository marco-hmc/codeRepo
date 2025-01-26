// 表达式模板（Expression Templates）
// 表达式模板是一种用于优化数值计算的技术，它将数学运算推迟到编译期，从而避免在运行时进行不必要的临时对象创建。常见于需要高效数值计算的领域，如线性代数、图像处理等。

#include <iostream>

namespace ExpressionTemplates {
    template <typename T>
    struct expr {
        virtual T eval() const = 0;
    };

    template <typename T>
    struct constant : public expr<T> {
        T value;
        constant(T val) : value(val) {}
        T eval() const override { return value; }
    };

    template <typename T, typename L, typename R>
    struct add : public expr<T> {
        L left;
        R right;
        add(L l, R r) : left(l), right(r) {}
        T eval() const override { return left.eval() + right.eval(); }
    };
}  // namespace ExpressionTemplates

int main() {
    ExpressionTemplates::constant<int> c1(3);
    ExpressionTemplates::constant<int> c2(4);
    ExpressionTemplates::add<int, ExpressionTemplates::constant<int>,
                             ExpressionTemplates::constant<int>>
        sum(c1, c2);
    std::cout << "Result: " << sum.eval() << std::endl;
    return 0;
}