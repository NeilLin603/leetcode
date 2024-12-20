#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
static inline int sizeOfList(struct ListNode *head) {
    int result = 0;
    while (head) {
        head = head->next;
        result++;
    }
    return result;
}

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    n = sizeOfList(head) - n;
    struct ListNode *cur = head, *prev = NULL;
    while (n--) {
        prev = cur;
        cur = cur->next;
    }
    struct ListNode *next = cur->next;
    free(cur);
    if (prev) {
        prev->next = next;
        return head;
    }
    return next;
}

int main() {
    struct {
        int vals[5], valsSize, n;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5, .n = 2},
        {.vals = {1}, .valsSize = 1, .n = 1},
        {.vals = {1,2}, .valsSize = 2, .n = 1}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Create list
        head = createList(tc[i].vals, tc[i].valsSize);
        printList(head, "Input: head");
        printf("n = %d\n", tc[i].n);

        // Remove the target node
        head = removeNthFromEnd(head, tc[i].n);
        printList(head, "Output");
        printf("\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
