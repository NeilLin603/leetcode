#include <stdio.h>
#include <stdlib.h>

#define NULL_NODE 0x80000000

/**
 * Definition for a Node.
 */
struct Node {
    int val;
    struct Node *left, *right, *next;
};

//
// Start of the submission code
//
typedef struct Node Node_t;

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

Node_t *dequeue(Queue_t *q, int *const cnt) {
    QNode_t *temp = q->head;
    Node_t *ret = temp->node;
    q->head = temp->next;
    free(temp);

    if (ret->left) {
        enqueue(q, ret->left);
        (*cnt)++;
    }
    if (ret->right) {
        enqueue(q, ret->right);
        (*cnt)++;
    }
    return ret;
}

Node_t *connect(Node_t *root) {
    if (root) {
        Queue_t *q = initqueue();
        enqueue(q, root);
        int curLevelCnt = 0, nextLevelCnt = 1;

        Node_t *node;
        while (nextLevelCnt) {
            curLevelCnt = nextLevelCnt;
            nextLevelCnt = 0;

            node = dequeue(q, &nextLevelCnt);
            while (--curLevelCnt) {
                node->next = dequeue(q, &nextLevelCnt);
                node = node->next;
            }
            node->next = NULL;
        }
        free(q);
    }
    return root;
}
//
// End of the submission code
//

int dequeue2(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *ret = q->head;
    *node = ret->node;
    q->head = ret->next ? ret->next : (q->tail = NULL);
    free(ret);
    return 1;
}

Node_t *addNode(Queue_t *q, int val) {
    if (val == NULL_NODE) {
        return NULL;
    }
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    node->val = val;
    enqueue(q, node);
    return node;
}

Node_t *buildTree(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Queue_t *q = initqueue();
    Node_t *root = addNode(q, *vals), *node;
    while (--valsSize) {
        dequeue2(q, &node);
        node->next = NULL;
        node->left = addNode(q, *++vals);
        if (!--valsSize) {
            node->right = NULL;
            break;
        }
        node->right = addNode(q, *++vals);
    }
    while (dequeue2(q, &node)) {
        node->next = node->left = node->right = NULL;
    }
    free(q);
    return root;
}

void printTree(Node_t *root, char *name) {
    if (!root) {
        printf("%s = []\n");
        return;
    }
    printf("%s = [", name);
    Queue_t *q = initqueue();
    enqueue(q, root);
    int nullCnt = 0;
    while (dequeue2(q, &root)) {
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
    printf("\b]\n");
    free(q);
}

void printOutput(Node_t *root, char *name) {
    printf("%s: [");
    if (!root) {
        printf("]\n\n");
        return;
    }
    Node_t *head = root, *cur;
    while (head) {
        cur = head;
        head = NULL;
        while (cur) {
            if (!head && cur->left) {
                head = cur->left;
            }
            if (!head && cur->right) {
                head = cur->right;
            }
            printf("%d,", cur->val);
            cur = cur->next;
        }
        printf("#,");
    }
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

int main() {
    struct {
        int vals[16], valsSize;
    } tc[] = {
        {.vals = {1, 2, 3, 4, 5, NULL_NODE, 7}, .valsSize = 7},
        {.valsSize = 0}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        root = buildTree(tc[i].vals, tc[i].valsSize);
        printTree(root, "Input: root");

        // Output
        root = connect(root);
        printOutput(root, "Output");

        // Free tree
        freeTree(&root);
    }

    return 0;
}
