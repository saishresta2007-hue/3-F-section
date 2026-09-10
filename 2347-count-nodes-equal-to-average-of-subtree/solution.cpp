class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};

        auto left = dfs(node->left);
        auto right = dfs(node->right);

        int sum = left.first + right.first + node->val;
        int cnt = left.second + right.second + 1;

        if (sum / cnt == node->val)
            ans++;

        return {sum, cnt};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
