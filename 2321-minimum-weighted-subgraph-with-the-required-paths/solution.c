#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

typedef struct Edge {
    int to;
    int wt;
    struct Edge *next;
} Edge;

typedef struct {
    ll dist;
    int node;
} HeapNode;

static void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

typedef struct {
    HeapNode *arr;
    int size;
} MinHeap;

static void push(MinHeap *h, ll dist, int node) {
    int i = ++h->size;
    h->arr[i].dist = dist;
    h->arr[i].node = node;

    while (i > 1 && h->arr[i].dist < h->arr[i / 2].dist) {
        swap(&h->arr[i], &h->arr[i / 2]);
        i /= 2;
    }
}

static HeapNode pop(MinHeap *h) {
    HeapNode res = h->arr[1];
    h->arr[1] = h->arr[h->size--];

    int i = 1;

    while (1) {
        int smallest = i;
        int l = 2 * i;
        int r = 2 * i + 1;

        if (l <= h->size && h->arr[l].dist < h->arr[smallest].dist)
            smallest = l;

        if (r <= h->size && h->arr[r].dist < h->arr[smallest].dist)
            smallest = r;

        if (smallest == i)
            break;

        swap(&h->arr[i], &h->arr[smallest]);
        i = smallest;
    }

    return res;
}

static void dijkstra(int n, Edge **graph, int src, ll *dist) {
    const ll INF = LLONG_MAX / 4;

    for (int i = 0; i < n; i++)
        dist[i] = INF;

    MinHeap heap;
    heap.arr = (HeapNode *)malloc(sizeof(HeapNode) * (200005));
    heap.size = 0;

    dist[src] = 0;
    push(&heap, 0, src);

    while (heap.size) {
        HeapNode cur = pop(&heap);

        ll d = cur.dist;
        int u = cur.node;

        if (d != dist[u])
            continue;

        for (Edge *e = graph[u]; e; e = e->next) {
            int v = e->to;
            ll nd = d + e->wt;

            if (nd < dist[v]) {
                dist[v] = nd;
                push(&heap, nd, v);
            }
        }
    }

    free(heap.arr);
}

long long minimumWeight(int n, int** edges, int edgesSize,
                        int* edgesColSize, int src1,
                        int src2, int dest) {
    Edge **g = (Edge **)calloc(n, sizeof(Edge *));
    Edge **rg = (Edge **)calloc(n, sizeof(Edge *));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        Edge *e1 = (Edge *)malloc(sizeof(Edge));
        e1->to = v;
        e1->wt = w;
        e1->next = g[u];
        g[u] = e1;

        Edge *e2 = (Edge *)malloc(sizeof(Edge));
        e2->to = u;
        e2->wt = w;
        e2->next = rg[v];
        rg[v] = e2;
    }

    ll *d1 = (ll *)malloc(sizeof(ll) * n);
    ll *d2 = (ll *)malloc(sizeof(ll) * n);
    ll *d3 = (ll *)malloc(sizeof(ll) * n);

    dijkstra(n, g, src1, d1);
    dijkstra(n, g, src2, d2);
    dijkstra(n, rg, dest, d3);

    const ll INF = LLONG_MAX / 4;
    ll ans = INF;

    for (int i = 0; i < n; i++) {
        if (d1[i] == INF || d2[i] == INF || d3[i] == INF)
            continue;

        ll total = d1[i] + d2[i] + d3[i];
        if (total < ans)
            ans = total;
    }

    free(d1);
    free(d2);
    free(d3);

    for (int i = 0; i < n; i++) {
        Edge *p = g[i];
        while (p) {
            Edge *t = p;
            p = p->next;
            free(t);
        }

        p = rg[i];
        while (p) {
            Edge *t = p;
            p = p->next;
            free(t);
        }
    }

    free(g);
    free(rg);

    return ans == INF ? -1 : ans;
}
