#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! Solving concept: recursively flatten the child trees by in-order traversal
//! Example:
//!           |                       |    1          1           |
//!           |                       |   /            \          |
//!           |      1          1     |  2              2         |
//!     1     |     / \        / \    |   \              \        |
//!    / \    |    2   5      2   5   |    3              3       |
//!   2   5   =>  /     \  =>  \   \  =>    \      =>      \      |
//!  / \   \  |  3       6      3   6 |      4              4     |
//! 3   4   6 |   \              \    |       \              \    |
//!           |    4              4   |        5              5   |
//!           |                       |         \              \  |
//!           |                       |          6              6 |
//!           |        (root = 2)     |        (root = 1)         |
//!
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
static inline struct TreeNode *rightLeaf(struct TreeNode *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

void flatten(struct TreeNode *root) {
    if (root) {
        flatten(root->left);
        flatten(root->right);
        if (root->left) {
            if (root->right) {
                rightLeaf(root->left)->right = root->right;
            }
            root->right = root->left;
            root->left = NULL;
        }
    }
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
    QNode_t *head;
    QNode_t *tail;
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

#define NULL_NODE 0x80000000

#define ADD_NODE(q, node, vals)                     \
    if (*(vals) != NULL_NODE) {                     \
        (node) = (Node_t *)malloc(sizeof(Node_t));  \
        (node)->val = *(vals);                      \
        enqueue((q), (node));                       \
    } else {                                        \
        (node) = NULL;                              \
    }                                               \
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
            root->right = NULL;
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
    printf("%s [");
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
        {.vals = {1,2,5,3,4,NULL_NODE,6}, .valsSize = 7},
        {.valsSize = 0}, {.vals = {0}, .valsSize = 1}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root =");

        // Output
        flatten(root);
        printTree(root, "Output:");
        printf("\n");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
