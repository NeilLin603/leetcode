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
    struct Node *copy = copyList(head), *cur1 = head, *cur2 = copy, *rand;
    int idx = 0;
    do {
        rand = head;
        while (cur1->random != rand) {
            rand = rand->next;
            idx++;
        }
        rand = copy;
        while (idx) {
            rand = rand->next;
            idx--;
        }
        cur2->random = rand;
        cur1 = cur1->next;
        cur2 = cur2->next;
    } while (cur1);
    return copy;
}
