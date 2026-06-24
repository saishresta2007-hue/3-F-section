#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL

typedef struct {
    int sz;
    long long a[150][150];
} Matrix;

static void matMul(Matrix *A, Matrix *B, Matrix *C) {
    int n = A->sz;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C->a[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            long long x = A->a[i][k];
            if (!x) continue;

            for (int j = 0; j < n; j++) {
                if (B->a[k][j]) {
                    C->a[i][j] =
                        (C->a[i][j] + x * B->a[k][j]) % MOD;
                }
            }
        }
    }
    C->sz = n;
}

static void matPow(Matrix *base, long long exp, Matrix *res) {
    int n = base->sz;

    res->sz = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res->a[i][j] = (i == j);
        }
    }

    Matrix cur = *base;
    Matrix tmp;

    while (exp > 0) {
        if (exp & 1LL) {
            matMul(res, &cur, &tmp);
            *res = tmp;
        }

        matMul(&cur, &cur, &tmp);
        cur = tmp;

        exp >>= 1LL;
    }
}

int zigZagArrays(int n, int l, int r) {
    int m = r - l + 1;
    int sz = 2 * m;

    Matrix T;
    T.sz = sz;

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            T.a[i][j] = 0;
        }
    }

    /* U(v) <- D(u), u < v */
    for (int v = 1; v <= m; v++) {
        int row = v - 1;

        for (int u = 1; u < v; u++) {
            int col = m + (u - 1);
            T.a[row][col] = 1;
        }
    }

    /* D(v) <- U(u), u > v */
    for (int v = 1; v <= m; v++) {
        int row = m + (v - 1);

        for (int u = v + 1; u <= m; u++) {
            int col = u - 1;
            T.a[row][col] = 1;
        }
    }

    long long vec[150] = {0};

    /* length = 2 */
    for (int v = 1; v <= m; v++) {
        vec[v - 1] = v - 1;       /* U */
        vec[m + v - 1] = m - v;   /* D */
    }

    Matrix P;
    matPow(&T, n - 2, &P);

    long long ans = 0;

    for (int i = 0; i < sz; i++) {
        long long cur = 0;

        for (int j = 0; j < sz; j++) {
            cur = (cur + P.a[i][j] * vec[j]) % MOD;
        }

        ans = (ans + cur) % MOD;
    }

    return (int)ans;
}
