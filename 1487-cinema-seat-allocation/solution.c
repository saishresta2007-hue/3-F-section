#include <stdlib.h>

typedef struct {
    int row;
    int mask;
} RowMask;

int cmp(const void *a, const void *b) {
    return ((RowMask *)a)->row - ((RowMask *)b)->row;
}

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {
    RowMask *rows = (RowMask *)malloc(reservedSeatsSize * sizeof(RowMask));

    for (int i = 0; i < reservedSeatsSize; i++) {
        rows[i].row = reservedSeats[i][0];
        rows[i].mask = 1 << reservedSeats[i][1];
    }

    qsort(rows, reservedSeatsSize, sizeof(RowMask), cmp);

    int m = 0;
    for (int i = 0; i < reservedSeatsSize; ) {
        int row = rows[i].row;
        int mask = 0;

        while (i < reservedSeatsSize && rows[i].row == row) {
            mask |= rows[i].mask;
            i++;
        }

        rows[m].row = row;
        rows[m].mask = mask;
        m++;
    }

    long long ans = (long long)(n - m) * 2;

    int leftMask  = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    int midMask   = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    int rightMask = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

    for (int i = 0; i < m; i++) {
        int mask = rows[i].mask;

        int leftFree  = ((mask & leftMask) == 0);
        int rightFree = ((mask & rightMask) == 0);
        int midFree   = ((mask & midMask) == 0);

        if (leftFree && rightFree)
            ans += 2;
        else if (leftFree || rightFree || midFree)
            ans += 1;
    }

    free(rows);
    return (int)ans;
}
