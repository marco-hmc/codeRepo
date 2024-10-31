#include <memory>

int main() {
    {
        std::unique_ptr<int> ptr = std::make_unique<int>(42);
        *ptr = 100;
    }
    {
        std::unique_ptr<int> ptr(new int(42));
        *ptr = 100;
    }
    return 0;
}