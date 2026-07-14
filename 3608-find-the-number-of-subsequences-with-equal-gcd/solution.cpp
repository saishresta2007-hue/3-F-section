class Solution {
public:
    static const int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        const int MAXV = 200;

        // Precompute gcd
        int gcdVal[201][201];
        for (int i = 0; i <= MAXV; i++) {
            for (int j = 0; j <= MAXV; j++) {
                if (i == 0) gcdVal[i][j] = j;
                else if (j == 0) gcdVal[i][j] = i;
                else gcdVal[i][j] = std::gcd(i, j);
            }
        }

        vector<vector<int>> dp(MAXV + 1, vector<int>(MAXV + 1, 0));
        vector<vector<int>> ndp(MAXV + 1, vector<int>(MAXV + 1, 0));

        dp[0][0] = 1;

        for (int x : nums) {
            for (int i = 0; i <= MAXV; i++)
                fill(ndp[i].begin(), ndp[i].end(), 0);

            for (int g1 = 0; g1 <= MAXV; g1++) {
                for (int g2 = 0; g2 <= MAXV; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    long long cur = dp[g1][g2];

                    // Skip x
                    ndp[g1][g2] = (ndp[g1][g2] + cur) % MOD;

                    // Put into seq1
                    int ng1 = gcdVal[g1][x];
                    ndp[ng1][g2] = (ndp[ng1][g2] + cur) % MOD;

                    // Put into seq2
                    int ng2 = gcdVal[g2][x];
                    ndp[g1][ng2] = (ndp[g1][ng2] + cur) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAXV; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};
