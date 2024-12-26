#include <bitset>
#include <cassert>

/*
  ## 非类型模板参数的常见用法

  1. 使用非类型模板参数来控制函数行为：
     通过非类型模板参数，可以在编译时传递常量值，从而控制函数的行为。
     例如，下面的 find_next 和 find_prev 函数使用布尔值 IsSet 来决定查找的条件。
*/

namespace BitsetOperations {

    template <bool IsSet = true, std::size_t N>
    std::size_t find_next(const std::bitset<N>& b, std::size_t cur) {
        for (std::size_t i = cur + 1; i < N; ++i) {
            if (!(b.test(i) ^ IsSet)) {
                return i;
            }
        }
        return N;
    }

    template <bool IsSet = true, std::size_t N>
    std::size_t find_prev(const std::bitset<N>& b, std::size_t cur) {
        if (cur > N) {
            cur = N;
        }
        for (int i = static_cast<int>(cur) - 1; i >= 0; --i) {
            if (!(b.test(i) ^ IsSet)) {
                return i;
            }
        }
        return N;
    }

    template <bool IsSet = true, std::size_t N>
    std::size_t circular_find_next(const std::bitset<N>& b, std::size_t cur) {
        if (cur > N) {
            cur = N;
        }
        std::size_t res = find_next<IsSet>(b, cur);
        if (res != N) {
            return res;
        }
        for (std::size_t i = 0; i < cur; ++i) {
            if (!(b.test(i) ^ IsSet)) {
                return i;
            }
        }
        return N;
    }

    template <bool IsSet = true, std::size_t N>
    std::size_t circular_find_prev(const std::bitset<N>& b, std::size_t cur) {
        if constexpr (N == 0) {
            return N;
        }
        std::size_t res = find_prev<IsSet>(b, cur);
        if (res != N) {
            return res;
        }
        for (std::size_t i = N - 1; i > cur; --i) {
            if (!(b.test(i) ^ IsSet)) {
                return i;
            }
        }
        return N;
    }

}  // namespace BitsetOperations

void test_find_next() {
    std::bitset<8> b{"10010111"};
    static constexpr int next_set[] = {1, 2, 4, 4, 7, 7, 7, 8, 8, 8};
    static constexpr int next_unset[] = {3, 3, 3, 5, 5, 6, 8, 8, 8, 8};

    for (std::size_t i = 0; i < std::size(next_set); ++i) {
        assert(BitsetOperations::find_next<true>(b, i) == next_set[i]);
        assert(BitsetOperations::find_next<false>(b, i) == next_unset[i]);
    }
}

void test_find_prev() {
    std::bitset<8> b{"10010110"};
    static constexpr int prev_set[] = {8, 8, 1, 2, 2, 4, 4, 4, 7, 7};
    static constexpr int prev_unset[] = {8, 0, 0, 0, 3, 3, 5, 6, 6, 6};

    for (std::size_t i = 0; i < std::size(prev_set); ++i) {
        assert(BitsetOperations::find_prev<true>(b, i) == prev_set[i]);
        assert(BitsetOperations::find_prev<false>(b, i) == prev_unset[i]);
    }
}

void test_circular_find_next() {
    std::bitset<8> b{"01010111"};
    static constexpr int next_set[] = {1, 2, 4, 4, 6, 6, 0, 0, 0, 0};
    static constexpr int next_unset[] = {3, 3, 3, 5, 5, 7, 7, 3, 3, 3};

    for (std::size_t i = 0; i < std::size(next_set); ++i) {
        assert(BitsetOperations::circular_find_next<true>(b, i) == next_set[i]);
        assert(BitsetOperations::circular_find_next<false>(b, i) ==
               next_unset[i]);
    }
}

void test_circular_find_prev() {
    std::bitset<8> b{"10011001"};
    static constexpr int prev_set[] = {7, 0, 0, 0, 3, 4, 4, 4, 7, 7};
    static constexpr int prev_unset[] = {6, 6, 1, 2, 2, 2, 5, 6, 6, 6};

    for (std::size_t i = 0; i < std::size(prev_set); ++i) {
        assert(BitsetOperations::circular_find_prev<true>(b, i) == prev_set[i]);
        assert(BitsetOperations::circular_find_prev<false>(b, i) ==
               prev_unset[i]);
    }
}

int main() {
    test_find_next();
    test_find_prev();
    test_circular_find_next();
    test_circular_find_prev();
}