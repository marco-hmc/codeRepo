
#include <functional>
#include <iostream>

template <typename T>
class reference_wrapper {
public:
    explicit reference_wrapper(T& ref) : ptr_(std::addressof(ref)) {}
    
    operator T&() const { return *ptr_; }
    T& get() const { return *ptr_; }
    
private:
    T* ptr_;
};

template <typename T>
reference_wrapper<T> ref(T& ref) {
    return reference_wrapper<T>(ref);
}

int main() {
    int x = 5;
    int& ref_x = ref(x);
    
    ref_x = 10;

    std::cout << "x: " << x << '\n'; // Output: x: 10

    return 0;
}