#include <tuple>
#include <type_traits>

namespace jc {

    template <typename T, typename Tuple>
    struct is_among;

    template <typename T, template <typename...> class Tuple, typename... List>
    struct is_among<T, Tuple<List...>>
        : std::disjunction<std::is_same<T, List>...> {
    };

    template <typename T, typename Tuple>
    inline constexpr bool is_among_v = is_among<T, Tuple>::value;

}  // namespace jc

static_assert(jc::is_among_v<int, std::tuple<char, int, double>>);
static_assert(!jc::is_among_v<float, std::tuple<char, int, double>>);

int main() {}

/*
1. std::disjunction怎么用？
    用于在编译时对一系列类型特征进行逻辑或（OR）操作。如果给定的类型特征列表中至少有一个是 true，则 std::disjunction 的结果为 true；如果所有类型特征都是 false，则结果为 false。
*/