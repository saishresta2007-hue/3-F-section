#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> g(n);

        for (auto &e : invocations) {
            g[e[0]].push_back(e[1]);
        }

        // Find all suspicious methods reachable from k
        vector<int> suspicious(n, 0);
        queue<int> q;
        q.push(k);
        suspicious[k] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : g[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = 1;
                    q.push(v);
                }
            }
        }

        // Check if any non-suspicious method invokes a suspicious one
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all;
            }
        }

        // Remove all suspicious methods
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (!suspicious[i]) ans.push_back(i);
        }

        return ans;
    }
};
