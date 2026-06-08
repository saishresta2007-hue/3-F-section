/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

long long totalSum;
long long best;

long long findTotal(struct TreeNode* root) {
    if (root == NULL) return 0;

    return root->val +
           findTotal(root->left) +
           findTotal(root->right);
}

long long dfs(struct TreeNode* root) {
    if (root == NULL) return 0;

    long long left = dfs(root->left);
    long long right = dfs(root->right);

    long long sum = root->val + left + right;

    long long product = sum * (totalSum - sum);
    if (product > best)
        best = product;

    return sum;
}

int maxProduct(struct TreeNode* root) {
    const long long MOD = 1000000007LL;

    totalSum = findTotal(root);
    best = 0;

    dfs(root);

    return (int)(best % MOD);
}
