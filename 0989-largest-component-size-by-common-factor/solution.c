#include <stdlib.h>

int parent[20000];
int size[20000];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    int pa = find(a);
    int pb = find(b);

    if (pa == pb) return;

    if (size[pa] < size[pb]) {
        int temp = pa;
        pa = pb;
        pb = temp;
    }

    parent[pb] = pa;
    size[pa] += size[pb];
}

int largestComponentSize(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int factorOwner[100001];
    for (int i = 0; i <= 100000; i++)
        factorOwner[i] = -1;

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];

        for (int f = 2; f * f <= x; f++) {
            if (x % f == 0) {

                if (factorOwner[f] == -1)
                    factorOwner[f] = i;
                else
                    unite(i, factorOwner[f]);

                while (x % f == 0)
                    x /= f;
            }
        }

        if (x > 1) {
            if (factorOwner[x] == -1)
                factorOwner[x] = i;
            else
                unite(i, factorOwner[x]);
        }
    }

    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        if (find(i) == i && size[i] > ans)
            ans = size[i];
    }

    return ans;
}
