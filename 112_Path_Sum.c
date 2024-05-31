#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode *root, int targetSum) {
    if (!root) {
        return false;
    }
    targetSum -= root->val;
    if (!(root->left || root->right)) {
        return !targetSum;
    }
    return hasPathSum(root->left, targetSum) ||
           hasPathSum(root->right, targetSum);
}

int main() {
    struct {
        int vals[16], valsSize, targetSum;
    } tc[] = {
        {.vals = {5,4,8,11,NULL_NODE,13,4,7,2,NULL_NODE,NULL_NODE,NULL_NODE,1},
         .valsSize = 13, .targetSum = 22},
        {.vals = {1,2,3}, .valsSize = 3, .targetSum = 5}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");
        printf(", targetSum = %d", tc[i].targetSum);

        // Output
        printf("\nOutput: %s\n\n",
               hasPathSum(root, tc[i].targetSum) ? "true" : "false");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
