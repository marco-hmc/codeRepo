int *aptr = malloc(nrows * ncols * sizeof(int));
int **rptr = malloc(nrows * sizeof(int *));
for (int k = 0; k < nrows; k++) {
    rptr[k] = aptr + (k * ncols);
}