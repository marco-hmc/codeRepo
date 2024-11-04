#include <cassert>
#include <set>
#include <vector>

template <int a, int b>
struct Tmp {
    constexpr int foo() { return a + b; }
};

namespace jc {

template <typename T, template <typename...> class Container>
void f(const Container<T> &) {}

} // namespace jc

int main() {
  {
    jc::f(std::vector<int>{});
  jc::f(std::vector<double>{});
  jc::f(std::set<int>{});
  }
  {    Tmp<1, 2> tmp;
    constexpr int uyy = tmp.foo();
    return uyy;
    }
}
