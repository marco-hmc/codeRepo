#include <stdio.h>
#include <stdlib.h>

#define COLS 5
const int ROWS = 10;

typedef int RowArray[COLS];

int main(void) {
    RowArray *rptr = malloc(ROWS * COLS * sizeof(int));
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            rptr[row][col] = 8;
        }
    }

    return 0;
}