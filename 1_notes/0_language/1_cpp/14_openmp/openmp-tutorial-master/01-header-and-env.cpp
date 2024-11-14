#include <omp.h>

#include <cassert>
#include <cstdio>

#ifndef _OPENMP
assert(false);
#endif

int main() {
    const int maxThreadSize = omp_get_max_threads();
    const int currentThreadSize = omp_get_num_threads();

#pragma omp parallel num_threads(4)
    { printf("Hello from thread %d\n", omp_get_thread_num()); }

#pragma omp parallel
    { printf("Hello from thread %d\n", omp_get_thread_num()); }

    return 0;
}
