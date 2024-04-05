#include <stdbool.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSumSub(struct TreeNode *root, int targetSum) {
    if (!root->left && !root->right) {
        return root->val == targetSum;
    }
    if (root->left) if (hasPathSumSub(root->left, targetSum - root->val)) {
        return true;
    }
    if (root->right) if (hasPathSumSub(root->right, targetSum - root->val)) {
        return true;
    }
    return false;
}

bool hasPathSum(struct TreeNode *root, int targetSum) {
    if (!root) {
        return false;
    }
    return hasPathSumSub(root, targetSum);
}
