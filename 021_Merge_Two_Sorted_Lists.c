#include "linked_list_basic.h"

#if 1 /* Loop approach */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }

    // Head node
    struct ListNode *head, *cur;
    if (list1->val < list2->val) {
        head = cur = list1;
    } else {
        head = cur = list2;
        list2 = list1;
    }

    // Others
    list1 = cur->next;
    while (list1) {
        if (list1->val < list2->val) {
            cur = list1;
            list1 = cur->next;
        } else {
            cur = cur->next = list2;
            list2 = list1;
            list1 = cur->next;
        }
    }
    cur->next = list2;
    return head;
}
#else /* Recursive approach */
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }
    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    list2->next = mergeTwoLists(list1, list2->next);
    return list2;
}
#endif

int main() {
    struct {
        int vals1[10], vals1Size, vals2[10], vals2Size;
    } tc[] = {
        {.vals1 = {1,2,4}, .vals1Size = 3, .vals2 = {1,3,4}, .vals2Size = 3},
        {.vals1Size = 0, .vals2Size = 0},
        {.vals1Size = 0, .vals2 = {0}, .vals2Size = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *list1, *list2, *list3;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        
        // Create lists
        list1 = createList(tc[i].vals1, tc[i].vals1Size);
        list2 = createList(tc[i].vals2, tc[i].vals2Size);
        printList(list1, "l1");
        printList(list2, "l2");

        // Merge two lists
        list3 = mergeTwoLists(list1, list2);
        printList(list3, "Output");
        printf("\n");

        // Free lists
        freeList(&list3);
    }

    return 0;
}
