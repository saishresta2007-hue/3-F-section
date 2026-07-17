class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        vector<long long> cnt(mx + 1, 0);

        // Count numbers divisible by each d
        for (int d = 1; d <= mx; d++) {
            for (int m = d; m <= mx; m += d)
                cnt[d] += freq[m];
        }

        vector<long long> exact(mx + 1, 0);

        // Inclusion-Exclusion
        for (int d = mx; d >= 1; d--) {
            long long c = cnt[d];
            exact[d] = c * (c - 1) / 2;
            for (int m = d + d; m <= mx; m += d)
                exact[d] -= exact[m];
        }

        vector<long long> pref(mx + 1, 0);
        for (int i = 1; i <= mx; i++)
            pref[i] = pref[i - 1] + exact[i];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long k : queries) {
            int g = lower_bound(pref.begin() + 1, pref.end(), k + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};
