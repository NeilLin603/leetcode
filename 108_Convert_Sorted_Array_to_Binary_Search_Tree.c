#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* sortedArrayToBST(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = nums[numsSize >> 1];
    root->left = sortedArrayToBST(nums, numsSize >> 1);
    root->right = sortedArrayToBST(nums + (numsSize >> 1) + 1, numsSize & 1 ? numsSize >> 1 : (numsSize >> 1) - 1);
    return root;
}
