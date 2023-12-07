#include <bitset>
#include <cassert>
#include <iterator>

template <int a, int b>
struct Tmp {
    constexpr int foo() { return a + b; }
};

int main() {
    Tmp<1, 2> tmp;
    constexpr int uyy = tmp.foo();
    return uyy;
}