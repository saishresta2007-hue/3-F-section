class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            // Reverse alphabet value:
            // a = 26, b = 25, ..., z = 1
            int reverseValue = 'z' - s[i] + 1;

            // Position in string is i + 1
            ans += reverseValue * (i + 1);
        }

        return ans;
    }
};
