#include <stdlib.h>

int** highestPeak(int** isWater, int isWaterSize, int* isWaterColSize,
                  int* returnSize, int** returnColumnSizes) {
    int m = isWaterSize;
    int n = isWaterColSize[0];

    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));

    int** height = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
        height[i] = (int*)malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) {
            height[i][j] = -1;
        }
    }

    int maxSize = m * n;
    int* qx = (int*)malloc(maxSize * sizeof(int));
    int* qy = (int*)malloc(maxSize * sizeof(int));

    int front = 0, rear = 0;

    /* Add all water cells as BFS sources */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (isWater[i][j] == 1) {
                height[i][j] = 0;
                qx[rear] = i;
                qy[rear] = j;
                rear++;
            }
        }
    }

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (front < rear) {
        int x = qx[front];
        int y = qy[front];
        front++;

        for (int k = 0; k < 4; k++) {
            int nx = x + dirs[k][0];
            int ny = y + dirs[k][1];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                height[nx][ny] == -1) {

                height[nx][ny] = height[x][y] + 1;

                qx[rear] = nx;
                qy[rear] = ny;
                rear++;
            }
        }
    }

    free(qx);
    free(qy);

    return height;
}
