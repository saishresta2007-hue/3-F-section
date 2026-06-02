class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;

        if (rankv[a] == rankv[b]) rankv[a]++;

        return true;
    }
};

class Solution {
public:
    int kruskal(int n, vector<vector<int>>& edges, int skip, int force) {
        DSU dsu(n);
        int weight = 0;
        int used = 0;

        if (force != -1) {
            dsu.unite(edges[force][0], edges[force][1]);
            weight += edges[force][2];
            used++;
        }

        for (int i = 0; i < edges.size(); i++) {
            if (i == skip) continue;

            if (dsu.unite(edges[i][0], edges[i][1])) {
                weight += edges[i][2];
                used++;
            }
        }

        return (used == n - 1) ? weight : INT_MAX;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n, vector<vector<int>>& edges) {

        int m = edges.size();

        vector<vector<int>> e;
        for (int i = 0; i < m; i++) {
            e.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }

        sort(e.begin(), e.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        vector<vector<int>> sortedEdges;
        for (auto &x : e) {
            sortedEdges.push_back({x[0], x[1], x[2]});
        }

        int mstWeight = kruskal(n, sortedEdges, -1, -1);

        vector<int> critical, pseudo;

        for (int i = 0; i < m; i++) {
            int originalIdx = e[i][3];

            // Critical: removing it increases MST weight
            if (kruskal(n, sortedEdges, i, -1) > mstWeight) {
                critical.push_back(originalIdx);
            }
            // Pseudo-critical: forcing it still allows an MST
            else if (kruskal(n, sortedEdges, -1, i) == mstWeight) {
                pseudo.push_back(originalIdx);
            }
        }

        return {critical, pseudo};
    }
};
