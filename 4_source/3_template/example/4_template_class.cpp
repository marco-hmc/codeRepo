#include <set>
#include <vector>

namespace jc {

template <typename T, template <typename...> class Container>
void f(const Container<T>&) {}

}  // namespace jc

int main() {
  jc::f(std::vector<int>{});
  jc::f(std::vector<double>{});
  jc::f(std::set<int>{});
}