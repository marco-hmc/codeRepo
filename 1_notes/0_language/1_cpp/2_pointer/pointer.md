```c++
/*
             tab + 0        tab + 1
   Address  0x7ffc5c78b530  0x7ffc5c78b538  0x7ffc5c78b530  0x7ffc5c78b534  0x7ffc5c78b538  0x7ffc5c78b53c
     Value  0x7ffc5c78b530  0x7ffc5c78b538  1  				2  				3  				4
                 [0]           [1]         [0][0]          [0][1]          [1][0]          [1][1]

tab = table[0] = table[0][0] = 0x7ffc5c78b530
*tab = 0x7ffc5c78b530
**tab = table[0][0] = 1

tab + 1 = table[1] = table[1][0] = 0x7ffc5c78b538
*(tab + 1) = 0x7ffc5c78b538
**(tab + 1) = table[1][0] = 3

*/

#include <stdio.h>

int main() {
    int tab[2][2] = {{1, 2}, {3, 4}};

    // 输出*tab, **tab, *(tab + 1), **(tab + 1)的值
    printf("tab = %p\n", tab);
    printf("*tab = %p\n", *tab);
    printf("**tab = %d\n", **tab);

    printf("tab + 1 = %p\n", tab + 1);
    printf("*(tab + 1) = %p\n", *(tab + 1));
    printf("***(tab + 1) = %d\n", **(tab + 1));
    return 0;
}
```

```c++
struct Foo{
    int a;
    int b;
};

Foo *(*bar) = nullptr;
Foo **bar = nullptr;
```

```c++
void bubble(int a[], int N) {
    int i, j, t;
    for (i = N - 1; i >= 0; i--) {
        for (j = 1; j <= i; j++) {
            if (a[j - 1] > a[j]) {
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }
        }
    }
}

```

```c++
void func(int a[][3], int rows) {
    // 使用 a[i][j] 访问数组元素
}
int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
func(arr, 2);
```

```plaintext
Stack:
|----------------|
| int **rowptr   | -> Stack:
|----------------|    |---------------------------              |
| int row        |    | int *[nrows]                            | -> |-----------------------           |
| main frame     |    |---------------------------              |    | int[ncols] (rowptr[0])           |
|                |    | int *[0] (rowptr[0])                    |    | int[ncols] (rowptr[1])           |
|                |    | int *[1] (rowptr[1])                    |    | ...                              |
|                |    |...                                      |    | ...                              |
|                |    | int *[nrows - 1] (rowptr[nrows - 1])    |    | int[ncols] (rowptr[nrows - 1])   |
|                |    |---------------------------              |    |-----------------------           |
```

```c++
#include <stdio.h>
#include <stdlib.h>

#define COLS 5

typedef int RowArray[COLS];

int main(void) {
    int nrows = 10;
    RowArray *rptr;
    rptr = malloc(nrows * COLS * sizeof(int));
    for (int row = 0; row < nrows; row++) {
        for (int col = 0; col < COLS; col++) {
            rptr[row][col] = 17;
        }
    }

    return 0;
}

```

```c++
    int *aptr = malloc(nrows * ncols * sizeof(int));
    int **rptr = malloc(nrows * sizeof(int *));
    for (int k = 0; k < nrows; k++) {
        rptr[k] = aptr + (k * ncols);
    }
```

```c++
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int X_DIM = 16;
const int Y_DIM = 5;
const int Z_DIM = 3;

int main(void) {
    char *space = malloc(X_DIM * Y_DIM * Z_DIM * sizeof(char));
    char ***Arr3D = malloc(Z_DIM * sizeof(char **));
    for (int z = 0; z < Z_DIM; z++) {
        Arr3D[z] = malloc(Y_DIM * sizeof(char *));
        for (int y = 0; y < Y_DIM; y++) {
            Arr3D[z][y] = space + (z * (X_DIM * Y_DIM) + y * X_DIM);
        }
    }

    ptrdiff_t diff;
    for (int z = 0; z < Z_DIM; z++) {
        printf("Location of array %d is %p\n", z, *Arr3D[z]);
        for (int y = 0; y < Y_DIM; y++) {
            printf("  Array %d and Row %d starts at %p", z, y, Arr3D[z][y]);
            diff = Arr3D[z][y] - space;
            printf("    diff = %ld  ", diff);
            printf(" z = %d  y = %d\n", z, y);
        }
    }
    return 0;
}
```