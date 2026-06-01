#include <stdlib.h>
#include <string.h>

#define RED 0
#define BLUE 1

typedef struct {
    int node;
    int color;
    int dist;
} State;

int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize,
                              int* redEdgesColSize, int** blueEdges,
                              int blueEdgesSize, int* blueEdgesColSize,
                              int* returnSize) {
    
    int red[100][100] = {0};
    int blue[100][100] = {0};

    for (int i = 0; i < redEdgesSize; i++) {
        red[redEdges[i][0]][redEdges[i][1]] = 1;
    }

    for (int i = 0; i < blueEdgesSize; i++) {
        blue[blueEdges[i][0]][blueEdges[i][1]] = 1;
    }

    int visited[100][2];
    memset(visited, 0, sizeof(visited));

    int *ans = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        ans[i] = -1;
    }

    State queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = (State){0, RED, 0};
    queue[rear++] = (State){0, BLUE, 0};

    visited[0][RED] = 1;
    visited[0][BLUE] = 1;

    ans[0] = 0;

    while (front < rear) {
        State cur = queue[front++];

        if (cur.color == RED) {
            for (int nei = 0; nei < n; nei++) {
                if (blue[cur.node][nei] && !visited[nei][BLUE]) {
                    visited[nei][BLUE] = 1;

                    if (ans[nei] == -1 || ans[nei] > cur.dist + 1)
                        ans[nei] = cur.dist + 1;

                    queue[rear++] = (State){nei, BLUE, cur.dist + 1};
                }
            }
        } else {
            for (int nei = 0; nei < n; nei++) {
                if (red[cur.node][nei] && !visited[nei][RED]) {
                    visited[nei][RED] = 1;

                    if (ans[nei] == -1 || ans[nei] > cur.dist + 1)
                        ans[nei] = cur.dist + 1;

                    queue[rear++] = (State){nei, RED, cur.dist + 1};
                }
            }
        }
    }

    *returnSize = n;
    return ans;
}
