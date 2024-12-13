#include <omp.h>

#include <cstdio>

int main() {
#pragma omp parallel
    {
#pragma omp single
        {
            // 仅由一个线程执行的代码块
            printf("This is executed by a single thread.\n");
        }
#pragma omp barrier
#pragma omp critical
        {
            // 由每个线程执行的代码块
            printf("This is executed by thread %d\n", omp_get_thread_num());
        }
    }

    return 0;
}