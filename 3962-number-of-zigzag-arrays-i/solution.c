#include <stdlib.h>

#define MOD 1000000007LL

int zigZagArrays(int n, int l, int r) {
    int m = r - l + 1;

    long long *up = (long long *)calloc(m + 2, sizeof(long long));
    long long *down = (long long *)calloc(m + 2, sizeof(long long));
    long long *newUp = (long long *)calloc(m + 2, sizeof(long long));
    long long *newDown = (long long *)calloc(m + 2, sizeof(long long));
    long long *pref = (long long *)calloc(m + 2, sizeof(long long));
    long long *suff = (long long *)calloc(m + 3, sizeof(long long));

    for (int v = 1; v <= m; v++) {
        up[v] = v - 1;
        down[v] = m - v;
    }

    for (int len = 3; len <= n; len++) {
        pref[0] = 0;
        for (int i = 1; i <= m; i++) {
            pref[i] = (pref[i - 1] + down[i]) % MOD;
        }

        suff[m + 1] = 0;
        for (int i = m; i >= 1; i--) {
            suff[i] = (suff[i + 1] + up[i]) % MOD;
        }

        for (int v = 1; v <= m; v++) {
            newUp[v] = pref[v - 1];
            newDown[v] = suff[v + 1];
        }

        long long *tmp;
        tmp = up; up = newUp; newUp = tmp;
        tmp = down; down = newDown; newDown = tmp;
    }

    long long ans = 0;
    for (int v = 1; v <= m; v++) {
        ans = (ans + up[v] + down[v]) % MOD;
    }

    free(up);
    free(down);
    free(newUp);
    free(newDown);
    free(pref);
    free(suff);

    return (int)ans;
}
