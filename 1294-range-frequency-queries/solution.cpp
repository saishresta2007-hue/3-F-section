class RangeFreqQuery {
    unordered_map<int, vector<int>> pos;

public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            pos[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value) {
        if (!pos.count(value))
            return 0;

        vector<int>& indices = pos[value];

        auto l = lower_bound(indices.begin(), indices.end(), left);
        auto r = upper_bound(indices.begin(), indices.end(), right);

        return r - l;
    }
};
