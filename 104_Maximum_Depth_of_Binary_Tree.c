#include "binary_tree.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode *root) {
    if (!root) {
        return 0;
    }
    int left = maxDepth(root->left), right = maxDepth(root->right);
    return 1 + MAX(left, right);
}

int main() {
    struct {
        int vals[10], valsSize;
    } tc[] = {
        {.vals = {3, 9, 20, NULL_NODE, NULL_NODE, 15, 7}, .valsSize = 7},
        {.vals = {1, NULL_NODE, 2}, .valsSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = createTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        printf("Output: %d\n\n", maxDepth(root));

        // Free tree
        freeTree(&root);
    }

    return 0;
}
