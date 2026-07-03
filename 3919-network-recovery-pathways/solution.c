#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

typedef struct {
    int to;
    int cost;
    int next;
} Edge;

static int n, m;
static ll K;
static bool *onlineNodes;
static int (*allEdges)[3];

bool can(ll x) {
    Edge *g = (Edge *)malloc(sizeof(Edge) * (m > 0 ? m : 1));
    int *head = (int *)malloc(sizeof(int) * n);
    int *indeg = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) head[i] = -1;

    int idx = 0;

    for (int i = 0; i < m; i++) {
        int u = allEdges[i][0];
        int v = allEdges[i][1];
        int c = allEdges[i][2];

        if ((ll)c < x) continue;
        if (u != 0 && !onlineNodes[u]) continue;
        if (v != n - 1 && !onlineNodes[v]) continue;

        g[idx].to = v;
        g[idx].cost = c;
        g[idx].next = head[u];
        head[u] = idx++;
        indeg[v]++;
    }

    int *q = (int *)malloc(sizeof(int) * n);
    int *topo = (int *)malloc(sizeof(int) * n);

    int front = 0, rear = 0, sz = 0;

    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0)
            q[rear++] = i;
    }

    while (front < rear) {
        int u = q[front++];
        topo[sz++] = u;

        for (int e = head[u]; e != -1; e = g[e].next) {
            int v = g[e].to;
            if (--indeg[v] == 0)
                q[rear++] = v;
        }
    }

    const ll INF = (1LL << 60);
    ll *dist = (ll *)malloc(sizeof(ll) * n);

    for (int i = 0; i < n; i++)
        dist[i] = INF;
    dist[0] = 0;

    for (int i = 0; i < sz; i++) {
        int u = topo[i];
        if (dist[u] == INF) continue;

        for (int e = head[u]; e != -1; e = g[e].next) {
            int v = g[e].to;
            ll nd = dist[u] + (ll)g[e].cost;
            if (nd < dist[v])
                dist[v] = nd;
        }
    }

    bool ok = (dist[n - 1] <= K);

    free(g);
    free(head);
    free(indeg);
    free(q);
    free(topo);
    free(dist);

    return ok;
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize,
                     bool* online, int onlineSize, long long k) {
    (void)edgesColSize;

    n = onlineSize;
    m = edgesSize;
    K = k;
    onlineNodes = online;

    allEdges = (int (*)[3])malloc(sizeof(int[3]) * (m > 0 ? m : 1));

    ll hi = 0;

    for (int i = 0; i < m; i++) {
        allEdges[i][0] = edges[i][0];
        allEdges[i][1] = edges[i][1];
        allEdges[i][2] = edges[i][2];

        if ((ll)edges[i][2] > hi)
            hi = edges[i][2];
    }

    ll lo = 0, ans = -1;

    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;

        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    free(allEdges);
    return (int)ans;
}
