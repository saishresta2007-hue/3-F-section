class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        int odd = 0, midIdx = -1;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] & 1) {
                odd++;
                midIdx = i;
            }
        }

        if (odd > 1) return "";

        int n = s.size();
        int m = n / 2;

        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) halfCnt[i] = cnt[i] / 2;

        string leftTarget = target.substr(0, m);

        auto buildPalindrome = [&](const string& half) {
            string res = half;
            if (n & 1) res.push_back(char('a' + midIdx));
            for (int i = m - 1; i >= 0; i--) {
                res.push_back(half[i]);
            }
            return res;
        };

        vector<int> rem = halfCnt;
        bool possible = true;

        for (char c : leftTarget) {
            int x = c - 'a';
            if (rem[x] == 0) {
                possible = false;
                break;
            }
            rem[x]--;
        }

        if (possible) {
            string pal = buildPalindrome(leftTarget);
            if (pal > target) return pal;
        }

        vector<vector<int>> pref(m + 1, vector<int>(26));
        pref[0] = halfCnt;

        int matched = 0;
        while (matched < m) {
            int x = leftTarget[matched] - 'a';
            if (pref[matched][x] == 0) break;

            pref[matched + 1] = pref[matched];
            pref[matched + 1][x]--;
            matched++;
        }

        string bestHalf = "";

        for (int i = min(m - 1, matched); i >= 0; i--) {
            vector<int> cur = pref[i];
            int need = leftTarget[i] - 'a';

            int pick = -1;
            for (int d = need + 1; d < 26; d++) {
                if (cur[d] > 0) {
                    pick = d;
                    break;
                }
            }

            if (pick == -1) continue;

            string half = leftTarget.substr(0, i);
            half.push_back(char('a' + pick));
            cur[pick]--;

            for (int d = 0; d < 26; d++) {
                half.append(cur[d], char('a' + d));
            }

            bestHalf = half;
            break;
        }

        if (bestHalf.empty()) return "";
        return buildPalindrome(bestHalf);
    }
};
