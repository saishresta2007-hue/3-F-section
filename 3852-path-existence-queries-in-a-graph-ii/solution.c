/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int cmp(const void *a, const void *b) {
    Node *x = (Node *)a;
    Node *y = (Node *)b;
    if (x->val != y->val)
        return x->val - y->val;
    return x->idx - y->idx;
}

int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff,
                          int** queries, int queriesSize,
                          int* queriesColSize, int* returnSize) {

    Node *arr = (Node *)malloc(sizeof(Node) * n);
    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }

    qsort(arr, n, sizeof(Node), cmp);

    int *pos = (int *)malloc(sizeof(int) * n);
    int *comp = (int *)malloc(sizeof(int) * n);

    int cid = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i].val - arr[i - 1].val > maxDiff)
            cid++;
        comp[i] = cid;
        pos[arr[i].idx] = i;
    }

    int *reach = (int *)malloc(sizeof(int) * n);
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (r < i) r = i;
        while (r + 1 < n && arr[r + 1].val - arr[i].val <= maxDiff)
            r++;
        reach[i] = r;
    }

    int LOG = 20;
    int **up = (int **)malloc(LOG * sizeof(int *));
    for (int i = 0; i < LOG; i++)
        up[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        up[0][i] = reach[i];

    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {
        int u = pos[queries[i][0]];
        int v = pos[queries[i][1]];

        if (u == v) {
            ans[i] = 0;
            continue;
        }

        if (u > v) {
            int t = u;
            u = v;
            v = t;
        }

        if (comp[u] != comp[v]) {
            ans[i] = -1;
            continue;
        }

        int cur = u;
        int steps = 0;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][cur] < v) {
                cur = up[k][cur];
                steps += (1 << k);
            }
        }

        ans[i] = steps + 1;
    }

    for (int i = 0; i < LOG; i++)
        free(up[i]);
    free(up);
    free(arr);
    free(pos);
    free(comp);
    free(reach);

    *returnSize = queriesSize;
    return ans;
}
