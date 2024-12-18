#include <omp.h>

#include <iostream>

int main() {
    const int N = 100;
    int a[N], b[N], c[N];

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = 2 * i;
    }

// Parallel region with distribute construct
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp distribute
            for (int i = 0; i < N; ++i) {
                c[i] = a[i] + b[i];
            }
        }
    }

    // Print result
    for (int i = 0; i < N; ++i) {
        std::cout << "c[" << i << "] = " << c[i] << std::endl;
    }

    return 0;
}