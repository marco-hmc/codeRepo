#include <omp.h>

#include <iostream>

int main() {
#pragma omp parallel
    {
#pragma omp single
        {
            std::cout << "Starting tasks..." << std::endl;

#pragma omp task
            {
                std::cout << "Task 1 executed by thread "
                          << omp_get_thread_num() << std::endl;
            }

#pragma omp task
            {
                std::cout << "Task 2 executed by thread "
                          << omp_get_thread_num() << std::endl;
            }

#pragma omp taskwait
            std::cout << "All tasks completed." << std::endl;
        }
    }

    return 0;
}