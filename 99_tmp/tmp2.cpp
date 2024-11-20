#include <iostream>

int main() {
    int arr1[10];
    // int arr2[10];
    std::fill(std::begin(arr1), std::end(arr1), 1);
    // std::fill(std::begin(arr2), std::end(arr2), 2);

    // arr1[15] = 5;
    std::cout << "Value: " << arr1[15] << std::endl;

    // for (int i = 0; i < 10; ++i) {
    //     std::cout << arr2[i] << " ";
    // }
    std::cout << std::endl;
    return 0;
}