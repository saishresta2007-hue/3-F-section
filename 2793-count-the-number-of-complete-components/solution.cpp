class Solution {
public:
    vector<vector<int>> adj;
    vector<int> vis;
    int vertices, degreeSum;

    void dfs(int node) {
        vis[node] = 1;
        vertices++;
        degreeSum += adj[node].size();

        for (int nei : adj[node]) {
            if (!vis[nei]) {
                dfs(nei);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        adj.assign(n, {});
        vis.assign(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                vertices = 0;
                degreeSum = 0;

                dfs(i);

                if (degreeSum == vertices * (vertices - 1))
                    ans++;
            }
        }

        return ans;
    }
};
