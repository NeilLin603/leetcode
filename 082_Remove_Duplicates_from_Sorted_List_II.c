#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *deleteDuplicates(struct ListNode *head) {
    if (head && head->next) {
        struct ListNode *cur = head->next;
        while (head->val == cur->val) {
            do {
                free(head);
                head = cur;
                cur = cur->next;
                if (!cur) {
                    return NULL;
                }
            } while (head->val == cur->val);
            free(head);
            head = cur;
            cur = cur->next;
            if (!cur) {
                return head;
            }
        }
        struct ListNode *prv = head, *next = cur->next;
        while (next) {
            while (cur->val == next->val) {
                do {
                    free(cur);
                    cur = next;
                    next = cur->next;
                    if (!next) {
                        prv->next = NULL;
                        return head;
                    }
                } while (cur->val == next->val);
                free(cur);
                cur = next;
                next = cur->next;
                prv->next = cur;
                if (!next) {
                    return head;
                }
            }
            prv = cur;
            cur = next;
            next = cur->next;
        }
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
