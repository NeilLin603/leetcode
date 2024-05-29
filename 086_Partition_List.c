#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *partition(struct ListNode *head, int x) {
    if (!head) {
        return NULL;
    }

    // Search the head nodes for two partitions
    struct ListNode *l1, *l2, *t1, *t2; 
    if (head->val < x) {
        l1 = head;
        do {
            t1 = head;
            head = head->next;
            if (!head) {
                return l1;
            }
        } while (head->val < x);
        l2 = t2 = head;
    } else {
        l2 = head;
        do {
            t2 = head;
            head = head->next;
            if (!head) {
                return l2;
            }
        } while (head->val >= x);
        l1 = t1 = head;
    }

    // Distribute the other nodes for two partitions
    while (head->next) {
        head = head->next;
        if (head->val < x) {
            t1 = t1->next = head;
        } else {
            t2 = t2->next = head;
        }
    }

    // Combine the two partitions
    t1->next = l2;
    t2->next = NULL;
    return l1;
}

int main() {
    struct {
        int vals[10], valsSize, x;
    } tc[] = {
        {.vals = {1,4,3,2,5,2}, .valsSize = 6, .x = 3},
        {.vals = {2,1}, .valsSize = 2, .x = 2},
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        head = createList(tc[i].vals, tc[i].valsSize);
        printList(head, "Input: head");
        printf("x = %d\n", tc[i].x);

        // Output
        head = partition(head, tc[i].x);
        printList(head, "Output");
        printf("\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
