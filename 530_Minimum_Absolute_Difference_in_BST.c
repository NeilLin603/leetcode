#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} Node_t;

//
// Start of the submission code
//
#if 0 /* Method 1: time complexity = O(n^2) */
#define MAX_DIFFERENCE 0x7fffffff
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int maxValueOfBst(struct TreeNode *root) {
    return root->right ? maxValueOfBst(root->right) : root->val;
}

static int minValueOfBst(struct TreeNode *root) {
    return root->left ? minValueOfBst(root->left) : root->val;
}

int getMinimumDifference(struct TreeNode *root) {
    int a, b, minL = MAX_DIFFERENCE, minR = MAX_DIFFERENCE;
    if (root->left) {
        a = root->val - maxValueOfBst(root->left);
        b = getMinimumDifference(root->left);
        minL = MIN(a, b);
    }
    if (root->right) {
        a = minValueOfBst(root->right) - root->val;
        b = getMinimumDifference(root->right);
        minR = MIN(a, b);
    }
    return MIN(minL, minR);
}
#else /* Method 2: time complexity = O(n) */
typedef struct QueueNode {
    int val;
    struct QueueNode *next;
} QNode_t;

typedef struct {
    QNode_t *head;
    QNode_t *tail;
} Queue_t;

static Queue_t *initqueue() {
    Queue_t *q = (Queue_t *)malloc(sizeof(Queue_t));
    q->head = q->tail = NULL;
    return q;
}

static void enqueue(Queue_t *q, int val) {
    QNode_t *new = (QNode_t *)malloc(sizeof(QNode_t));
    new->val = val;
    new->next = NULL;
    q->tail = q->tail ? (q->tail->next = new) : (q->head = new);
}

static int dequeue(Queue_t *q, int *val) {
    if (q->head) {
        QNode_t *ret = q->head;
        *val = ret->val;
        q->head = ret->next ? ret->next : (q->tail = NULL);
        return 1;
    }
    return 0;
}

static void inorderTraverse(Queue_t *q, struct TreeNode *root) {
    if (root) {
        inorderTraverse(q, root->left);
        enqueue(q, root->val);
        inorderTraverse(q, root->right);
    }
}

int getMinimumDifference(struct TreeNode *root) {
    Queue_t *q = initqueue();
    inorderTraverse(q, root);
    int pre, cur;
    dequeue(q, &cur);
    dequeue(q, &pre);
    int min = pre - cur;
    while (dequeue(q, &cur)) {
        if (min > cur - pre) {
            min = cur - pre;
        }
        pre = cur;
    }
    free(q);
    return min;
}
#endif
//
// End of the submission code
//

#define NULL_NODE -1

typedef struct QueueNode2 {
    Node_t *node;
    struct QueueNode2 *next;
} QNode2_t;

typedef struct {
    QNode2_t *head;
    QNode2_t *tail;
} Queue2_t;

Queue2_t *initqueue2() {
    Queue2_t *q = (Queue2_t *)malloc(sizeof(Queue2_t));
    q->head = q->tail = NULL;
    return q;
}

void enqueue2(Queue2_t *q, Node_t *node) {
    QNode2_t *new = (QNode2_t *)malloc(sizeof(QNode2_t));
    new->node = node;
    new->next = NULL;
    q->tail = q->head ? (q->tail->next = new) : (q->head = new);
}

int dequeue2(Queue2_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode2_t *temp = q->head;
    *node = temp->node;
    q->head = temp->next ? temp->next : (q->tail = NULL);
    free(temp);
    return 1;
}

static Node_t *addNode(Queue2_t *q, int val) {
    Node_t *ret = (Node_t *)malloc(sizeof(Node_t));
    ret->val = val;
    enqueue2(q, ret);
    return ret;
}

Node_t *buildTree(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Node_t *root = (Node_t *)malloc(sizeof(Node_t)), *node;
    root->val = *vals;
    Queue2_t *q = initqueue2();
    enqueue2(q, root);
    while (--valsSize) {
        dequeue2(q, &node);
        node->left = *++vals != NULL_NODE ? addNode(q, *vals) : NULL;
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        node->right = *++vals != NULL_NODE ? addNode(q, *vals) : NULL;
    }
    while (dequeue2(q, &node)) {
        node->left = node->right = NULL;
    }
    free(q);
    return root;
}

void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    Queue2_t *q = initqueue2();
    enqueue2(q, root);
    int nullCnt = 0;
    while (dequeue2(q, &root)) {
        if (root) {
            while (nullCnt) {
                printf("null,");
                nullCnt--;
            }
            printf("%d,", root->val);
            enqueue2(q, root->left);
            enqueue2(q, root->right);
        } else {
            nullCnt++;
        }
    }
    free(q);
    printf("\b]\n");
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
        int vals[32], valsSize;
    } tc[] = {
        {.vals = {4, 2, 6, 1, 3}, .valsSize = 5},
        {.vals = {1, 0, 48, NULL_NODE, NULL_NODE, 12, 49}, .valsSize = 7},
        {.vals = {236, 104, 701, NULL_NODE, 227, NULL_NODE, 911}, .valsSize = 7}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        printf("Output: %d\n\n", getMinimumDifference(root));

        // Free tree
        freeTree(&root);
    }

    return 0;
}
