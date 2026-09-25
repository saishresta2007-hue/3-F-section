class Solution {
public:
    set<string> parse(string &s, int &i) {
        vector<set<string>> parts;
        parts.push_back({""});

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> cur;

            if (islower(s[i])) {
                cur.insert(string(1, s[i]));
                i++;
            } else if (s[i] == '{') {
                i++;
                cur = parseUnion(s, i);
            }

            set<string> temp;
            for (auto &a : parts.back()) {
                for (auto &b : cur) {
                    temp.insert(a + b);
                }
            }
            parts.back() = temp;
        }

        return parts.back();
    }

    set<string> parseUnion(string &s, int &i) {
        set<string> res;

        while (true) {
            set<string> cur = parse(s, i);
            res.insert(cur.begin(), cur.end());

            if (i >= s.size() || s[i] == '}') {
                if (i < s.size()) i++;
                break;
            }

            if (s[i] == ',') i++;
        }

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> ans = parseUnion(expression, i);
        return vector<string>(ans.begin(), ans.end());
    }
};
