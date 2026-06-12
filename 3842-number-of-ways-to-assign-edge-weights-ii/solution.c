#include <stdlib.h>
#include <string.h>

#define MOD 1000000007LL

typedef struct {
    int to, next;
} Edge;

static int LOG;

static void dfs(int u, int p, int *head, Edge *g,
                int *depth, int **up) {
    up[0][u] = p;

    for (int e = head[u]; e != -1; e = g[e].next) {
        int v = g[e].to;
        if (v == p) continue;

        depth[v] = depth[u] + 1;
        dfs(v, u, head, g, depth, up);
    }
}

static int lca(int u, int v, int *depth, int **up) {
    if (depth[u] < depth[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }

    int diff = depth[u] - depth[v];

    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            u = up[j][u];
        }
    }

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }

    return up[0][u];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize,
                       int** queries, int queriesSize, int* queriesColSize,
                       int* returnSize) {
    int n = edgesSize + 1;

    int *head = (int *)malloc((n + 1) * sizeof(int));
    memset(head, -1, (n + 1) * sizeof(int));

    Edge *g = (Edge *)malloc((2 * edgesSize) * sizeof(Edge));
    int idx = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        g[idx] = (Edge){v, head[u]};
        head[u] = idx++;

        g[idx] = (Edge){u, head[v]};
        head[v] = idx++;
    }

    LOG = 1;
    while ((1 << LOG) <= n) LOG++;

    int **up = (int **)malloc(LOG * sizeof(int *));
    for (int i = 0; i < LOG; i++) {
        up[i] = (int *)calloc(n + 1, sizeof(int));
    }

    int *depth = (int *)calloc(n + 1, sizeof(int));

    dfs(1, 0, head, g, depth, up);

    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            up[j][v] = up[j - 1][ up[j - 1][v] ];
        }
    }

    int *pow2 = (int *)malloc(n * sizeof(int));
    pow2[0] = 1;
    for (int i = 1; i < n; i++) {
        pow2[i] = (int)((2LL * pow2[i - 1]) % MOD);
    }

    int *ans = (int *)malloc(queriesSize * sizeof(int));

    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];

        int w = lca(u, v, depth, up);
        int dist = depth[u] + depth[v] - 2 * depth[w];

        if (dist == 0) {
            ans[i] = 0;
        } else {
            ans[i] = pow2[dist - 1];
        }
    }

    *returnSize = queriesSize;

    free(head);
    free(g);
    free(depth);
    free(pow2);

    for (int i = 0; i < LOG; i++) {
        free(up[i]);
    }
    free(up);

    return ans;
}
