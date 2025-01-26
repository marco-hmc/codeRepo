#include <iostream>
#include <type_traits>

/*
1. std::conditional 怎么用？
    std::conditional 是一个模板元编程工具，用于根据布尔常量 `B` 的值选择两种类型之一。
    如果 `B` 为 true，则选择类型 `T`；否则选择类型 `F`。
*/

namespace conditionalUsage {
    template <bool B, typename T, typename F>
    using select_type = typename std::conditional<B, T, F>::type;

    struct TrueType {
        static constexpr const char* name = "TrueType";
    };

    struct FalseType {
        static constexpr const char* name = "FalseType";
    };

    using SelectedType1 = select_type<true, TrueType, FalseType>;
    using SelectedType2 = select_type<false, TrueType, FalseType>;

    static_assert(std::is_same<SelectedType1, TrueType>::value,
                  "SelectedType1 应该是 TrueType");
    static_assert(std::is_same<SelectedType2, FalseType>::value,
                  "SelectedType2 应该是 FalseType");

    void test() {
        std::cout << "SelectedType1: " << SelectedType1::name << std::endl;
        std::cout << "SelectedType2: " << SelectedType2::name << std::endl;
    }
}  // namespace conditionalUsage

namespace conditionalImpl {

    template <bool B, typename T, typename F>
    struct conditional {
        using type = T;
    };

    template <typename T, typename F>
    struct conditional<false, T, F> {
        using type = F;
    };

    template <bool B, typename T, typename F>
    using select_type = typename conditional<B, T, F>::type;

    struct TrueType {
        static constexpr const char* name = "TrueType";
    };

    struct FalseType {
        static constexpr const char* name = "FalseType";
    };

    using SelectedType1 = select_type<true, TrueType, FalseType>;
    using SelectedType2 = select_type<false, TrueType, FalseType>;

    static_assert(std::is_same<SelectedType1, TrueType>::value,
                  "SelectedType1 应该是 TrueType");
    static_assert(std::is_same<SelectedType2, FalseType>::value,
                  "SelectedType2 应该是 FalseType");

    void test() {
        std::cout << "SelectedType1: " << SelectedType1::name << std::endl;
        std::cout << "SelectedType2: " << SelectedType2::name << std::endl;
    }
}  // namespace conditionalImpl

int main() {
    conditionalUsage::test();
    conditionalImpl::test();
    return 0;
}