#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};

    auto it1 = vec.begin();
    auto it2 = vec.end();
    auto dist = std::distance(it1, it2);  // 5
    std::cout << "Distance between begin and end: " << dist << std::endl;

    // 计算部分距离
    auto it3 = vec.begin() + 2;
    auto partial_dist = std::distance(it1, it3);

    std::cout << "Distance between begin and third element: " << partial_dist
              << std::endl;

    return 0;
}