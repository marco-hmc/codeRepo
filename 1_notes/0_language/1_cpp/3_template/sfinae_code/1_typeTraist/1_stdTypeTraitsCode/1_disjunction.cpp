#include <tuple>
#include <type_traits>

/*
1. std::disjunction怎么用？
    用于在编译时对一系列类型特征进行逻辑或（OR）操作。
    如果给定的类型特征列表中至少有一个是 true，则 std::disjunction 的结果为 true；
    如果所有类型特征都是 false，则结果为 false。
*/

namespace disjunctionUsage {
    template <typename T, typename Tuple>
    struct is_among;

    template <typename T, template <typename...> class Tuple, typename... List>
    struct is_among<T, Tuple<List...>>
        : std::disjunction<std::is_same<T, List>...> {};

    template <typename T, typename Tuple>
    inline constexpr bool is_among_v = is_among<T, Tuple>::value;

    static_assert(is_among_v<int, std::tuple<char, int, double>>,
                  "int 应该在元组中");
    static_assert(!is_among_v<float, std::tuple<char, int, double>>,
                  "float 不应该在元组中");
}  // namespace disjunctionUsage

////////////////////////////////////////////////////////////////////
namespace disjunctionImpl {
    // 基本模板：当没有类型特征时，结果为 false
    template <typename...>
    struct disjunction : std::false_type {};

    // 特化版本：当至少有一个类型特征时，结果为 true
    template <typename B1>
    struct disjunction<B1> : B1 {};

    // 递归版本：如果第一个类型特征为 true，则结果为 true；否则继续检查下一个类型特征
    template <typename B1, typename... Bn>
    struct disjunction<B1, Bn...>
        : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};
}  // namespace disjunctionImpl

int main() { return 0; }