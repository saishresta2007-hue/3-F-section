#include <stdlib.h>

int* findSmallestSetOfVertices(int n,
                               int** edges,
                               int edgesSize,
                               int* edgesColSize,
                               int* returnSize) {

    int* indegree = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        indegree[edges[i][1]]++;
    }

    int* result = (int*)malloc(n * sizeof(int));
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            result[k++] = i;
        }
    }

    free(indegree);

    *returnSize = k;
    return result;
}
