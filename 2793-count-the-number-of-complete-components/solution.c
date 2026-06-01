#include <stdlib.h>
#include <stdbool.h>

void dfs(int node, int** graph, int* degree,
         bool* visited, int* vertices, int* degreeSum) {
    visited[node] = true;
    (*vertices)++;
    (*degreeSum) += degree[node];

    for (int i = 0; i < degree[node]; i++) {
        int next = graph[node][i];
        if (!visited[next]) {
            dfs(next, graph, degree, visited,
                vertices, degreeSum);
        }
    }
}

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
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
    int complete = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int vertices = 0;
            int degreeSum = 0;

            dfs(i, graph, degree, visited,
                &vertices, &degreeSum);

            int edgesCount = degreeSum / 2;
            int required = vertices * (vertices - 1) / 2;

            if (edgesCount == required)
                complete++;
        }
    }

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }

    free(graph);
    free(degree);
    free(idx);
    free(visited);

    return complete;
}
