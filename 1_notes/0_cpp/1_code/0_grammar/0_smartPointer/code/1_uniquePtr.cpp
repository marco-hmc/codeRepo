#include <iostream>

template <typename T>
class UniquePtr {
   public:
    explicit UniquePtr(T *p = nullptr) : ptr(p) {}
    ~UniquePtr() { delete ptr; }

   public:
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

   public:
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

   public:
    T *get() const { return ptr; }

    void reset(T *p = nullptr) {
        del();
        ptr = p;
    }

    T *release()  // 返回资源,资源的释放由调用方处理
    {
        T *pTemp = ptr;
        ptr = nullptr;
        return pTemp;
    }

   private:
    void del() {
        if (!ptr) return;
        delete ptr;
        ptr = nullptr;
    }

   private:
    T *ptr;
};

int main() {
    UniquePtr<int> ptr(new int(42));
    std::cout << "Value: " << *ptr << '\n';
    *ptr = 100;
    std::cout << "Value: " << *ptr << '\n';
    ptr.reset();

    // 尝试访问已释放的对象会导致运行时错误
    // std::cout << "Value: " << *ptr << '\n';
    return 0;
}
