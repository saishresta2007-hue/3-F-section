class Solution {
public:
    struct Node {
        int len;
        int leftLen, rightLen, best;
        char leftChar, rightChar;

        Node() {
            len = 0;
            leftLen = rightLen = best = 0;
            leftChar = rightChar = 0;
        }

        Node(char c) {
            len = 1;
            leftLen = rightLen = best = 1;
            leftChar = rightChar = c;
        }
    };

    vector<Node> seg;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Prefix
        res.leftLen = a.leftLen;
        if (a.leftLen == a.len && a.rightChar == b.leftChar) {
            res.leftLen = a.len + b.leftLen;
        }

        // Suffix
        res.rightLen = b.rightLen;
        if (b.rightLen == b.len && a.rightChar == b.leftChar) {
            res.rightLen = b.len + a.rightLen;
        }

        // Best answer completely inside either half
        res.best = max(a.best, b.best);

        // Best answer crossing the boundary
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.rightLen + b.leftLen);
        }

        return res;
    }

    void build(int node, int l, int r, const string& s) {
        if (l == r) {
            seg[node] = Node(s[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, char c) {
        if (l == r) {
            seg[node] = Node(c);
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, c);
        else
            update(node * 2 + 1, mid + 1, r, pos, c);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.size();
        int k = queryIndices.size();

        seg.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> lengths;

        for (int i = 0; i < k; i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, pos, c);

            lengths.push_back(seg[1].best);
        }

        return lengths;
    }
};
