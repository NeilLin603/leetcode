#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} Node_t;

struct TreeNode *buildTree(int *inorder, int inorderSize,
                           int *postorder, int postorderSize) {
    if (!inorderSize) {
        return NULL;
    }
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1];
    int idx = 0;
    while (root->val != inorder[idx++]);
    root->right = buildTree(inorder + idx, inorderSize - idx,
                            postorder + idx - 1, postorderSize - idx);
    root->left = buildTree(inorder, idx - 1, postorder, idx - 1);
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

Queue_t *initqueue() {
    Queue_t *q = (Queue_t *)malloc(sizeof(Queue_t));
    q->head = q->tail = NULL;
    return q;
}

void enqueue(Queue_t *q, Node_t *node) {
    QNode_t *tail = (QNode_t *)malloc(sizeof(QNode_t));
    tail->node = node;
    tail->next = NULL;
    q->tail = q->head ? (q->tail->next = tail) : (q->head = tail);
}

int dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *head = q->head;
    *node = head->node;
    q->head = head->next;
    free(head);
    if (!q->head) {
        q->tail = NULL;
    }
    return 1;
}

void printTree(Node_t *root, char *name) {
    printf("%s: [", name);
    Queue_t *q = initqueue();
    enqueue(q, root);
    int nullCnt = 0;
    while (dequeue(q, &root)) {
        if (root) {
            while (nullCnt) {
                printf("null,");
                nullCnt--;
            }
            printf("%d,", root->val);
            enqueue(q, root->left);
            enqueue(q, root->right);
        } else {
            nullCnt++;
        }
    }
    free(q);
    printf("\b]\n\n");
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
        int inorder[10], postorder[10], size;
    } tc[] = {
        {.inorder = {9,3,15,20,7}, .postorder = {9,15,7,20,3}, .size = 5},
        {.inorder = {-1}, .postorder = {-1}, .size = 1}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Inputs
        printArray(tc[i].inorder, tc[i].size, "Input: inorder");
        printArray(tc[i].postorder, tc[i].size, ", postorder");

        // Output
        root = buildTree(tc[i].inorder, tc[i].size, tc[i].postorder, tc[i].size);
        printTree(root, "\nOutput");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
