class Solution {
public:
    vector<string> ans;
    
    bool isValid(string s) {
        int count = 0;
        
        for (char c : s) {
            if (c == '(')
                count++;
            else if (c == ')') {
                count--;
                if (count < 0)
                    return false;
            }
        }
        
        return count == 0;
    }
    
    void solve(string s, int start, int removals) {
        if (removals == 0) {
            if (isValid(s))
                ans.push_back(s);
            return;
        }
        
        for (int i = start; i < s.length(); i++) {
            // Avoid generating duplicate strings
            if (i > start && s[i] == s[i - 1])
                continue;
            
            // Only parentheses can be removed
            if (s[i] != '(' && s[i] != ')')
                continue;
            
            string temp = s.substr(0, i) + s.substr(i + 1);
            solve(temp, i, removals - 1);
        }
    }
    
    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;
        
        // Find minimum number of parentheses to remove
        for (char c : s) {
            if (c == '(') {
                left++;
            } 
            else if (c == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }
        
        int removals = left + right;
        solve(s, 0, removals);
        
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        
        return ans;
    }
};
