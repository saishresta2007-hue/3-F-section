class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // nextPos[i][c] = first position >= i containing character c
        vector<array<int, 26>> nextPos(n + 1);

        for (int c = 0; c < 26; c++)
            nextPos[n][c] = n;

        for (int i = n - 1; i >= 0; i--) {
            nextPos[i] = nextPos[i + 1];
            nextPos[i][word1[i] - 'a'] = i;
        }

        // prevPos[i][c] = last position < i containing character c
        vector<array<int, 26>> prevPos(n + 1);

        for (int c = 0; c < 26; c++)
            prevPos[0][c] = -1;

        for (int i = 1; i <= n; i++) {
            prevPos[i] = prevPos[i - 1];
            prevPos[i][word1[i - 1] - 'a'] = i - 1;
        }

        /*
         * exact[j] = latest possible position of word2[j]
         * such that word2[j..m-1] can be matched exactly.
         */
        vector<int> exact(m + 1, -1);
        exact[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            int limit = exact[j + 1];

            if (limit == -1)
                continue;

            exact[j] = prevPos[limit][word2[j] - 'a'];
        }

        /*
         * almost[j] = latest possible position of word2[j]
         * such that word2[j..m-1] can be matched with
         * at most one mismatch.
         */
        vector<int> almost(m + 1, -1);
        almost[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            int target = word2[j] - 'a';
            int best = -1;

            // Case 1: Match current character exactly.
            // The mismatch can be used later.
            if (almost[j + 1] != -1) {
                best = prevPos[almost[j + 1]][target];
            }

            // Case 2: Use the mismatch at current character.
            // The remaining suffix must match exactly.
            if (exact[j + 1] != -1) {
                for (int c = 0; c < 26; c++) {
                    if (c == target)
                        continue;

                    int p = prevPos[exact[j + 1]][c];
                    best = max(best, p);
                }
            }

            almost[j] = best;
        }

        // word2 cannot be formed with at most one mismatch.
        if (almost[0] == -1)
            return {};

        vector<int> ans;

        int pos = 0;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {
            int target = word2[j] - 'a';

            int chosen = n;
            bool mismatchUsedHere = false;

            /*
             * Option 1: Match word2[j] exactly.
             */
            int p = nextPos[pos][target];

            if (p != n) {
                bool possible = false;

                if (j == m - 1) {
                    possible = true;
                }
                else if (usedMismatch) {
                    // Mismatch already used.
                    // Remaining suffix must be exact.
                    if (exact[j + 1] != -1 &&
                        exact[j + 1] > p) {
                        possible = true;
                    }
                }
                else {
                    // Mismatch is still available.
                    if (almost[j + 1] != -1 &&
                        almost[j + 1] > p) {
                        possible = true;
                    }
                }

                if (possible) {
                    chosen = p;
                    mismatchUsedHere = usedMismatch;
                }
            }

            /*
             * Option 2: Use the one mismatch at this position.
             */
            if (!usedMismatch && exact[j + 1] != -1) {
                int limit = exact[j + 1];

                for (int c = 0; c < 26; c++) {
                    if (c == target)
                        continue;

                    int q = nextPos[pos][c];

                    if (q == n)
                        continue;

                    // Remaining suffix must be matched exactly.
                    if (j == m - 1 || limit > q) {
                        if (q < chosen) {
                            chosen = q;
                            mismatchUsedHere = true;
                        }
                    }
                }
            }

            if (chosen == n)
                return {};

            ans.push_back(chosen);
            pos = chosen + 1;
            usedMismatch = mismatchUsedHere;
        }

        return ans;
    }
};


