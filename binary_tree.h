#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NULL_NODE 0x80000000L

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node_t;

typedef struct QueueNode {
    Node_t *node;
    struct QueueNode *next;
} QNode_t;

typedef struct {
    QNode_t *head;
    QNode_t *tail;
} Queue_t;

static void enqueue(Queue_t *q, Node_t *node) {
    QNode_t *new = (QNode_t *)malloc(sizeof(QNode_t));
    new->node = node;
    new->next = NULL;
    if (q->tail) {
        q->tail = q->tail->next = new;
    } else {
        q->head = q->tail = new;
    }
}

static bool dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return false;
    }
    QNode_t *ret = q->head;
    *node = ret->node;
    q->head = ret->next;
    free(ret);
    if (!q->head) {
        q->tail = NULL;
    }
    return true;
}

static Node_t *buildTree(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Queue_t q = {NULL, NULL};
    Node_t *root = (Node_t *)malloc(sizeof(Node_t)), *node;
    root->val = *vals;
    enqueue(&q, root);
    while (dequeue(&q, &node)) if (node) {
        if (!--valsSize) {
            node->left = node->right = NULL;
            break;
        }
        if (*++vals != NULL_NODE) {
            node->left = (Node_t *)malloc(sizeof(Node_t));
            node->left->val = *vals;
        } else {
            node->left = NULL;
        }
        enqueue(&q, node->left);
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        if (*++vals != NULL_NODE) {
            node->right = (Node_t *)malloc(sizeof(Node_t));
            node->right->val = *vals;
        } else {
            node->right = NULL;
        }
        enqueue(&q, node->right);
    }
    while (dequeue(&q, &node)) if (node) {
        node->left = node->right = NULL;
    }
    return root;
}

static void freeTree(Node_t **root) {
    if (*root) {
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

static void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    if (root) {
        Queue_t q = {NULL, NULL};
        printf("%d", root->val);
        enqueue(&q, root->left);
        enqueue(&q, root->right);
        Node_t *node;
        int cnt = 0;
        while (dequeue(&q, &node)) {
            if (node) {
                while (cnt) {
                    printf(",null");
                    cnt--;
                }
                printf(",%d", node->val);
                enqueue(&q, node->left);
                enqueue(&q, node->right);
            } else {
                cnt++;
            }
        }
    }
    printf("]\n");
}

#endif /* BINARY_TREE_H */
