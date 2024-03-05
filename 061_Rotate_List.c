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
        struct ListNode *cur = head;
        int n = 1;
        while (cur->next) {
            cur = cur->next;
            n++;
        }
        cur->next = head;
        k = n - k % n;
        while (k--) {
            cur = cur->next;
        }
        head = cur->next;
        cur->next = NULL;
    }
    return head;
}

int main() {
    struct TestCase {
        int vals[30], valsSize, k;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5, .k = 2},
        {.vals = {0,1,2}, .valsSize = 3, .k = 4}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *head;

    for (int i = 0; i < tcSize; i++) {
        // Create list
        head = createList(tc[i].vals, tc[i].valsSize);

        // Input
        printf("Example %d:\n", i + 1);
        printSinglyList(head, "Input: head");
        printf("k = %d\n", tc[i].k);

        // Output
        head = rotateRight(head, tc[i].k);
        printSinglyList(head, "Output");
        printf("\n");

        // Free list nodes
        freeSinglyList(&head);
    }

    return 0;
}
