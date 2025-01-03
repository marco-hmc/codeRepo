#include <iostream>
#include <type_traits>

namespace ConceptIsPointer {
    template <typename T>
    concept IsPointer = std::is_pointer_v<T>;

    // Function that only accepts pointer types
    void processPointer(IsPointer auto ptr) {
        std::cout << "Processing pointer: " << ptr << std::endl;
    }

    // Function that only accepts non-pointer types
    template <typename T>
        requires(!IsPointer<T>)
    void processNonPointer(T value) {
        std::cout << "Processing non-pointer: " << value << std::endl;
    }

    void test() {
        int x = 10;
        int* ptr = &x;

        processPointer(ptr);   // This will work
        processNonPointer(x);  // This will work

        // processPointer(x);      // This will cause a compilation error
        // processNonPointer(ptr); // This will cause a compilation error
    }

}  // namespace ConceptIsPointer

namespace Deferenceable {
    template <typename T>
    concept Dereferenceable = requires(T x) { *x; };

    template <typename T>
        requires Dereferenceable<T>
    void f(T& i) {
        *i = 0;
    }

    void test() {
        int i = 42;
        f(i);  // This will not compile
    }

}  // namespace Deferenceable

int main() {
    ConceptIsPointer::test();
    Deferenceable::test();
    return 0;
}
