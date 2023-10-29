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
    std::vector<int> v = { 1, 2, 3, 4, 5, 5, 6, 5 };
    print(v);

    std::remove(v.begin(), v.end(), 5);  // error  
    print(v);

    v.erase(std::remove(v.begin(), v.end(), 5), v.end());
    print(v);

    v.erase(std::remove_if(v.begin(), v.end(), isOdd), v.end());
    print(v);
}

// #include <iostream>
// #include <vector>
// #include <algorithm>

// void print(const std::vector<int>& vec) {
//     for (const auto& i : vec) {
//         std::cout << i << ' ';
//     }
//     std::cout << std::endl;
// }

// int main() {
//     std::vector<int> vec = { 1, 2, 3, 4, 5, 5, 6, 5 };
//     print(vec);
//     auto new_end = std::remove(vec.begin(), vec.end(), 5);
//     print(vec);
//     vec.erase(new_end, vec.end());
//     print(vec);
//     for (int i : vec) {
//         std::cout << i << " ";
//     }

//     return 0;
// }