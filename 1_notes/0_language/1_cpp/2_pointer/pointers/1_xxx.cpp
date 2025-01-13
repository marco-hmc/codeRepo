#include <cassert>
#include <iostream>

namespace differenceBetweenPntAndArray {
    void example1() {
        int myArray[5] = {1, 2, 3, 4, 5};
        static_assert(sizeof(myArray) == 20);
        // myArray = nullptr;  // error: array type 'int [5]' is not assignable

        int *p = myArray;
        static_assert(sizeof(p) == 8);
        p = nullptr;

        assert(myArray[1] == *myArray + 1);    // true
        assert(myArray[1] == *(myArray + 1));  // true
    }
}  // namespace differenceBetweenPntAndArray

namespace arrDecayToPtr {
    void method(int *arr, int size) {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void method2(int arr[], int size) {
        int arrNoDecay[5] = {1, 2, 3, 4, 5};
        assert(sizeof(arr) == 8 && sizeof(arrNoDecay) == 20);
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void example1() {
        int myArray[5] = {1, 2, 3, 4, 5};
        method(myArray, 5);
        method2(myArray, 5);
    }

}  // namespace arrDecayToPtr

int main() {
    differenceBetweenPntAndArray::example1();
    arrDecayToPtr::example1();
    return 0;
}