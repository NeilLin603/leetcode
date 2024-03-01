#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
static inline void travelToTail(struct ListNode **cur, int *rem) {
    while ((*cur)->next) {
        *cur = (*cur)->next;
        if (*rem) {
            if ((*cur)->val != 9) {
                (*cur)->val++;
                *rem = 0;
            } else {
                (*cur)->val = 0;
            }
        }
    }
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *head = l1;
    int rem = 0;
    for (;;) {
        l1->val += l2->val + rem;
        if (l1->val >= 10) {
            l1->val -= 10;
            rem = 1;
        } else {
            rem = 0;
        }
        if (!(l1->next && l2->next)) {
            break;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    travelToTail(&l1, &rem);
    l1->next = l2->next;
    travelToTail(&l1, &rem);
    if (rem) {
        struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
        new->val = 1;
        new->next = (struct ListNode *)NULL;
        l1->next = new;
    }
    return head;
}

int main() {
    struct TestCase {
        int vals1[100], vals1Size, vals2[100], vals2Size;
    } tc[] = {
        {.vals1 = {2,4,3}, .vals1Size = 3, .vals2 = {5,6,4}, .vals2Size = 3},
        {.vals1 = {0}, .vals1Size = 1, .vals2 = {0}, .vals2Size = 1},
        {.vals1 = {9,9,9,9,9,9,9}, .vals1Size = 7, .vals2 = {9,9,9,9}, .vals2Size = 4},
        {.vals1 = {0}, .vals1Size = 1, .vals2 = {7,3}, .vals2Size = 2}};
    int tcSize = sizeof(tc) / sizeof(tc[0]), tmp;

    Node_t *l1, *l2;
    for (int i = 0; i < tcSize; i++) {
        // Create l1 & l2
        l1 = (Node_t *)NULL;
        l2 = (Node_t *)NULL;
        for (int j = 0; j < tc[i].vals1Size; j++) {
            pushTail(&l1, tc[i].vals1[j]);
        }
        for (int j = 0; j < tc[i].vals2Size; j++) {
            pushTail(&l2, tc[i].vals2[j]);
        }

        // Functional test
        printf("Example %d:\nInput:\n", i + 1);
        printSinglyList(l1, "l1");
        printSinglyList(l2, "l2");
        printSinglyList(addTwoNumbers(l1, l2), "Output");
        printf("\n");

        // Free lists
        while (l1 != l2) {
            popHead(&l1, &tmp);
            popHead(&l2, &tmp);
        }
        while (popHead(&l1, &tmp));
    }

    return 0;
}
