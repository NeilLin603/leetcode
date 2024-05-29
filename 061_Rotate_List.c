#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *rotateRight(struct ListNode *head, int k) {
    if (head) {
        // Travel to the tail of the list
        int n = 1;
        struct ListNode *tail = head;
        while (tail->next) {
            n++;
            tail = tail->next;
        }
        tail->next = head; // Concatenate tail & head nodes

        // Find the break point
        k = n - k % n;
        while (k--) {
            tail = tail->next;
        }
        head = tail->next;
        tail->next = NULL;
    }
    return head;
}

int main() {
    struct {
        int vals[10], valsSize, k;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5, .k = 2},
        {.vals = {0,1,2}, .valsSize = 3, .k = 4}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        head = createList(tc[i].vals, tc[i].valsSize);
        printList(head, "Input: head");
        printf("k = %d\n", tc[i].k);

        // Output
        head = rotateRight(head, tc[i].k);
        printList(head, "Output");
        printf("\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
