#include <limits.h>

int findTheCity(int n, int** edges, int edgesSize, int* edgesColSize,
                int distanceThreshold) {
    int dist[100][100];

    // Initialize distances
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX / 2;
        }
    }

    // Add edges
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        dist[u][v] = w;
        dist[v][u] = w;
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int answer = -1;
    int minReachable = INT_MAX;

    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold)
                count++;
        }

        if (count <= minReachable) {
            minReachable = count;
            answer = i;  // larger index chosen on tie
        }
    }

    return answer;
}
