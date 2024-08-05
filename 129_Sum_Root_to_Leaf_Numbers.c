#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! Solving concept:
//! 1. According to the characteristic of trees, each leaf binding with exactly
//!    one parent path, which can be represented by a parent number.
//! 2. Recursively pass the parent number and multiple it by 10 to it's child
//!    nodes in each iteration, then the number correspond to each leaf node can
//!    be found out.
//!*****************************************************************************

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

//
// Start of the submission code
//
int sumNumbersSub(struct TreeNode *root, int parentNum) {
    int ret = 0;
    parentNum = parentNum * 10 + root->val;
    if (root->left) {
        ret += sumNumbersSub(root->left, parentNum);
    }
    if (root->right) {
        ret += sumNumbersSub(root->right, parentNum);
    }
    return ret ? ret : parentNum;
}

int sumNumbers(struct TreeNode *root) {
    return sumNumbersSub(root, 0);
}
//
// End of the submission code
//

typedef struct TreeNode Node_t;

typedef struct QueueNode {
    Node_t *node;
    struct QueueNode *next;
} QNode_t;

typedef struct {
    QNode_t *head, *tail;
} Queue_t;

Queue_t *initqueue() {
    Queue_t *q = (Queue_t *)malloc(sizeof(Queue_t));
    q->head = q->tail = NULL;
    return q;
}

void enqueue(Queue_t *q, Node_t *node) {
    QNode_t *new = (QNode_t *)malloc(sizeof(QNode_t));
    new->node = node;
    new->next = NULL;
    q->tail = q->head ? (q->tail->next = new) : (q->head = new);
}

int dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *tmp = q->head;
    *node = tmp->node;
    q->head = tmp->next ? tmp->next : (q->tail = NULL);
    free(tmp);
    return 1;
}

#define NULL_NODE -1

#define ADD_NODE(q, node, vals)                                                \
    if (*(vals) != NULL_NODE) {                                                \
        (node) = (Node_t *)malloc(sizeof(Node_t));                             \
        (node)->val = *(vals);                                                 \
        enqueue((q), (node));                                                  \
    } else {                                                                   \
        (node) = NULL;                                                         \
    }                                                                          \
    (vals)++

Node_t *buildTree(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Node_t *root, *node;
    Queue_t *q = initqueue();
    ADD_NODE(q, root, vals);
    while (--valsSize) {
        dequeue(q, &node);
        ADD_NODE(q, node->left, vals);
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        ADD_NODE(q, node->right, vals);
    }
    while (dequeue(q, &node)) {
        node->left = node->right = NULL;
    }
    free(q);
    return root;
}

void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    if (root) {
        printf("%d", root->val);
        Queue_t *q = initqueue();
        enqueue(q, root->left);
        enqueue(q, root->right);
        int nullCnt = 0;
        while (dequeue(q, &root)) {
            if (root) {
                while (nullCnt) {
                    printf(",null");
                    nullCnt--;
                }
                printf(",%d", root->val);
                enqueue(q, root->left);
                enqueue(q, root->right);
            } else {
                nullCnt++;
            }
        }
        free(q);
    }
    printf("]\n");
}

void freeTree(Node_t **root) {
    if (*root) {
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

int main() {
    struct {
        int vals[8], valsSize;
    } tc[] = {
        {.vals = {1,2,3}, .valsSize = 3},
        {.vals = {4,9,0,5,1}, .valsSize = 5}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        printf("Output: %d\n\n", sumNumbers(root));

        // Free tree
        freeTree(&root);
    }

    return 0;
}
