#include <stdio.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll cnt;
    ll wav;
} Node;

char s[20];
Node dp[20][3][11][11];
char vis[20][3][11][11];

Node dfs(int pos, int tight, int state, int a, int b) {
    int len = strlen(s);

    if (pos == len) {
        Node res = {1, 0};
        return res;
    }

    if (!tight && vis[pos][state][a][b]) {
        return dp[pos][state][a][b];
    }

    int lim = tight ? (s[pos] - '0') : 9;
    Node res = {0, 0};

    for (int d = 0; d <= lim; d++) {
        int ntight = tight && (d == lim);

        if (state == 0) {
            if (d == 0) {
                Node nxt = dfs(pos + 1, ntight, 0, 10, 10);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                Node nxt = dfs(pos + 1, ntight, 1, 10, d);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            }
        }
        else if (state == 1) {
            Node nxt = dfs(pos + 1, ntight, 2, b, d);
            res.cnt += nxt.cnt;
            res.wav += nxt.wav;
        }
        else {
            int add = ((b > a && b > d) || (b < a && b < d)) ? 1 : 0;

            Node nxt = dfs(pos + 1, ntight, 2, b, d);

            res.cnt += nxt.cnt;
            res.wav += nxt.wav + (ll)add * nxt.cnt;
        }
    }

    if (!tight) {
        vis[pos][state][a][b] = 1;
        dp[pos][state][a][b] = res;
    }

    return res;
}

ll solve(ll n) {
    if (n <= 0) return 0;

    sprintf(s, "%lld", n);
    memset(vis, 0, sizeof(vis));

    return dfs(0, 1, 0, 10, 10).wav;
}

long long totalWaviness(long long num1, long long num2) {
    return solve(num2) - solve(num1 - 1);
}

/* Example usage
int main() {
    long long num1 = 120, num2 = 130;
    printf("%lld\n", totalWaviness(num1, num2)); // 3
    return 0;
}
*/
