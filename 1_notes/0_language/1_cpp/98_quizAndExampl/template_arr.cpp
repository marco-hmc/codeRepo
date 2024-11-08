#include <cassert>
#include <cstddef>

namespace jc {

template <typename T, typename U>
constexpr bool less(const T &a, const U &b) {
    return a < b;
}

template <typename T, std::size_t M, std::size_t N>
constexpr bool less(T (&a)[M], T (&b)[N]) {
    for (std::size_t i = 0; i < M && i < N; ++i) {
        if (a[i] < b[i]) {
            return true;
        }
        if (b[i] < a[i]) {
            return false;
        }
    }
    return M < N;
}

}  // namespace jc

static_assert(jc::less(0, 42));
static_assert(!jc::less("down", "demo"));
static_assert(jc::less("demo", "down"));

int main() {}