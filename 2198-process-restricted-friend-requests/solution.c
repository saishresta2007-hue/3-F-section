#include <stdlib.h>
#include <stdbool.h>

int parent[1000];
int rankArr[1000];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);

    if (px == py) return;

    if (rankArr[px] < rankArr[py]) {
        parent[px] = py;
    } else if (rankArr[px] > rankArr[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rankArr[px]++;
    }
}

bool* friendRequests(int n,
                     int** restrictions,
                     int restrictionsSize,
                     int* restrictionsColSize,
                     int** requests,
                     int requestsSize,
                     int* requestsColSize,
                     int* returnSize) {

    *returnSize = requestsSize;
    bool* result = (bool*)malloc(sizeof(bool) * requestsSize);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }

    for (int i = 0; i < requestsSize; i++) {
        int u = requests[i][0];
        int v = requests[i][1];

        int pu = find(u);
        int pv = find(v);

        bool valid = true;

        if (pu != pv) {
            for (int j = 0; j < restrictionsSize; j++) {
                int x = restrictions[j][0];
                int y = restrictions[j][1];

                int px = find(x);
                int py = find(y);

                if ((px == pu && py == pv) ||
                    (px == pv && py == pu)) {
                    valid = false;
                    break;
                }
            }
        }

        result[i] = valid;

        if (valid)
            unite(u, v);
    }

    return result;
}
