#include "linked_list_basic.h"

/**
 * Definition for a Node.
 */
struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

#if 1 /* Solution 1 */
static inline struct Node *copyList(struct Node *head) {
    struct Node *copy = (struct Node *)malloc(sizeof(struct Node)), *new = copy;
    new->val = head->val;
    while (head->next) {
        head = head->next;
        new->next = (struct Node *)malloc(sizeof(struct Node));
        new = new->next;
        new->val = head->val;
    }
    new->next = NULL;
    return copy;
}

struct Node *copyRandomList(struct Node *head) {
    if (!head) {
        return NULL;
    }
    struct Node *copy = copyList(head), *cur1 = head, *cur2 = copy, *rnd;
    int idx = 0;
    do {
        rnd = head;
        cur2->random = copy;
        while (cur1->random != rnd) {
            rnd = rnd->next;
            cur2->random = cur2->random->next;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    } while (cur1);
    return copy;
}
#else /* Solution 2 */
struct Node *randNode(struct Node *head, struct Node *cur, struct Node *copy) {
    while (cur->random != head) {
        head = head->next;
        copy = copy->next;
    }
    return copy;
}

struct Node *copyRandomList(struct Node *head) {
    if (!head) {
        return NULL;
    }

    struct Node *copy = (struct Node *)malloc(sizeof(struct Node));
    copy->val = head->val;
    struct Node *cur1 = head->next, *cur2 = copy;
    while (cur1) {
        cur2->next = (struct Node *)malloc(sizeof(struct Node));
        cur2 = cur2->next;
        cur2->val = cur1->val;
        cur1 = cur1->next;
    }
    cur2->next = NULL;

    cur1 = head;
    cur2 = copy;
    while (cur1) {
        cur2->random = randNode(head, cur1, copy);
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return copy;
}
#endif
