class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // Node found

            // Case 1 & 2: zero or one child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }

            if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            // Case 3: two children
            TreeNode* succ = root->right;
            while (succ->left) {
                succ = succ->left;
            }

            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }

        return root;
    }
};
