#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *partition(struct ListNode *head, int x) {
    if (head) {
        struct ListNode *cur = head, *tail, *head1, *tail1;
        if (head->val < x) {
            while (cur->val < x) {
                tail = cur;
                cur = cur->next;
                if (!cur) {
                    return head;
                }
            }
            head1 = cur;
            tail1 = cur;
        } else {
            head1 = head;
            while (cur->val >= x) {
                tail1 = cur;
                cur = cur->next;
                if (!cur) {
                    return head;
                }
            }
            head = cur;
            tail = cur;
        }
        cur = cur->next;
        while (cur) {
            if (cur->val < x) {
                tail->next = cur;
                tail = cur;
            } else {
                tail1->next = cur;
                tail1 = cur;
            }
            cur = cur->next;
        }
        tail->next = head1;
        tail1->next = NULL;
    }
    return head;
}

int main() {
    struct TestCase {
        int vals[30], valsSize, x;
    } tc[] = {
        {.vals = {1,4,3,2,5,2}, .valsSize = 6, .x = 3},
        {.vals = {2,1}, .valsSize = 2, .x = 2}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *head;

    for (int i = 0; i < tcSize; i++) {
        // Create list
        head = createList(tc[i].vals, tc[i].valsSize);

        // Input
        printf("Example %d:\n", i + 1);
        printSinglyList(head, "Input: head");
        printf("x = %d\n", tc[i].x);

        // Output
        head = partition(head, tc[i].x);
        printSinglyList(head, "Output");
        printf("\n");

        // Free list nodes
        freeSinglyList(&head);
    }

    return 0;
}
