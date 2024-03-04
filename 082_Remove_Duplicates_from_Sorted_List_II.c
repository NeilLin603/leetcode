#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *deleteDuplicates(struct ListNode *head) {
    if (!(head && head->next)) {
        return head;
    }
    Node_t *cur = head->next;
    int val;
    while (head->val == cur->val) {
        val = cur->val;
        while (val == head->val) {
            free(head);
            head = cur;
            cur = cur->next;
        }
    }
    Node_t *prv, *ret;
    while (cur->next) {
        prv = cur;
        cur = cur->next;
        while (cur->next && cur->val == cur->next->val) {
            val = cur->val;
            while (val == cur->val) {
                ret = cur->next;
                free(cur);
                cur = ret;
            }
        }
        prv->next = cur;
    }
    return head;
}

int main() {
    struct TestCase {
        int vals[30], valsSize;
    } tc[] = {
        {.vals = {1,2,3,3,4,4,5}, .valsSize = 7},
        {.vals = {1,1,1,2,3}, .valsSize = 5}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *head;

    for (int i = 0; i < tcSize; i++) {
        // Create list
        head = createList(tc[i].vals, tc[i].valsSize);

        // Input
        printf("Example %d:\n", i + 1);
        printSinglyList(head, "Input: head");

        // Output
        head = deleteDuplicates(head);
        printSinglyList(head, "Output");
        printf("\n");

        // Free list nodes
        freeSinglyList(&head);
    }

    return 0;
}
