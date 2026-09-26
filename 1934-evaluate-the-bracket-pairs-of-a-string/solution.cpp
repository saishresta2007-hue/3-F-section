#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        for (auto &k : knowledge) {
            mp[k[0]] = k[1];
        }

        string result;
        string key;
        bool inside = false;

        for (char ch : s) {
            if (ch == '(') {
                inside = true;
                key = "";
            }
            else if (ch == ')') {
                inside = false;
                if (mp.count(key))
                    result += mp[key];
                else
                    result += "?";
            }
            else {
                if (inside)
                    key += ch;
                else
                    result += ch;
            }
        }

        return result;
    }
};
