// Linq（Language Integrated Query）是一个强大的查询语言，允许我们以函数式风格操作集合。
// 在 C++ 中，可以使用范围操作符、Lambda 表达式和 std::transform 等技术来实现类似 Linq 的操作。

#include <algorithm>
#include <iostream>
#include <vector>

namespace linq_demo {
    template <typename T, typename Func>
    std::vector<T> where(const std::vector<T>& input, Func&& func) {
        std::vector<T> result;
        std::copy_if(input.begin(), input.end(), std::back_inserter(result),
                     func);
        return result;
    }
}  // namespace linq_demo

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = linq_demo::where(vec, [](int x) { return x % 2 == 0; });

    for (int num : result) {
        std::cout << num << " ";  // 输出: 2 4
    }
    std::cout << std::endl;
    return 0;
}