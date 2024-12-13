#include <omp.h>

#include <iostream>

int main() {
    //   #pragma omp parallel sections num_threads(4)
    omp_set_num_threads(4);

// 并行区域，包含多个并行执行的代码块
#pragma omp parallel sections
    {
#pragma omp section
        {
            // 第一个并行执行的代码块
            int thread_id = omp_get_thread_num();
            std::cout << "Section 1 executed by thread " << thread_id
                      << std::endl;
        }

#pragma omp section
        {
            // 第二个并行执行的代码块
            int thread_id = omp_get_thread_num();
            std::cout << "Section 2 executed by thread " << thread_id
                      << std::endl;
        }

#pragma omp section
        {
            // 第三个并行执行的代码块
            int thread_id = omp_get_thread_num();
            std::cout << "Section 3 executed by thread " << thread_id
                      << std::endl;
        }

#pragma omp section
        {
            // 第四个并行执行的代码块
            int thread_id = omp_get_thread_num();
            std::cout << "Section 4 executed by thread " << thread_id
                      << std::endl;
        }
    }

    return 0;
}