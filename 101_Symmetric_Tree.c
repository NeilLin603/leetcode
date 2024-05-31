#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSymmetricSub(struct TreeNode *l, struct TreeNode *r) {
    if (!(l || r)) {
        return true;
    }
    if (!l && r || l && !r) {
        return false;
    }
    if (l->val != r->val) {
        return false;
    }
    return isSymmetricSub(l->left, r->right) &&
           isSymmetricSub(l->right, r->left);
}

bool isSymmetric(struct TreeNode *root) {
    return isSymmetricSub(root->left, root->right);
}

int main() {
    struct {
        int vals[10], valsSize;
    } tc[] = {
        {.vals = {1,2,2,3,4,4,3}, .valsSize = 7},
        {.vals = {1,2,2,NULL_NODE,3,NULL_NODE,3}, .valsSize = 7}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        printf("Output: %s\n\n", isSymmetric(root) ? "true" : "false");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
