#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    int* degree = calloc(n + 1, sizeof(int));

    for (int i = 0; i < roadsSize; i++) {
        degree[roads[i][0]]++;
        degree[roads[i][1]]++;
    }

    int** neigh = malloc((n + 1) * sizeof(int*));
    int** dist = malloc((n + 1) * sizeof(int*));

    for (int i = 1; i <= n; i++) {
        neigh[i] = malloc(degree[i] * sizeof(int));
        dist[i] = malloc(degree[i] * sizeof(int));
    }

    int* idx = calloc(n + 1, sizeof(int));

    for (int i = 0; i < roadsSize; i++) {
        int a = roads[i][0];
        int b = roads[i][1];
        int d = roads[i][2];

        neigh[a][idx[a]] = b;
        dist[a][idx[a]++] = d;

        neigh[b][idx[b]] = a;
        dist[b][idx[b]++] = d;
    }

    bool* visited = calloc(n + 1, sizeof(bool));
    int* queue = malloc((n + 1) * sizeof(int));

    int front = 0, rear = 0;
    queue[rear++] = 1;
    visited[1] = true;

    int answer = INT_MAX;

    while (front < rear) {
        int u = queue[front++];

        for (int i = 0; i < degree[u]; i++) {
            int v = neigh[u][i];
            int d = dist[u][i];

            if (d < answer)
                answer = d;

            if (!visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        free(neigh[i]);
        free(dist[i]);
    }

    free(neigh);
    free(dist);
    free(degree);
    free(idx);
    free(visited);
    free(queue);

    return answer;
}
