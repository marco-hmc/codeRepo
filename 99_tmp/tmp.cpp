#include <memory>
#include <stdexcept>
#include <typeinfo>

class Any {
  public:
    template <typename T>
    Any(T value)
        : ptr_(std::unique_ptr<void, void (*)(void *)>(
              new T(std::move(value)),
              [](void *ptr) { static_cast<T *>(ptr)->~T(); })),
          type_(&typeid(T)) {}

    ~Any() = default;

    template <typename T>
    T &get() {
        if (typeid(T) != *type_) {
            throw std::bad_cast();
        }
        return *static_cast<T *>(ptr_.get());
    }

    // 不删除拷贝构造和赋值操作
    // Any(const Any &) = delete;
    // Any &operator=(const Any &) = delete;
    Any(Any &&other) noexcept = default;
    Any &operator=(Any &&other) noexcept = default;

  private:
    std::unique_ptr<void, void (*)(void *)> ptr_;
    const std::type_info *type_;
};

int main() {
    Any a(42);
    Any b = a;  // 调用默认拷贝构造函数
    // 当 a 和 b 析构时，会出现双重释放问题
    return 0;
}