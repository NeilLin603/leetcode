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
    struct ListNode *cur = head, *ret1 = NULL;
    while (--left) {
        ret1 = cur;
        cur = cur->next;
    }
    struct ListNode *tmp, *ret2 = cur->next;
    while (right--) {
        tmp = ret2;
        ret2 = ret2->next;
        tmp->next = cur;
        cur = tmp;
    }
    if (ret1) {
        ret1->next->next = ret2;
        ret1->next = cur;
        return head;
    }
    head->next = ret2;
    return cur;
}

int main() {
    struct TestCase {
        int vals[500], valsSize, left, right;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5, .left = 2, .right = 4},
        {.vals = {5}, .valsSize = 1, .left = 1, .right = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *head;

    for (int i = 0; i < tcSize; i++) {
        // Create list
        head = createList(tc[i].vals, tc[i].valsSize);

        // Input
        printf("Example %d:\n", i + 1);
        printSinglyList(head, "Input: head");
        printf("left = %d, right = %d\n", tc[i].left, tc[i].right);

        // Output
        head = reverseBetween(head, tc[i].left, tc[i].right);
        printSinglyList(head, "Output");
        printf("\n");

        // Free list nodes
        freeSinglyList(&head);
    }

    return 0;
}
