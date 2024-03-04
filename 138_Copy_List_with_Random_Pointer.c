#include "linked_list_basic.h"

/**
 * Definition for a Node.
 */
struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

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
