#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;
    return x[0] - y[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {

    qsort(intervals, intervalsSize, sizeof(int *), compare);

    int **result = (int **)malloc(intervalsSize * sizeof(int *));
    *returnColumnSizes = (int *)malloc(intervalsSize * sizeof(int));

    int idx = 0;

    result[idx] = (int *)malloc(2 * sizeof(int));
    result[idx][0] = intervals[0][0];
    result[idx][1] = intervals[0][1];

    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= result[idx][1]) {
            // Overlap: extend the current interval
            if (intervals[i][1] > result[idx][1])
                result[idx][1] = intervals[i][1];
        } else {
            // No overlap: start a new interval
            idx++;
            result[idx] = (int *)malloc(2 * sizeof(int));
            result[idx][0] = intervals[i][0];
            result[idx][1] = intervals[i][1];
        }
    }

    *returnSize = idx + 1;

    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    return result;
}
