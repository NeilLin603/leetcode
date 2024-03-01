#include "linked_list_basic.h"

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
    struct ListNode *head;
    if (list1->val < list2->val) {
        head = list1;
        list1 = list1->next;
    } else {
        head = list2;
        list2 = list2->next;
    }

    // Others
    struct ListNode *cur = head;
    while (list1 && list2) {
        if (list1->val < list2->val) {
            cur->next = list1;
            list1 = list1->next;
        } else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }
    cur->next = list1 ? list1 : list2;
    return head;
}

int main() {
    struct TestCase {
        int vals1[50], vals1Size, vals2[50], vals2Size;
    } tc[] = {
        {.vals1 = {1,2,4}, .vals1Size = 3, .vals2 = {1,3,4}, .vals2Size = 3},
        {.vals1Size = 0, .vals2Size = 0},
        {.vals1Size = 0, .vals2 = {0}, .vals2Size = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *list1, *list2, *output;

    for (int i = 0; i < tcSize; i++) {
        // Create list1 & list2
        list1 = createList(tc[i].vals1, tc[i].vals1Size);
        list2 = createList(tc[i].vals2, tc[i].vals2Size);

        // Functional test
        printf("Example %d:\n", i + 1);
        printf("Input:\n");
        printSinglyList(list1, "list1");
        printSinglyList(list2, "list2");
        output = mergeTwoLists(list1, list2);
        printSinglyList(output, "Output");
        printf("\n");

        // Free list
        freeSinglyList(&output);
    }

    return 0;
}
