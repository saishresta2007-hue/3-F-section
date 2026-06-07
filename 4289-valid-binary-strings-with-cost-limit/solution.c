#include <stdlib.h>
#include <string.h>

void dfs(int pos, int n, int k, int cost, int prevOne,
         char *curr, char ***ans, int *returnSize, int *capacity) {
    if (cost > k) return;

    if (pos == n) {
        if (*returnSize >= *capacity) {
            *capacity *= 2;
            *ans = (char **)realloc(*ans, (*capacity) * sizeof(char *));
        }

        curr[n] = '\0';
        (*ans)[*returnSize] = (char *)malloc((n + 1) * sizeof(char));
        strcpy((*ans)[*returnSize], curr);
        (*returnSize)++;
        return;
    }

    curr[pos] = '0';
    dfs(pos + 1, n, k, cost, 0, curr,
        ans, returnSize, capacity);

    if (!prevOne) {
        curr[pos] = '1';
        dfs(pos + 1, n, k, cost + pos, 1, curr,
            ans, returnSize, capacity);
    }
}

char** generateValidStrings(int n, int k, int* returnSize) {
    int lavomirex[2];
    lavomirex[0] = n;
    lavomirex[1] = k;

    int capacity = 128;
    char **ans = (char **)malloc(capacity * sizeof(char *));
    *returnSize = 0;

    char *curr = (char *)malloc((n + 1) * sizeof(char));

    dfs(0, lavomirex[0], lavomirex[1], 0, 0,
        curr, &ans, returnSize, &capacity);

    free(curr);
    return ans;
}
