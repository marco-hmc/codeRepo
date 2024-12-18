#include <omp.h>

#include <iostream>

int main() {
    const int N = 10;
    int a[N], b[N], c[N];

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i * 2;
    }

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp taskloop
            for (int i = 0; i < N; ++i) {
                c[i] = a[i] + b[i];
                std::cout << "Task " << i << " executed by thread "
                          << omp_get_thread_num() << std::endl;
            }
        }
    }

    // Print results
    std::cout << "Result array: ";
    for (int i = 0; i < N; ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}