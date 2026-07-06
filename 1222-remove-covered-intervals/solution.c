#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;

    if (x[0] != y[0])
        return x[0] - y[0];

    return y[1] - x[1];
}

int removeCoveredIntervals(int** intervals, int intervalsSize,
                           int* intervalsColSize) {
    qsort(intervals, intervalsSize, sizeof(int *), cmp);

    int count = 0;
    int maxEnd = -1;

    for (int i = 0; i < intervalsSize; i++) {
        int end = intervals[i][1];

        if (end > maxEnd) {
            count++;
            maxEnd = end;
        }
    }

    return count;
}
