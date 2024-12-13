#include <iostream>

int main() {
    const int size = 5;
    int a[size];

#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }

    for (int i : a) {
        std::cout << i << std::endl;
    }
    return 0;
}
