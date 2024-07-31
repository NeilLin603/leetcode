#include <stdio.h>
#include <stdlib.h>

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

Node_t *dequeue(Queue_t *q) {
    QNode_t *tmp = q->head;
    Node_t *ret = tmp->node;
    q->head = tmp->next ? tmp->next : (q->tail = NULL);
    free(tmp);
    return ret;
}

#define ADD_CHILD_NODE(q, child, cnt) if ((child)) { \
    enqueue((q), (child));                           \
    (cnt)++;                                         \
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **levelOrder(Node_t *root, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (!root) {
        return NULL;
    }

    int **ret = NULL, *curLevel = NULL, curLevelCnt = 0, nextLevelCnt = 1;
    Queue_t *q = initqueue();
    enqueue(q, root);
    while (nextLevelCnt) {
        // Inherit the node count of the next level
        curLevelCnt = nextLevelCnt;
        nextLevelCnt = 0;

        // Update the returned array size variables
        (*returnSize)++;
        *returnColumnSizes = (int *)realloc(*returnColumnSizes,
                                            sizeof(int) * *returnSize);
        *(*returnColumnSizes + *returnSize - 1) = curLevelCnt;

        // Allocate memory to store the current level nodes
        ret = (int **)realloc(ret, sizeof(int *) * *returnSize);
        *(ret + *returnSize - 1) = (int *)malloc(sizeof(int) * curLevelCnt);

        // Dequeue nodes for current level, enqueue nodes for the next level,
        // and update the returned array
        for (int i = 0; i < curLevelCnt; i++) {
            root = dequeue(q);
            *(*(ret + *returnSize - 1) + i) = root->val;
            ADD_CHILD_NODE(q, root->left, nextLevelCnt);
            ADD_CHILD_NODE(q, root->right, nextLevelCnt);
        }
    }
    free(q);
    return ret;
}
//
// End of the submission code
//

int dequeue2(Queue_t *q, Node_t **node) {
    if (q->head) {
        *node = dequeue(q);
        return 1;
    }
    return 0;
}

#define NULL_NODE 0x80000000

#define ADD_NODE(q, node, vals) if (*++(vals) != NULL_NODE) { \
    (node) = (Node_t *)malloc(sizeof(Node_t));                \
    (node)->val = *(vals);                                    \
    enqueue((q), (node));                                     \
} else {                                                      \
    (node) = NULL;                                            \
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
        ADD_NODE(q, node->left, vals)
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        ADD_NODE(q, node->right, vals)
    }
    while (dequeue2(q, &node)) {
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
        while (dequeue2(q, &root)) {
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

void printArray(int *nums, int numsSize) {
    printf("[");
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", *(nums + i));
        }
    }
    printf("]");
}

void print2DArray(int **nums, int rowSize, int *colSize, char *name) {
    printf("%s :[", name);
    if (rowSize) {
        printArray(*nums, *colSize);
        while (--rowSize) {
            printf(",");
            printArray(*++nums, *++colSize);
        }
    }
    printf("]\n\n");
}

int main() {
    struct {
        int vals[8], valsSize;
    } tc[] = {
        {.vals = {3, 9, 20, NULL_NODE, NULL_NODE, 15, 7}, .valsSize = 7},
        {.vals = {1}, .valsSize = 1},
        {.valsSize = 0}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    int **out, returnSize, *returnColumnSizes;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        out = levelOrder(root, &returnSize, &returnColumnSizes);
        print2DArray(out, returnSize, returnColumnSizes, "Output");

        // Free memory
        freeTree(&root);
        for (int j = 0; j < returnSize; j++) {
            free(*(out + j));
        }
        free(out);
        free(returnColumnSizes);
    }

    return 0;
}
