#include <omp.h>

#include <iostream>

int main() {
    omp_set_num_threads(4);

#pragma omp parallel
    {
#pragma omp single
        {
            std::cout << "Starting task group" << std::endl;

#pragma omp taskgroup
            {
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

#pragma omp task
                {
                    std::cout << "Task 3 executed by thread "
                              << omp_get_thread_num() << std::endl;
                }
            }

            std::cout << "Task group completed" << std::endl;
        }
    }

    return 0;
}