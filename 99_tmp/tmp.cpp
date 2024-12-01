#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 5
#endif

#ifndef FS
#define FS 38
#endif

struct node {
    int data;
    int fibData;
    struct node* next;
};

int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

void processwork(struct node* p) {
    int n = p->data;
    p->fibData = fib(n);
}

struct node* init_list(struct node* p) {
    struct node* head = (struct node*)malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibData = 0;

    struct node* temp = NULL;
    for (int i = 0; i < N; i++) {
        temp = (struct node*)malloc(sizeof(struct node));
        p->next = temp;
        p = temp;
        p->data = FS + i + 1;
        p->fibData = i + 1;
    }
    p->next = NULL;
    return head;
}

int main(int /*argc*/, char* /*argv*/[]) {
    printf("Process linked list\n");
    printf(
        "  Each linked list node will be processed by function "
        "'processwork()'\n");
    printf(
        "  Each ll node will compute %d fibonacci numbers beginning with %d\n",
        N, FS);

    struct node* p = NULL;
    p = init_list(p);
    struct node* head = p;

    double start = omp_get_wtime();

    // 使用 OpenMP 并行处理链表节点
#pragma omp parallel
    {
#pragma omp single
        {
            while (p != NULL) {
#pragma omp task firstprivate(p)
                { processwork(p); }
                p = p->next;
            }
        }
    }

    double end = omp_get_wtime();

    p = head;
    struct node* temp = NULL;
    while (p != NULL) {
        printf("%d : %d\n", p->data, p->fibData);
        temp = p->next;
        free(p);
        p = temp;
    }

    printf("Compute Time: %f seconds\n", end - start);

    return 0;
}