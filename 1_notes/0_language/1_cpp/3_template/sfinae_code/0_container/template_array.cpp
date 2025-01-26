// 数组类型的元编程
// 可以使用模板元编程实现一些特殊类型的数组或数组操作。例如，编译期计算数组的长度、查找数组中的最大值等。

#include <iostream>

namespace Array_Meta {
    template <typename T, size_t N>
    struct array {
        T data[N];

        constexpr size_t size() const { return N; }

        constexpr T max() const {
            T max_val = data[0];
            for (size_t i = 1; i < N; ++i) {
                if (data[i] > max_val) {
                    max_val = data[i];
                }
            }
            return max_val;
        }
    };

    void test() {
        array<int, 5> arr = {1, 2, 3, 4, 5};
        std::cout << "Array size: " << arr.size() << std::endl;
        std::cout << "Max value: " << arr.max() << std::endl;
    }
}  // namespace Array_Meta

int main() {
    Array_Meta::test();
    return 0;
}