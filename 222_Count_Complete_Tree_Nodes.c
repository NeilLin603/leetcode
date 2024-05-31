#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode *root) {
    return root ? 1 + countNodes(root->left) + countNodes(root->right) : 0;
}

int main() {
    struct {
        int vals[16], valsSize;
    } tc[] = {
        {.vals = {1,2,3,4,5,6}, .valsSize = 6},
        {.valsSize = 0},
        {.vals = {1}, .valsSize = 1}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        printf("\nOutput: %d:\n\n", countNodes(root));

        // Free tree
        freeTree(&root);
    }

    return 0;
}
