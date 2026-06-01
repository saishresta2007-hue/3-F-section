#define INF 1000000000000LL

typedef struct {
    int n;
    long long dist[101][101];
} Graph;

Graph* graphCreate(int n, int** edges, int edgesSize, int* edgesColSize) {
    Graph* obj = (Graph*)malloc(sizeof(Graph));
    obj->n = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                obj->dist[i][j] = 0;
            else
                obj->dist[i][j] = INF;
        }
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        obj->dist[u][v] = w;
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (obj->dist[i][k] == INF ||
                    obj->dist[k][j] == INF)
                    continue;

                long long nd = obj->dist[i][k] + obj->dist[k][j];

                if (nd < obj->dist[i][j])
                    obj->dist[i][j] = nd;
            }
        }
    }

    return obj;
}

void graphAddEdge(Graph* obj, int* edge, int edgeSize) {
    int u = edge[0];
    int v = edge[1];
    long long w = edge[2];

    if (w >= obj->dist[u][v])
        return;

    obj->dist[u][v] = w;

    int n = obj->n;

    for (int i = 0; i < n; i++) {
        if (obj->dist[i][u] == INF) continue;

        for (int j = 0; j < n; j++) {
            if (obj->dist[v][j] == INF) continue;

            long long nd = obj->dist[i][u] + w + obj->dist[v][j];

            if (nd < obj->dist[i][j])
                obj->dist[i][j] = nd;
        }
    }
}

int graphShortestPath(Graph* obj, int node1, int node2) {
    return obj->dist[node1][node2] == INF
           ? -1
           : (int)obj->dist[node1][node2];
}

void graphFree(Graph* obj) {
    free(obj);
}

/**
 * Your Graph struct will be instantiated and called as such:
 * Graph* obj = graphCreate(n, edges, edgesSize, edgesColSize);
 * graphAddEdge(obj, edge, edgeSize);
 *
 * int param_2 = graphShortestPath(obj, node1, node2);
 *
 * graphFree(obj);
 */
