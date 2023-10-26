#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

bool isOdd(int i) { return i & 1; }

void print(const std::vector<int>& vec) {
    for (const auto& i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    print(v);

    std::remove(v.begin(), v.end(), 5);  // error
    print(v);

    v.erase(std::remove(v.begin(), v.end(), 5), v.end());
    print(v);

    v.erase(std::remove_if(v.begin(), v.end(), isOdd), v.end());
    print(v);
}