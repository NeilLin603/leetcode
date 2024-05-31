#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode *p, struct TreeNode *q) {
    if (!(p || q)) {
        return true;
    }
    if (!p && q || p && !q) {
        return false;
    }
    if (p->val != q->val) {
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main() {
    struct {
        int pVals[10], pSize, qVals[10], qSize;
    } tc[] = {
        {.pVals = {1, 2, 3}, .pSize = 3, .qVals = {1, 2, 3}, .qSize = 3},
        {.pVals = {1, 2}, .pSize = 2, .qVals = {1, NULL_NODE, 2}, .qSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *p, *q;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        p = buildTree(tc[i].pVals, tc[i].pSize);
        printTree(p, "p");
        q = buildTree(tc[i].qVals, tc[i].qSize);
        printTree(q, "q");

        // Output
        printf("Output: %s\n\n", isSameTree(p, q) ? "true" : "false");

        // Free trees
        freeTree(&p);
        freeTree(&q);
    }

    return 0;
}
