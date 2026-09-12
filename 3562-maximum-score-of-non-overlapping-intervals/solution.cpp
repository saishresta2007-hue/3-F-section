class Solution {
public:
    struct State {
        long long score;
        vector<int> ids;
    };

    static bool lexSmaller(const vector<int>& a, const vector<int>& b) {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    static State better(const State& A, const State& B) {
        if (A.score != B.score)
            return (A.score > B.score) ? A : B;

        if (lexSmaller(A.ids, B.ids))
            return A;
        return B;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> seg(n);
        for (int i = 0; i < n; i++) {
            seg[i] = {intervals[i][0], intervals[i][1],
                      intervals[i][2], i};
        }

        sort(seg.begin(), seg.end(),
             [](const auto& a, const auto& b) {
                 if (a[0] != b[0]) return a[0] < b[0];
                 return a[1] < b[1];
             });

        vector<long long> starts(n);
        for (int i = 0; i < n; i++) starts[i] = seg[i][0];

        vector<int> nxt(n);
        for (int i = 0; i < n; i++) {
            long long endPos = seg[i][1];
            nxt[i] = upper_bound(starts.begin(), starts.end(), endPos) - starts.begin();
        }

        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int k = 0; k <= 4; k++) {
            dp[n][k].score = 0;
            dp[n][k].ids.clear();
        }

        for (int i = n - 1; i >= 0; i--) {
            dp[i][0] = {0, {}};

            for (int k = 1; k <= 4; k++) {
                State skip = dp[i + 1][k];

                State take;
                take.score = seg[i][2] + dp[nxt[i]][k - 1].score;
                take.ids = dp[nxt[i]][k - 1].ids;
                take.ids.push_back((int)seg[i][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(skip, take);
            }
        }

        return dp[0][4].ids;
    }
};
