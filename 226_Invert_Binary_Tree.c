#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *invertTree(struct TreeNode *root) {
    if (root) {
        struct TreeNode *left = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(left);
    }
    return root;
}

int main() {
    struct {
        int vals[10], valsSize;
    } tc[] = {
        {.vals = {4,2,7,1,3,6,9}, .valsSize = 7},
        {.vals = {2,1,3}, .valsSize = 3},
        {.valsSize = 0}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        root = invertTree(root);
        printTree(root, "Output");
        printf("\n");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
