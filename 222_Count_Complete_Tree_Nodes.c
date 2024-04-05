/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int countNodes(struct TreeNode *root) {
    return root ? 1 + countNodes(root->left) + countNodes(root->right) : 0;
}
