#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *keys;
    int **vals;
    int *sizes;
    int cap;
} HashMap;

#define HASH_SIZE 200003

int hash(int x) {
    return ((long long)x * 1000003LL) % HASH_SIZE;
}

int getIndex(HashMap *map, int key) {
    int h = hash(key);
    while (map->keys[h] != -1 && map->keys[h] != key)
        h = (h + 1) % HASH_SIZE;
    return h;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize,
                          int source, int target) {
    if (source == target) return 0;

    HashMap map;
    map.cap = HASH_SIZE;
    map.keys = (int*)malloc(sizeof(int) * HASH_SIZE);
    map.vals = (int**)calloc(HASH_SIZE, sizeof(int*));
    map.sizes = (int*)calloc(HASH_SIZE, sizeof(int));

    for (int i = 0; i < HASH_SIZE; i++)
        map.keys[i] = -1;

    for (int bus = 0; bus < routesSize; bus++) {
        for (int j = 0; j < routesColSize[bus]; j++) {
            int stop = routes[bus][j];
            int idx = getIndex(&map, stop);

            if (map.keys[idx] == -1)
                map.keys[idx] = stop;

            map.vals[idx] = realloc(
                map.vals[idx],
                (map.sizes[idx] + 1) * sizeof(int)
            );
            map.vals[idx][map.sizes[idx]++] = bus;
        }
    }

    int *queue = (int*)malloc(sizeof(int) * 100005);
    int front = 0, rear = 0;

    bool *visitedBus = (bool*)calloc(routesSize, sizeof(bool));

    bool *visitedStop = (bool*)calloc(HASH_SIZE, sizeof(bool));

    queue[rear++] = source;

    int busesTaken = 0;

    while (front < rear) {
        int levelSize = rear - front;
        busesTaken++;

        for (int i = 0; i < levelSize; i++) {
            int stop = queue[front++];

            int idx = getIndex(&map, stop);
            if (map.keys[idx] == -1) continue;

            for (int k = 0; k < map.sizes[idx]; k++) {
                int bus = map.vals[idx][k];

                if (visitedBus[bus]) continue;
                visitedBus[bus] = true;

                for (int s = 0; s < routesColSize[bus]; s++) {
                    int nextStop = routes[bus][s];

                    if (nextStop == target) {
                        free(queue);
                        free(visitedBus);
                        free(visitedStop);
                        return busesTaken;
                    }

                    int nextIdx = getIndex(&map, nextStop);

                    if (!visitedStop[nextIdx]) {
                        visitedStop[nextIdx] = true;
                        queue[rear++] = nextStop;
                    }
                }
            }
        }
    }

    free(queue);
    free(visitedBus);
    free(visitedStop);

    return -1;
}
