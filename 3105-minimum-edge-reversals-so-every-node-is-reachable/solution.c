#include <stdlib.h>

typedef struct {
    int to;
    int cost;
} Edge;

typedef struct {
    Edge *e;
    int size;
    int cap;
} Vec;

static void addEdge(Vec *g, int u, int v, int cost) {
    if (g[u].size == g[u].cap) {
        g[u].cap = g[u].cap ? g[u].cap * 2 : 4;
        g[u].e = realloc(g[u].e, g[u].cap * sizeof(Edge));
    }
    g[u].e[g[u].size++] = (Edge){v, cost};
}

static int dfsCount(int u, int parent, Vec *g) {
    int res = 0;

    for (int i = 0; i < g[u].size; i++) {
        int v = g[u].e[i].to;
        int cost = g[u].e[i].cost;

        if (v == parent) continue;

        res += cost;
        res += dfsCount(v, u, g);
    }

    return res;
}

static void dfsReroot(int u, int parent, Vec *g, int *ans) {
    for (int i = 0; i < g[u].size; i++) {
        int v = g[u].e[i].to;
        int cost = g[u].e[i].cost;

        if (v == parent) continue;

        if (cost == 0)
            ans[v] = ans[u] + 1;
        else
            ans[v] = ans[u] - 1;

        dfsReroot(v, u, g, ans);
    }
}

int* minEdgeReversals(int n, int** edges, int edgesSize,
                      int* edgesColSize, int* returnSize) {
    Vec *g = calloc(n, sizeof(Vec));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        addEdge(g, u, v, 0); // original direction
        addEdge(g, v, u, 1); // reverse direction
    }

    int *ans = malloc(n * sizeof(int));

    ans[0] = dfsCount(0, -1, g);

    dfsReroot(0, -1, g, ans);

    for (int i = 0; i < n; i++) {
        free(g[i].e);
    }
    free(g);

    *returnSize = n;
    return ans;
}
