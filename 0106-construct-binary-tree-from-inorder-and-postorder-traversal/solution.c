/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* build(
    int* inorder,
    int* postorder,
    int inStart,
    int inEnd,
    int* postIndex,
    int* map
) {
    if (inStart > inEnd)
        return NULL;

    int rootVal = postorder[(*postIndex)--];
    struct TreeNode* root = createNode(rootVal);

    int pos = map[rootVal + 3000];

    // Build right subtree first because postorder is Left->Right->Root
    root->right = build(inorder, postorder, pos + 1, inEnd, postIndex, map);
    root->left = build(inorder, postorder, inStart, pos - 1, postIndex, map);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize,
                           int* postorder, int postorderSize) {
    int map[6001];

    for (int i = 0; i < inorderSize; i++) {
        map[inorder[i] + 3000] = i;
    }

    int postIndex = postorderSize - 1;

    return build(inorder, postorder, 0, inorderSize - 1,
                 &postIndex, map);
}
