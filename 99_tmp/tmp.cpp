#include <omp.h>

#include <iostream>

int main() {
    int x = 10;
    int y = 20;

#pragma omp parallel private(x) firstprivate(y)
    {
        x = 5;  // Each thread has its own private copy of x, initialized to an undefined value
        y +=
            omp_get_thread_num();  // Each thread has its own private copy of y, initialized to 20

        std::cout << "Thread " << omp_get_thread_num() << ": x = " << x
                  << ", y = " << y << std::endl;
    }

    std::cout << "Outside parallel region: x = " << x << ", y = " << y
              << std::endl;

    return 0;
}