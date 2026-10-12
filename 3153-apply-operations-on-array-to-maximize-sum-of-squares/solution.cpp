class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1000000007;
        long long ans = 0;
        int bits[32] = {0};

        for (int num : nums) {
            for (int i = 0; i < 32; i++) {
                if (num & (1 << i)) {
                    bits[i]++;
                }
            }
        }

        for (int i = 0; i < k; i++) {
            long long num = 0;

            for (int j = 0; j < 32; j++) {
                if (bits[j] > 0) {
                    num |= (1LL << j);
                    bits[j]--;
                }
            }

            ans = (ans + num * num) % MOD;
        }

        return ans;
    }
}; 
