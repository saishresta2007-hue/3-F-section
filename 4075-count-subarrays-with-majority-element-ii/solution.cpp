class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int size = 2 * n + 5;
        int offset = n + 2;

        vector<int> bit(size + 1, 0);

        auto update = [&](int idx, int val) {
            while (idx <= size) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        };

        auto query = [&](int idx) {
            long long res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        };

        long long ans = 0;
        int pref = 0;

        // Initial prefix sum = 0
        update(offset, 1);

        for (int x : nums) {
            pref += (x == target ? 1 : -1);

            int idx = pref + offset;

            // Count previous prefix sums < current prefix sum
            ans += query(idx - 1);

            update(idx, 1);
        }

        return ans;
    }
};
