#include <stdlib.h>

void dfs(int** graph, int* graphSize, int node, int target,
         int* path, int pathLen,
         int*** result, int* returnSize, int** returnColumnSizes) {
    
    path[pathLen++] = node;

    if (node == target) {
        (*result) = realloc(*result, ((*returnSize) + 1) * sizeof(int*));
        (*returnColumnSizes) = realloc(*returnColumnSizes,
                                       ((*returnSize) + 1) * sizeof(int));

        (*result)[*returnSize] = malloc(pathLen * sizeof(int));
        for (int i = 0; i < pathLen; i++) {
            (*result)[*returnSize][i] = path[i];
        }

        (*returnColumnSizes)[*returnSize] = pathLen;
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < graphSize[node]; i++) {
        dfs(graph, graphSize, graph[node][i], target,
            path, pathLen,
            result, returnSize, returnColumnSizes);
    }
}

int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize,
                           int* returnSize, int** returnColumnSizes) {
    
    *returnSize = 0;
    *returnColumnSizes = NULL;
    
    int** result = NULL;
    int path[15];  // n <= 15

    dfs(graph, graphColSize, 0, graphSize - 1,
        path, 0,
        &result, returnSize, returnColumnSizes);

    return result;
}
