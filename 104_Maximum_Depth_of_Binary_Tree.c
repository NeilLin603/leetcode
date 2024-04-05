#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode *root) {
    return root ? 1 + MAX(maxDepth(root->left), maxDepth(root->right)) : 0;
}
