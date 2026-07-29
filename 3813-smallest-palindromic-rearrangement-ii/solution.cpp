class Solution {
public:
    static const int CAP = 1000000;

    long long combCap(int n, int r) {
        r = min(r, n - r);
        long long res = 1;
        for (int i = 1; i <= r; i++) {
            __int128 cur = (__int128)res * (n - r + i);
            cur /= i;
            if (cur > CAP) return CAP + 1;
            res = (long long)cur;
        }
        return res;
    }

    long long countWays(vector<int> &cnt) {
        long long res = 1;
        int used = 0;
        for (int c : cnt) {
            if (c == 0) continue;
            long long ways = combCap(used + c, c);
            res *= ways;
            if (res > CAP) return CAP + 1;
            used += c;
        }
        return res;
    }

    // LeetCode expected function
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char ch : s) freq[ch - 'a']++;

        vector<int> half(26, 0);
        char mid = 0;
        int halfLen = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            halfLen += half[i];
            if (freq[i] % 2) mid = char('a' + i);
        }

        if (countWays(half) < k) return "";

        string left;
        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid) return left + string(1, mid) + right;
        return left + right;
    }
};
