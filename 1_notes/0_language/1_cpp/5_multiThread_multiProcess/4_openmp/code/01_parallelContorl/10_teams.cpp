#include <omp.h>

#include <iostream>

int main() {
    const int N = 10;
    int a[N];
    int b[N];
    int c[N];

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i * 2;
    }

// Parallel region with teams
#pragma omp target teams distribute parallel for
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Print results
    for (int i = 0; i < N; ++i) {
        std::cout << "c[" << i << "] = " << c[i] << std::endl;
    }

    return 0;
}