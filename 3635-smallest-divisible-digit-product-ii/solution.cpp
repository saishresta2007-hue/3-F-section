class Solution {
public:
    string smallestNumber(string num, long long t) {
        // Required powers of 2, 3, 5, 7.
        int r2 = 0, r3 = 0, r5 = 0, r7 = 0;

        while (t % 2 == 0) {
            r2++;
            t /= 2;
        }

        while (t % 3 == 0) {
            r3++;
            t /= 3;
        }

        while (t % 5 == 0) {
            r5++;
            t /= 5;
        }

        while (t % 7 == 0) {
            r7++;
            t /= 7;
        }

        // Any other prime factor cannot be produced by digits 1..9.
        if (t != 1)
            return "-1";

        /*
            Factor contribution of each digit:
            
            1 -> 0,0,0,0
            2 -> 1,0,0,0
            3 -> 0,1,0,0
            4 -> 2,0,0,0
            5 -> 0,0,1,0
            6 -> 1,1,0,0
            7 -> 0,0,0,1
            8 -> 3,0,0,0
            9 -> 0,2,0,0
        */
        int f[10][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {1,0,0,0},
            {0,1,0,0},
            {2,0,0,0},
            {0,0,1,0},
            {1,1,0,0},
            {0,0,0,1},
            {3,0,0,0},
            {0,2,0,0}
        };

        int A = r2 + 1;
        int B = r3 + 1;
        int C = r5 + 1;
        int D = r7 + 1;

        int sD = 1;
        int sC = D;
        int sB = C * D;
        int sA = B * C * D;

        auto id = [&](int a, int b, int c, int d) {
            return a * sA + b * sB + c * sC + d;
        };

        const int INF = 1e9;
        int states = A * B * C * D;

        /*
            dp[a][b][c][d] =
            minimum number of digits needed to provide
            at least a factors of 2,
            b factors of 3,
            c factors of 5,
            d factors of 7.
        */
        vector<int> dp(states, INF);
        dp[id(0, 0, 0, 0)] = 0;

        for (int a = 0; a < A; a++) {
            for (int b = 0; b < B; b++) {
                for (int c = 0; c < C; c++) {
                    for (int d = 0; d < D; d++) {

                        if (a == 0 && b == 0 && c == 0 && d == 0)
                            continue;

                        int cur = id(a, b, c, d);

                        for (int digit = 2; digit <= 9; digit++) {
                            int na = max(0, a - f[digit][0]);
                            int nb = max(0, b - f[digit][1]);
                            int nc = max(0, c - f[digit][2]);
                            int nd = max(0, d - f[digit][3]);

                            dp[cur] = min(dp[cur],
                                          dp[id(na, nb, nc, nd)] + 1);
                        }
                    }
                }
            }
        }

        auto need = [&](int a, int b, int c, int d) {
            a = max(0, r2 - a);
            b = max(0, r3 - b);
            c = max(0, r5 - c);
            d = max(0, r7 - d);

            return dp[id(a, b, c, d)];
        };

        int n = num.size();

        // Prefix factor counts.
        vector<array<int, 4>> pref(n + 1);
        vector<bool> zeroFreePrefix(n + 1, true);

        pref[0] = {0, 0, 0, 0};

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i];

            if (num[i] == '0') {
                zeroFreePrefix[i + 1] = false;
                continue;
            }

            zeroFreePrefix[i + 1] = zeroFreePrefix[i];

            int d = num[i] - '0';

            pref[i + 1][0] = min(r2, pref[i + 1][0] + f[d][0]);
            pref[i + 1][1] = min(r3, pref[i + 1][1] + f[d][1]);
            pref[i + 1][2] = min(r5, pref[i + 1][2] + f[d][2]);
            pref[i + 1][3] = min(r7, pref[i + 1][3] + f[d][3]);
        }

        // Check if num itself is valid.
        if (zeroFreePrefix[n] &&
            pref[n][0] >= r2 &&
            pref[n][1] >= r3 &&
            pref[n][2] >= r5 &&
            pref[n][3] >= r7) {
            return num;
        }

        /*
            Try to find the smallest valid number having
            exactly the same length as num.
        */
        for (int i = n - 1; i >= 0; i--) {
            // Everything before i must be zero-free.
            if (!zeroFreePrefix[i])
                continue;

            int oldDigit = num[i] - '0';

            for (int d = oldDigit + 1; d <= 9; d++) {
                int e2 = min(r2, pref[i][0] + f[d][0]);
                int e3 = min(r3, pref[i][1] + f[d][1]);
                int e5 = min(r5, pref[i][2] + f[d][2]);
                int e7 = min(r7, pref[i][3] + f[d][3]);

                int remaining = n - i - 1;

                if (need(e2, e3, e5, e7) <= remaining) {

                    string ans = num.substr(0, i);
                    ans += char('0' + d);

                    int a = e2, b = e3, c = e5, e = e7;

                    // Make the suffix as small as possible.
                    for (int pos = i + 1; pos < n; pos++) {
                        int left = n - pos - 1;

                        for (int x = 1; x <= 9; x++) {
                            int na = min(r2, a + f[x][0]);
                            int nb = min(r3, b + f[x][1]);
                            int nc = min(r5, c + f[x][2]);
                            int nd = min(r7, e + f[x][3]);

                            if (need(na, nb, nc, nd) <= left) {
                                ans += char('0' + x);

                                a = na;
                                b = nb;
                                c = nc;
                                e = nd;

                                break;
                            }
                        }
                    }

                    return ans;
                }
            }
        }

        /*
            No solution with the same length.

            IMPORTANT:
            The answer may need MORE than n+1 digits.

            Therefore use the maximum of:
              - n+1
              - minimum digits required for t
        */
        int minDigits = dp[id(r2, r3, r5, r7)];

        int len = max(n + 1, minDigits);

        string ans;
        ans.reserve(len);

        int a = 0, b = 0, c = 0, d = 0;

        // Construct the lexicographically smallest zero-free number.
        for (int pos = 0; pos < len; pos++) {
            int left = len - pos - 1;

            for (int digit = 1; digit <= 9; digit++) {
                int na = min(r2, a + f[digit][0]);
                int nb = min(r3, b + f[digit][1]);
                int nc = min(r5, c + f[digit][2]);
                int nd = min(r7, d + f[digit][3]);

                if (need(na, nb, nc, nd) <= left) {
                    ans += char('0' + digit);

                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;

                    break;
                }
            }
        }

        return ans;
    }
};
