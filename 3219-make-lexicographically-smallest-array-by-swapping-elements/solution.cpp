class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());

        vector<int> ans(n);

        int start = 0;
        while (start < n) {
            int end = start;

            while (end + 1 < n &&
                   (long long)arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            vector<int> indices;
            vector<int> values;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
                values.push_back(arr[i].first);
            }

            sort(indices.begin(), indices.end());

            for (int i = 0; i < (int)indices.size(); i++) {
                ans[indices[i]] = values[i];
            }

            start = end + 1;
        }

        return ans;
    }
};
