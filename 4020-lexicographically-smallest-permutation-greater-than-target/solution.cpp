class Solution {
public:
    bool maxGreater(vector<int>& cnt, const string& target, int pos) {
        int p = pos;

        for (int ch = 25; ch >= 0; --ch) {
            for (int k = 0; k < cnt[ch]; ++k) {
                char c = 'a' + ch;

                if (c > target[p]) return true;
                if (c < target[p]) return false;

                ++p;
            }
        }

        return false;
    }

    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s) cnt[c - 'a']++;

        string ans;

        for (int i = 0; i < n; ++i) {
            bool chosen = false;

            for (int ch = 0; ch < 26; ++ch) {
                if (cnt[ch] == 0) continue;

                char c = 'a' + ch;
                if (c < target[i]) continue;

                cnt[ch]--;

                if (c == target[i]) {
                    if (maxGreater(cnt, target, i + 1)) {
                        ans.push_back(c);
                        chosen = true;
                        break;
                    }
                } else {
                    ans.push_back(c);

                    for (int d = 0; d < 26; ++d)
                        ans.append(cnt[d], char('a' + d));

                    return ans;
                }

                cnt[ch]++;
            }

            if (!chosen) return "";
        }

        return "";
    }
};
