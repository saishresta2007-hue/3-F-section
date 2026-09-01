class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<vector<int>> litterId(m, vector<int>(n, -1));

        int sr = -1, sc = -1;
        int k = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    litterId[i][j] = k++;
                }
            }
        }

        int fullMask = (1 << k) - 1;

        struct State {
            int r, c, mask, e, dist;
        };

        int cells = m * n;

        vector<vector<int>> best(cells, vector<int>(1 << k, -1));

        auto id = [&](int r, int c) {
            return r * n + c;
        };

        queue<State> q;
        q.push({sr, sc, 0, energy, 0});
        best[id(sr, sc)][0] = energy;

        int dirs[5] = {1, 0, -1, 0, 1};

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (cur.mask == fullMask) return cur.dist;

            if (cur.e == 0) continue; // cannot make another move

            for (int d = 0; d < 4; d++) {
                int nr = cur.r + dirs[d];
                int nc = cur.c + dirs[d + 1];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (classroom[nr][nc] == 'X') continue;

                int ne = cur.e - 1;
                int nmask = cur.mask;

                if (classroom[nr][nc] == 'L') {
                    nmask |= (1 << litterId[nr][nc]);
                }

                if (classroom[nr][nc] == 'R') {
                    ne = energy; // reset to full capacity
                }

                int pos = id(nr, nc);

                if (ne <= best[pos][nmask]) continue;

                best[pos][nmask] = ne;
                q.push({nr, nc, nmask, ne, cur.dist + 1});
            }
        }

        return -1;
    }
};
