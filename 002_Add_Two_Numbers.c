#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *ret = l1;
    int ovf = 0;
    for (;;) {
        l1->val += l2->val + ovf;
        if (l1->val >= 10) {
            l1->val -= 10;
            ovf = 1;
        } else {
            ovf = 0;
        }
        if (!l2->next) {
            break;
        }
        if (!l1->next) {
            l1->next = l2->next;
            break;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    while (ovf) {
        if (!l1->next) {
            l1->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            l1->next->val = 1;
            l1->next->next = NULL;
            break;
        }
        l1 = l1->next;
        if (l1->val != 9) {
            l1->val++;
            break;
        }
        l1->val = 0;
    }
    return ret;
}

int main() {
    struct {
        int vals1[10], vals1Size, vals2[10], vals2Size;
    } tc[] = {
        {.vals1 = {2,4,3}, .vals1Size = 3, .vals2 = {5,6,4}, .vals2Size = 3},
        {.vals1 = {0}, .vals1Size = 1, .vals2 = {0}, .vals2Size = 1},
        {.vals1 = {9,9,9,9,9,9,9}, .vals1Size = 7, .vals2 = {9,9,9,9}, .vals2Size = 4}};
    int tcSize = sizeof(tc) / sizeof(tc[0]), tmp;

    Node_t *l1, *l2;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        
        // Create lists
        l1 = createList(tc[i].vals1, tc[i].vals1Size);
        l2 = createList(tc[i].vals2, tc[i].vals2Size);
        printList(l1, "l1");
        printList(l2, "l2");

        // Add two lists
        printList(addTwoNumbers(l1, l2), "Output");
        printf("\n");

        // Free lists
        while (l1 != l2) {
            popHead(&l1, &tmp);
            popHead(&l2, &tmp);
        }
        freeList(&l1);
        // while (popHead(&l1, &tmp));
    }

    return 0;
}
