#include <stdbool.h>
#include <stdlib.h>

void dfs(int node, int destination, int** graph, int* size,
         bool* visited, bool* found) {
    if (*found) return;

    visited[node] = true;

    if (node == destination) {
        *found = true;
        return;
    }

    for (int i = 0; i < size[node]; i++) {
        int next = graph[node][i];
        if (!visited[next]) {
            dfs(next, destination, graph, size, visited, found);
        }
    }
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize,
               int source, int destination) {
    if (source == destination) return true;

    int* degree = calloc(n, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        degree[edges[i][0]]++;
        degree[edges[i][1]]++;
    }

    int** graph = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        graph[i] = malloc(degree[i] * sizeof(int));
    }

    int* idx = calloc(n, sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        graph[u][idx[u]++] = v;
        graph[v][idx[v]++] = u;
    }

    bool* visited = calloc(n, sizeof(bool));
    bool found = false;

    dfs(source, destination, graph, degree, visited, &found);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(degree);
    free(idx);
    free(visited);

    return found;
}
