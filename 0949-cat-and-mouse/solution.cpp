class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<vector<vector<int>>> color(
            n, vector<vector<int>>(n, vector<int>(2, 0)));

        vector<vector<vector<int>>> degree(
            n, vector<vector<int>>(n, vector<int>(2, 0)));

        for (int m = 0; m < n; m++) {
            for (int c = 0; c < n; c++) {
                degree[m][c][0] = graph[m].size(); // mouse turn

                int cnt = 0;
                for (int nxt : graph[c]) {
                    if (nxt != 0) cnt++;
                }
                degree[m][c][1] = cnt; // cat turn
            }
        }

        queue<array<int, 4>> q;

        // Mouse at hole => Mouse wins
        for (int c = 1; c < n; c++) {
            for (int t = 0; t < 2; t++) {
                color[0][c][t] = 1;
                q.push({0, c, t, 1});
            }
        }

        // Cat catches mouse => Cat wins
        for (int m = 1; m < n; m++) {
            for (int t = 0; t < 2; t++) {
                color[m][m][t] = 2;
                q.push({m, m, t, 2});
            }
        }

        auto parents = [&](int m, int c, int turn) {
            vector<array<int, 3>> res;

            if (turn == 0) { // mouse to move now, so parent was cat turn
                for (int pc : graph[c]) {
                    if (pc == 0) continue;
                    res.push_back({m, pc, 1});
                }
            } else { // cat to move now, so parent was mouse turn
                for (int pm : graph[m]) {
                    res.push_back({pm, c, 0});
                }
            }

            return res;
        };

        while (!q.empty()) {
            auto [m, c, turn, result] = q.front();
            q.pop();

            for (auto &p : parents(m, c, turn)) {
                int pm = p[0];
                int pc = p[1];
                int pturn = p[2];

                if (color[pm][pc][pturn] != 0) continue;

                bool canWin =
                    (pturn == 0 && result == 1) ||
                    (pturn == 1 && result == 2);

                if (canWin) {
                    color[pm][pc][pturn] = result;
                    q.push({pm, pc, pturn, result});
                } else {
                    degree[pm][pc][pturn]--;

                    if (degree[pm][pc][pturn] == 0) {
                        int loseResult = (pturn == 0 ? 2 : 1);
                        color[pm][pc][pturn] = loseResult;
                        q.push({pm, pc, pturn, loseResult});
                    }
                }
            }
        }

        return color[1][2][0];
    }
};
