#include <stdlib.h>

void backtrack(int start, int n, int k,
               int *curr, int currSize,
               int **result, int *returnSize,
               int *returnColumnSizes) {

    if (currSize == k) {
        result[*returnSize] = (int *)malloc(k * sizeof(int));

        for (int i = 0; i < k; i++) {
            result[*returnSize][i] = curr[i];
        }

        returnColumnSizes[*returnSize] = k;
        (*returnSize)++;
        return;
    }

    for (int i = start; i <= n; i++) {
        curr[currSize] = i;
        backtrack(i + 1, n, k,
                  curr, currSize + 1,
                  result, returnSize,
                  returnColumnSizes);
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int maxCombinations = 200000;

    int **result = (int **)malloc(maxCombinations * sizeof(int *));
    *returnColumnSizes = (int *)malloc(maxCombinations * sizeof(int));

    *returnSize = 0;

    int *curr = (int *)malloc(k * sizeof(int));

    backtrack(1, n, k, curr, 0,
              result, returnSize,
              *returnColumnSizes);

    free(curr);

    return result;
}
