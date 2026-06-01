/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int ans;

int dfs(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int left = dfs(root->left);
    int right = dfs(root->right);

    int leftPath = 0, rightPath = 0;

    if (root->left && root->left->val == root->val)
        leftPath = left + 1;

    if (root->right && root->right->val == root->val)
        rightPath = right + 1;

    if (leftPath + rightPath > ans)
        ans = leftPath + rightPath;

    return (leftPath > rightPath) ? leftPath : rightPath;
}

int longestUnivaluePath(struct TreeNode* root) {
    ans = 0;
    dfs(root);
    return ans;
}
