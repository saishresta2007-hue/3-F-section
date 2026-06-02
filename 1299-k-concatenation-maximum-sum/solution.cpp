class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long kadane(const vector<int>& arr, int times) {
        long long cur = 0, best = 0;

        for (int t = 0; t < times; t++) {
            for (int x : arr) {
                cur = max(0LL, cur + x);
                best = max(best, cur);
            }
        }

        return best;
    }

    int kConcatenationMaxSum(vector<int>& arr, int k) {
        long long total = 0;
        for (int x : arr) total += x;

        if (k == 1) {
            return kadane(arr, 1) % MOD;
        }

        long long maxTwo = kadane(arr, 2);
        long long ans = maxTwo;

        if (total > 0) {
            ans = maxTwo + (long long)(k - 2) * total;
        }

        return ans % MOD;
    }
};
