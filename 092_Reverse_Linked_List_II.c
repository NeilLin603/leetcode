#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    right -= left;
    struct ListNode *pre = NULL, *cur = head;

    // Find the start node to be reversed
    while (--left) {
        pre = cur;
        cur = cur->next;
    }

    // Reverse nodes
    struct ListNode *ret = cur, *next = cur->next, *next2;
    while (right--) {
        next2 = next->next;
        next->next = cur;
        cur = next;
        next = next2;
    }

    // Combine the node which are not reversed
    ret->next = next;
    if (pre) {
        pre->next = cur;
        return head;
    }
    return cur;
}

int main() {
    struct {
        int vals[10], valsSize, left, right;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5, .left = 2, .right = 4},
        {.vals = {5}, .valsSize = 1, .left = 1, .right = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        
        // Create lists
        head = createList(tc[i].vals, tc[i].valsSize);
        printList(head, "Input: head");
        printf("       left = %d, right = %d\n", tc[i].left, tc[i].right);

        // Reverse list between left & right
        head = reverseBetween(head, tc[i].left, tc[i].right);
        printList(head, "Output");
        printf("\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
