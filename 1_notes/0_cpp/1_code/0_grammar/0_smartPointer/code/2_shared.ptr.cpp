
#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i) { (*i)++; }

int main() {
    // auto pointer = new int(10); // illegal, no direct assignment
    // std::shared_ptr construction
    auto pointer = std::make_shared<int>(10);
    auto pointer2 = pointer;  // reference count + 1
    auto pointer3 = pointer;  // reference count + 1

    foo(pointer);
    std::cout << *pointer << '\n';  // 11
    int *p = pointer.get();         // does not increase reference count

    std::cout << "pointer.use_count() = " << pointer.use_count() << '\n';
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << '\n';
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << '\n';

    pointer2.reset();
    std::cout << "reset pointer2:" << '\n';
    std::cout << "pointer.use_count() = " << pointer.use_count() << '\n';
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << '\n';
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << '\n';

    pointer3.reset();
    std::cout << "reset pointer3:" << '\n';
    std::cout << "pointer.use_count() = " << pointer.use_count() << '\n';
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << '\n';
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << '\n';
    // std::cout << *pointer << '\n'; // reference count equals 0, illegal
    // access

    // Before leaving the scope, the pointer is destructed and
    // the reference count is reduced to 0
    return 0;
}
