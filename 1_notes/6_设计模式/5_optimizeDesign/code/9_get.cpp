#include <functional>
#include <iostream>
#include <optional>
#include <vector>

class VecWrapper {
  public:
    VecWrapper(const std::vector<int>& vec) : vec_(vec) {}

    std::optional<std::reference_wrapper<int>> get(size_t index) {
        if (index < vec_.size()) {
            return std::optional<std::reference_wrapper<int>>(vec_[index]);
        } else {
            return std::nullopt;
        }
    }

  private:
    std::vector<int> vec_;
};

int main() {
    std::vector<int> data = {10, 20, 30, 40, 50};
    VecWrapper vec(data);

    // 性能读
    auto x1 = vec.get(3).value().get();
    std::cout << "性能读: " << x1 << std::endl;

    // 安全读
    auto x2 = vec.get(3).value().get();
    std::cout << "安全读: " << x2 << std::endl;

    // 性能写
    vec.get(3).value().get() = 42;
    std::cout << "性能写: " << data[3] << std::endl;

    // 安全写
    vec.get(3).value().get() = 42;
    std::cout << "安全写: " << data[3] << std::endl;

    return 0;
}