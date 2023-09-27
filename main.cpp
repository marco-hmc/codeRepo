#include <cassert>
#include <cstring>
#include <string>
namespace jc {

    template <typename T>
    T max(T a, T b) {
        return a < b ? b : a;
    }

    template <typename T>
    T* max(T* a, T* b) {
        return *a < *b ? b : a;
    }

    const char* max(const char* a, const char* b) {
        return std::strcmp(a, b) < 0 ? b : a;
    }

}  // namespace jc

int main() {
    int a = 1;
    int b = 3;
    assert(jc::max(a, b) == b);
    assert(jc::max(&a, &b) == &b);

    std::string s1 = "down";
    std::string s2 = "demo";
    assert(jc::max(s1, s2) == "down");
    assert(std::strcmp(jc::max("down", "demo"), "down") == 0);
}