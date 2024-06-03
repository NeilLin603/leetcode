#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *merge(struct ListNode *list1, struct ListNode *list2) {
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }
    if (list1->val < list2->val) {
        list1->next = merge(list1->next, list2);
        return list1;
    }
    list2->next = merge(list1, list2->next);
    return list2;
}

struct ListNode *sortList(struct ListNode *head) {
    if (!head || !head->next) {
        return head;
    }
    struct ListNode *slow = head, *fast = head->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    head = sortList(head);
    fast = sortList(fast);
    return merge(head, fast);
}

int main() {
    struct {
        int nums[16], numsSize;
    } tc[] = {
        {.nums = {4,2,1,3}, .numsSize = 4},
        {.nums = {-1,5,3,4,0}, .numsSize = 5},
        {.numsSize = 0}
    };
    int tcSize = sizeof(tc) / sizeof(*tc);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        head = createList(tc[i].nums, tc[i].numsSize);
        printList(head, "Input: head");

        // Output
        head = sortList(head);
        printList(head, "\nOutput");
        printf("\n\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
