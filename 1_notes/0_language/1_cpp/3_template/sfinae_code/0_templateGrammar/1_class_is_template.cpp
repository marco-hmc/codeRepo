#include <vector>

/*
    模板参数如何接受一个带入参的模板类？
*/
namespace {
    template <typename T, template <typename...> class Container>
    void f(const Container<T>&) {}

}  // namespace

int main() { f(std::vector<int>{}); }