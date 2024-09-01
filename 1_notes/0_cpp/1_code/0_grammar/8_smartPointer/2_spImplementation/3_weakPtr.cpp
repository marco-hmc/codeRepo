#include <iostream>
#include <memory>

template <typename T> class weakPtr {
private:
  T *ptr;

public:
  weakPtr() : ptr(nullptr) {}
  weakPtr(T *p) : ptr(p) {}

  bool expired() const { return ptr == nullptr; }

  std::shared_ptr<T> lock() const {
    if (expired()) {
      return nullptr;
    }
    return std::shared_ptr<T>(ptr);
  }
};

int main() {
  std::shared_ptr<int> sharedPtr(new int(42));
  weakPtr<int> weak(sharedPtr.get());

  std::cout << "Expired: " << (weak.expired() ? "true" : "false") << '\n';

  std::shared_ptr<int> lockedPtr = weak.lock();
  if (lockedPtr) {
    std::cout << "Value: " << *lockedPtr << '\n';
  } else {
    std::cout << "Weak pointer expired." << '\n';
  }

  return 0;
}
