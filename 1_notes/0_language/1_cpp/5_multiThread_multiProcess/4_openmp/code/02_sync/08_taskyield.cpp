#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 0; i < 10; i++) {
#pragma omp task
                {
                    printf("Task %d executed by thread %d\n", i,
                           omp_get_thread_num());
#pragma omp taskyield
                }
            }
        }
    }
    return 0;
}