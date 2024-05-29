#include "linked_list_basic.h"

//**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
static struct ListNode *deleteDuplicatesSub(struct ListNode *head) {
    if (!head->next) {
        return head;
    }
    int val;
    struct ListNode *ret;
    while (head->val == head->next->val) {
        val = head->val;
        do {
            ret = head;
            head = ret->next;
            free(ret);
            if (!head) {
                return NULL;
            }
        } while (val == head->val);
        if (!head->next) {
            return head;
        }
    }
    head->next = deleteDuplicatesSub(head->next);
    return head;
}

struct ListNode *deleteDuplicates(struct ListNode *head) {
    return head ? deleteDuplicatesSub(head) : NULL;
}

int main() {
    struct {
        int vals[10], valsSize;
    } tc[] = {
        {.vals = {1,2,3,3,4,4,5}, .valsSize = 7},
        {.vals = {1,1,1,2,3}, .valsSize = 5}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        head = createList(tc[i].vals, tc[i].valsSize);
        printList(head, "Input: head");

        // Output
        head = deleteDuplicates(head);
        printList(head, "Output");
        printf("\n");

        // Free list
        freeList(&head);
    }

    return 0;
}
