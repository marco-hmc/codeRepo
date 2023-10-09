#include <bitset>
#include <cassert>
#include <iterator>

namespace jc {

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

}  // namespace jc

void test_find_next() {
    std::bitset<8> b{ "10010111" };
    static constexpr int _next_set[] = { 1, 2, 4, 4, 7, 7, 7, 8, 8, 8 };
    static constexpr int _next_unset[] = { 3, 3, 3, 5, 5, 6, 8, 8, 8, 8 };

    for (std::size_t i = 0; i < std::size(_next_set); ++i) {
        assert(jc::find_next<true>(b, i) == _next_set[i]);
        assert(jc::find_next<false>(b, i) == _next_unset[i]);
    }
}

void test_find_prev() {
    std::bitset<8> b{ "10010110" };
    static constexpr int _prev_set[] = { 8, 8, 1, 2, 2, 4, 4, 4, 7, 7 };
    static constexpr int _prev_unset[] = { 8, 0, 0, 0, 3, 3, 5, 6, 6, 6 };

    for (std::size_t i = 0; i < std::size(_prev_set); ++i) {
        assert(jc::find_prev<true>(b, i) == _prev_set[i]);
        assert(jc::find_prev<false>(b, i) == _prev_unset[i]);
    }
}

void test_circular_find_next() {
    std::bitset<8> b{ "01010111" };
    static constexpr int _next_set[] = { 1, 2, 4, 4, 6, 6, 0, 0, 0, 0 };
    static constexpr int _next_unset[] = { 3, 3, 3, 5, 5, 7, 7, 3, 3, 3 };

    for (std::size_t i = 0; i < std::size(_next_set); ++i) {
        assert(jc::circular_find_next<true>(b, i) == _next_set[i]);
        assert(jc::circular_find_next<false>(b, i) == _next_unset[i]);
    }
}

void test_circular_find_prev() {
    std::bitset<8> b{ "10011001" };
    static constexpr int _prev_set[] = { 7, 0, 0, 0, 3, 4, 4, 4, 7, 7 };
    static constexpr int _prev_unset[] = { 6, 6, 1, 2, 2, 2, 5, 6, 6, 6 };

    for (std::size_t i = 0; i < std::size(_prev_set); ++i) {
        assert(jc::circular_find_prev<true>(b, i) == _prev_set[i]);
        assert(jc::circular_find_prev<false>(b, i) == _prev_unset[i]);
    }
}

int main() {
    test_find_next();
    test_find_prev();
    test_circular_find_next();
    test_circular_find_prev();
    return 0;
}