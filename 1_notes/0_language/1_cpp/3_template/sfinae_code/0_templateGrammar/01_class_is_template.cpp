#include <vector>

/*
  ## 模板参数中的常见用法

  1. 模板参数如何接受一个带入参的模板类？
     通过模板模板参数的方式，可以接受一个带入参的模板类。
     例如，下面的 f 函数接受一个容器类，其中的元素类型为 T。
*/

namespace TemplateTemplateParameter {

    template <typename T, template <typename...> class Container>
    void f(const Container<T>& /*unused*/) {}

    void test() { f(std::vector<int>{}); }

}  // namespace TemplateTemplateParameter

int main() {
    TemplateTemplateParameter::test();
    return 0;
}