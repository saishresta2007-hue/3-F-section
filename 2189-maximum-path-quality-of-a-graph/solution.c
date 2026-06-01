typedef struct Edge {
    int to;
    int time;
    struct Edge *next;
} Edge;

int ans;

void dfs(int node,
         int timeUsed,
         int score,
         int maxTime,
         int *values,
         Edge **graph,
         int *vis)
{
    if (node == 0 && score > ans)
        ans = score;

    for (Edge *e = graph[node]; e; e = e->next) {
        int nxt = e->to;
        int t = e->time;

        if (timeUsed + t > maxTime)
            continue;

        int add = 0;

        if (vis[nxt] == 0)
            add = values[nxt];

        vis[nxt]++;

        dfs(nxt,
            timeUsed + t,
            score + add,
            maxTime,
            values,
            graph,
            vis);

        vis[nxt]--;
    }
}

int maximalPathQuality(int* values,
                       int valuesSize,
                       int** edges,
                       int edgesSize,
                       int* edgesColSize,
                       int maxTime)
{
    Edge **graph = calloc(valuesSize, sizeof(Edge*));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int t = edges[i][2];

        Edge *a = malloc(sizeof(Edge));
        a->to = v;
        a->time = t;
        a->next = graph[u];
        graph[u] = a;

        Edge *b = malloc(sizeof(Edge));
        b->to = u;
        b->time = t;
        b->next = graph[v];
        graph[v] = b;
    }

    int *vis = calloc(valuesSize, sizeof(int));

    ans = values[0];

    vis[0] = 1;

    dfs(0,
        0,
        values[0],
        maxTime,
        values,
        graph,
        vis);

    return ans;
}
