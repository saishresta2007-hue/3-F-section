class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        long long start = 1;

        for (int d = 1; start <= n; d++) {
            long long end = start * 10 - 1;
            long long cnt = min(n, end) - start + 1;

            if (cnt > 0) {
                ans += cnt * ((d - 1) / 3);
            }

            if (start > n / 10) break;
            start *= 10;
        }

        return ans;
    }
};
