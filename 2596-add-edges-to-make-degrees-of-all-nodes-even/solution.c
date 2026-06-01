#include <stdbool.h>
#include <stdlib.h>

#define SIZE 400009

typedef struct {
    long long key;
    bool used;
} Entry;

Entry table[SIZE];

long long makeKey(int u, int v) {
    if (u > v) {
        int t = u;
        u = v;
        v = t;
    }
    return (long long)u * 100001LL + v;
}

void insertEdge(int u, int v) {
    long long key = makeKey(u, v);
    int h = key % SIZE;

    while (table[h].used && table[h].key != key)
        h = (h + 1) % SIZE;

    table[h].used = true;
    table[h].key = key;
}

bool hasEdge(int u, int v) {
    long long key = makeKey(u, v);
    int h = key % SIZE;

    while (table[h].used) {
        if (table[h].key == key)
            return true;
        h = (h + 1) % SIZE;
    }
    return false;
}

bool isPossible(int n, int** edges, int edgesSize, int* edgesColSize) {
    int *deg = calloc(n + 1, sizeof(int));

    for (int i = 0; i < SIZE; i++)
        table[i].used = false;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        deg[u]++;
        deg[v]++;

        insertEdge(u, v);
    }

    int odd[4];
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1) {
            if (cnt < 4)
                odd[cnt] = i;
            cnt++;
        }
    }

    free(deg);

    if (cnt == 0)
        return true;

    if (cnt > 4)
        return false;

    if (cnt == 2) {
        int a = odd[0];
        int b = odd[1];

        if (!hasEdge(a, b))
            return true;

        for (int x = 1; x <= n; x++) {
            if (x == a || x == b)
                continue;

            if (!hasEdge(a, x) && !hasEdge(b, x))
                return true;
        }

        return false;
    }

    int a = odd[0];
    int b = odd[1];
    int c = odd[2];
    int d = odd[3];

    if (!hasEdge(a, b) && !hasEdge(c, d))
        return true;

    if (!hasEdge(a, c) && !hasEdge(b, d))
        return true;

    if (!hasEdge(a, d) && !hasEdge(b, c))
        return true;

    return false;
}
