class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<int>> dp(4, vector<int>(MAXX, 0));
        dp[0][0] = 1;

        // DP for XOR of exactly 3 distinct elements
        for (int v : nums) {
            for (int cnt = 3; cnt >= 1; cnt--) {
                for (int x = 0; x < MAXX; x++) {
                    if (dp[cnt - 1][x]) {
                        dp[cnt][x ^ v] = 1;
                    }
                }
            }
        }

        vector<int> seen(MAXX, 0);

        // Values obtained when at least two indices are equal
        for (int v : nums)
            seen[v] = 1;

        // Values obtained from three distinct indices
        for (int x = 0; x < MAXX; x++)
            if (dp[3][x])
                seen[x] = 1;

        int ans = 0;
        for (int x = 0; x < MAXX; x++)
            ans += seen[x];

        return ans;
    }
};

