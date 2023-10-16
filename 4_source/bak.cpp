#include <bitset>
#include <cassert>
#include <iterator>
#include <type_traits>
#include <iostream>

using namespace std;

namespace jc {
    template <bool IsSet = true, std::size_t N>
    void find_next(const std::bitset<N>& b, std::size_t cur) {
        const std::type_info& info = typeid(b);
        cout << typeid(b).name() << endl;
        cout << info.name() << endl;
    }


}  // namespace jc


int main() {
    std::bitset<12> b{ "100101110000" };
    static constexpr int _next_set[] = { 1, 2, 4, 4, 7, 7, 7, 8, 8, 8 };

    for (std::size_t i = 0; i < std::size(_next_set); ++i) {
        jc::find_next<true>(b, i);
    }
    return 0;
}