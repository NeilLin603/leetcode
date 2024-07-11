#include <stdio.h>
#include <stdlib.h>

#define NULL_NODE 0x80000000

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

//
//----------------- Submission code start -----------------
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
    QNode_t *in = (QNode_t *)malloc(sizeof(QNode_t));
    in->node = node;
    in->next = NULL;
    q->tail = q->head ? (q->tail->next = in) : (q->head = in);
}

Node_t *dequeue(Queue_t *q) {
    QNode_t *out = q->head;
    Node_t *ret = out->node;
    q->head = out->next;
    free(out);
    if (!q->head) {
        q->tail = NULL;
    }
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *averageOfLevels(Node_t *root, int *returnSize) {
    // Create a queue and put the root node into queue
    Queue_t *q = initqueue();
    enqueue(q, root);

    // Initialize counters for counting the total nodes of the current level and
    // the next level
    int currentLevelCount = 0, nextLevelCount = 1;
    double nodeCount;

    // Initialize the return array and the return size
    double *ret = NULL;
    *returnSize = 0;

    // Loop while there're stil nodes in the next level
    while (nextLevelCount) {
        // Shift the level to the next
        currentLevelCount = nextLevelCount;
        nodeCount = (double)nextLevelCount;
        nextLevelCount = 0;

        // Reallocate the return array
        ret = (double *)realloc(ret, sizeof(double) * ++*returnSize);
        ret[*returnSize - 1] = 0.0;

        // Compute the average value of the current level nodes
        while (currentLevelCount--) {
            root = dequeue(q);
            ret[*returnSize - 1] += (double)root->val;
            if (root->left) {
                enqueue(q, root->left);
                nextLevelCount++;
            }
            if (root->right) {
                enqueue(q, root->right);
                nextLevelCount++;
            }
        }
        ret[*returnSize - 1] /= nodeCount;
    }

    // Free the queue and return
    free(q);
    return ret;
}
//
//----------------- Submission code end -----------------
//

int dequeue2(Queue_t *q, Node_t **node) {
    if (q->head) {
        *node = dequeue(q);
        return 1;
    }
    return 0;
}

Node_t *buildTree(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Node_t *root = (Node_t *)malloc(sizeof(Node_t)), *node;
    root->val = *vals;
    Queue_t *q = initqueue();
    enqueue(q, root);
    while (--valsSize) {
        node = dequeue(q);
        if (*++vals != NULL_NODE) {
            node->left = (Node_t *)malloc(sizeof(Node_t));
            node->left->val = *vals;
            enqueue(q, node->left);
        } else {
            node->left = NULL;
        }
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        if (*++vals != NULL_NODE) {
            node->right = (Node_t *)malloc(sizeof(Node_t));
            node->right->val = *vals;
            enqueue(q, node->right);
        } else {
            node->right = NULL;
        }
    }
    while (dequeue2(q, &node)) {
        node->left = node->right = NULL;
    }
    free(q);
    return root;
}

void freeTree(Node_t **root) {
    if (*root) {
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    Queue_t *q = initqueue();
    enqueue(q, root);
    int nullCount = 0;
    while (dequeue2(q, &root)) {
        if (root) {
            while (nullCount) {
                printf("null,");
                nullCount--;
            }
            printf("%d,", root->val);
            enqueue(q, root->left);
            enqueue(q, root->right);
        } else {
            nullCount++;
        }
    }
    free(q);
    printf("\b]\n");
}

void printArray(double *nums, int numsSize, char *name) {
    printf("%s: [", name);
    if (numsSize) {
        printf("%.5f", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%.5f", nums[i]);
        }
    }
    printf("]\n\n");
}

int main() {
    struct {
        int vals[10], valsSize;
    } tc[] = {
        {.vals = {3, 9, 20, NULL_NODE, NULL_NODE, 15, 7}, .valsSize = 7},
        {.vals = {3, 9, 20, 15, 7}, .valsSize = 5}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    double *out;
    int outSize;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        Node_t *root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        out = averageOfLevels(root, &outSize);
        printArray(out, outSize, "Output");

        // Free memory
        free(root);
        free(out);
    }
    return 0;
}
