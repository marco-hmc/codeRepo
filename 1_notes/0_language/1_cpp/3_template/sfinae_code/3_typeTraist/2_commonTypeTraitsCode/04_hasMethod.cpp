#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

/*
2. 检测习惯用法 (Detection idiom)
    检测习惯用法是一种模板元编程技术，用于在编译时检查类型是否具有特定的成员函数或成员类型。
    它常用于 SFINAE（Substitution Failure Is Not An Error）技术中，根据条件选择合适的模板实例化。
*/

namespace detectionIdiomUsage {
    // 定义 detector 模板
    template <typename, template <typename...> class Op, typename... Args>
    struct detector : std::false_type {};

    template <template <typename...> class Op, typename... Args>
    struct detector<std::void_t<Op<Args...>>, Op, Args...> : std::true_type {};

    template <template <typename...> class Op, typename... Args>
    using is_detected = detector<void, Op, Args...>;

    // 定义 has_emplace_back 检测
    template <typename T>
    using has_emplace_back = decltype(std::declval<T>().emplace_back(
        std::declval<typename T::value_type>()));

    template <typename T>
    constexpr bool has_emplace_back_v =
        is_detected<has_emplace_back, std::remove_reference_t<T>>::value;

    // 静态断言测试
    static_assert(has_emplace_back_v<std::vector<int>>,
                  "std::vector<int> 应该具有 emplace_back 成员函数");
    static_assert(has_emplace_back_v<std::vector<int>&>,
                  "std::vector<int>& 应该具有 emplace_back 成员函数");
    static_assert(has_emplace_back_v<std::vector<int>&&>,
                  "std::vector<int>&& 应该具有 emplace_back 成员函数");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_emplace_back_v<std::vector<int>>: "
                  << has_emplace_back_v<std::vector<int>> << std::endl;
        std::cout << "has_emplace_back_v<std::vector<int>&>: "
                  << has_emplace_back_v<std::vector<int>&> << std::endl;
        std::cout << "has_emplace_back_v<std::vector<int>&&>: "
                  << has_emplace_back_v<std::vector<int>&&> << std::endl;
    }
}  // namespace detectionIdiomUsage

////////////////////////////////////////////////////////////////////
namespace detectionIdiomImpl {
    // detector 的实现
    template <typename, template <typename...> class Op, typename... Args>
    struct detector : std::false_type {};

    template <template <typename...> class Op, typename... Args>
    struct detector<std::void_t<Op<Args...>>, Op, Args...> : std::true_type {};

    template <template <typename...> class Op, typename... Args>
    using is_detected = detector<void, Op, Args...>;

    // has_emplace_back 的实现
    template <typename T>
    using has_emplace_back = decltype(std::declval<T>().emplace_back(
        std::declval<typename T::value_type>()));

    template <typename T>
    constexpr bool has_emplace_back_v =
        is_detected<has_emplace_back, std::remove_reference_t<T>>::value;

    // 静态断言测试
    static_assert(has_emplace_back_v<std::vector<int>>,
                  "std::vector<int> 应该具有 emplace_back 成员函数");
    static_assert(has_emplace_back_v<std::vector<int>&>,
                  "std::vector<int>& 应该具有 emplace_back 成员函数");
    static_assert(has_emplace_back_v<std::vector<int>&&>,
                  "std::vector<int>&& 应该具有 emplace_back 成员函数");

    void test() {
        std::cout << std::boolalpha;
        std::cout << "has_emplace_back_v<std::vector<int>>: "
                  << has_emplace_back_v<std::vector<int>> << std::endl;
        std::cout << "has_emplace_back_v<std::vector<int>&>: "
                  << has_emplace_back_v<std::vector<int>&> << std::endl;
        std::cout << "has_emplace_back_v<std::vector<int>&&>: "
                  << has_emplace_back_v<std::vector<int>&&> << std::endl;
    }
}  // namespace detectionIdiomImpl

int main() {
    detectionIdiomUsage::test();
    detectionIdiomImpl::test();
    return 0;
}