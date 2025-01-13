#include <cassert>
#include <iostream>

namespace arrPtr {
    void example1() {
        int actualArray[2][3] = {{1, 2, 3}, {4, 5, 6}};
        static_assert(sizeof(actualArray) == 24);  // 24

        int(*arr)[3] = actualArray;
        static_assert(sizeof(arr) == 8);     // 8
        static_assert(sizeof(*arr) == 12);   // 12
        assert(*arr + 1 == actualArray[1]);  // true

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

}  // namespace arrPtr

namespace decayToPrt {
    void func(int a[][3], int rows) {
        static_assert(sizeof(a) == 8);    // 8
        static_assert(sizeof(*a) == 12);  // 12

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void example1() {
        int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
        func(arr, 2);
    }

}  // namespace decayToPrt

int main() { return 0; }