#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node_t;

struct TreeNode *buildTree(int *preorder, int preorderSize,
                           int *inorder, int inorderSize) {
    struct TreeNode *root = NULL;
    if (preorderSize) {
        // Search 'preorder[0]' in the 'inorder' array
        int index = -1;
        while (inorder[++index] != *preorder);

        root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        root->val = *preorder++;
        root->left = buildTree(preorder, index, inorder, index);
        root->right = buildTree(preorder + index, preorderSize - index - 1,
                                inorder + index + 1, inorderSize - index - 1);
    }
    return root;
}

typedef struct QueueNode {
    Node_t *node;
    struct QueueNode *next;
} QNode_t;

typedef struct {
    QNode_t *head;
    QNode_t *tail;
} Queue_t;

void enqueue(Queue_t *q, Node_t *node) {
    QNode_t *tail = (QNode_t *)malloc(sizeof(QNode_t));
    tail->node = node;
    tail->next = NULL;
    if (q->head) {
        q->tail->next = tail;
        q->tail = tail;
    } else {
        q->head = q->tail = tail;
    }
}

int dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *temp = q->head;
    *node = temp->node;
    q->head = temp->next;
    if (!q->head) {
        q->tail = NULL;
    }
    free(temp);
    return 1;
}

void printTree(Node_t *root, char *name) {
    printf("%s: [", name);
    if (root) {
        printf("%d", root->val);
        Queue_t q = {NULL, NULL};
        enqueue(&q, root->left);
        enqueue(&q, root->right);
        int null_count = 0;
        Node_t *node;
        while (dequeue(&q, &node)) {
            if (node) {
                while (null_count) {
                    printf(",null");
                    null_count--;
                }
                printf(",%d", node->val);
                enqueue(&q, node->left);
                enqueue(&q, node->right);
            } else {
                null_count++;
            }
        }
    }
    printf("]\n\n");
}

void freeTree(Node_t **root) {
    if (*root) {
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]");
}

int main() {
    struct {
        int preorder[10], inorder[10], size;
    } tc[] = {
        {.preorder = {3,9,20,15,7}, .inorder = {9,3,15,20,7}, .size = 5},
        {.preorder = {-1}, .inorder = {-1}, .size = 1},
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Inputs
        printArray(tc[i].preorder, tc[i].size, "Input: preorder");
        printArray(tc[i].inorder, tc[i].size, ", inorder");

        // Output
        root = buildTree(tc[i].preorder, tc[i].size, tc[i].inorder, tc[i].size);
        printTree(root, "\nOutput");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
