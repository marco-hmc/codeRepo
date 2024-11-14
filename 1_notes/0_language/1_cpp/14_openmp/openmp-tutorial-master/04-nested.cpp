#include <omp.h>

#include <cstdio>

int main() {
    omp_set_nested(1);
    // omp_set_nested(1);

#pragma omp parallel num_threads(2)
    {
        printf("Level 1, thread %d of %d\n", omp_get_thread_num(),
               omp_get_num_threads());
#pragma omp parallel num_threads(2)
        {
            printf("Level 2, thread %d of %d\n", omp_get_thread_num(),
                   omp_get_num_threads());
        }
    }

    return 0;
}
