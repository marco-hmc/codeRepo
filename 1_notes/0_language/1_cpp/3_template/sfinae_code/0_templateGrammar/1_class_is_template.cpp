#include <vector>

namespace {
    template <typename T, template <typename...> class Container>
    void f(const Container<T>&) {}

}  // namespace

int main() { f(std::vector<int>{}); }