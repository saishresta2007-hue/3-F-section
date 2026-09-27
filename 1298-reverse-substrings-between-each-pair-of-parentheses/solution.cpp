class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr = "";

        for (char ch : s) {
            if (ch == '(') {
                st.push(curr);
                curr = "";
            }
            else if (ch == ')') {
                reverse(curr.begin(), curr.end());

                string temp = st.top();
                st.pop();

                curr = temp + curr;
            }
            else {
                curr += ch;
            }
        }

        return curr;
    }
};
