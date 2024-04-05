#include <stdbool.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSymmetricSub(struct TreeNode *l, struct TreeNode *r) {
    if (!l && !r) {
        return true;
    }
    if (!l && r || l && !r) {
        return false;
    }
    if (l->val != r->val) {
        return false;
    }
    return isSymmetricSub(l->left, r->right) && isSymmetricSub(l->right, r->left);
}

bool isSymmetric(struct TreeNode *root) {
    if (root) {
        return isSymmetricSub(root->left, root->right);
    }
    return true;
}
