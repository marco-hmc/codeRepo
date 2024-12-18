#include <omp.h>

#include <iostream>

int main() {
    int x = 0, y = 0;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                x = 1;
                std::cout << "Task 1 executed by thread "
                          << omp_get_thread_num() << std::endl;
            }

#pragma omp task
            {
                y = 2;
                std::cout << "Task 2 executed by thread "
                          << omp_get_thread_num() << std::endl;
            }

#pragma omp taskwait

            std::cout << "Both tasks completed. x = " << x << ", y = " << y
                      << std::endl;
        }
    }

    return 0;
}