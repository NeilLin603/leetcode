#include "linked_list_basic.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    if (head) {
        struct ListNode *traveler1 = head, *traveler2 = head;
        while (traveler2->next && traveler2->next->next) {
            traveler1 = traveler1->next;
            traveler2 = traveler2->next->next;
            if (traveler1 == traveler2) {
                return true;
            }
        }
    }
    return false;
}

Node_t *createList(int *vals, int valsSize, int pos) {
    Node_t *head = (Node_t *)NULL;
    if (pos > -1 && pos < valsSize) {
        pushHead(&head, vals[0]);
        Node_t *cur = head, *tail = head;
        for (int i = 1; i < valsSize; i++) {
            pushTail(&head, vals[i]);
            if (pos-- > 0) {
                cur = cur->next;
            }
            tail = tail->next;
        }
        tail->next = cur;
    } else {
        for (int i = 0; i < valsSize; i++) {
            pushTail(&head, vals[i]);
        }
    }
    return head;
}

int main() {
    struct TestCase {
        int vals[4], valsSize, pos;
    } tc[] = {
        {.vals = {3,2,0,-4}, .valsSize = 4, .pos = 1},
        {.vals = {1,2}, .valsSize = 2, .pos = 0},
        {.vals = {1}, .valsSize = 1, .pos = -1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]), tmp;
    Node_t *head, *cur;

    for (int i = 0; i < tcSize; i++) {
        head = createList(tc[i].vals, tc[i].valsSize, tc[i].pos);
        cur = head;
        printf("Example %d:\n", i + 1);
        printf("Input: head = [%d", head->val);
        for (int j = 1; j < tc[i].valsSize; j++) {
            cur = cur->next;
            printf(",%d", cur->val);
        }
        printf("], pos = %d\n", tc[i].pos);
        if (hasCycle(head)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }

        // Free list
        for (int i = 0; i < tc[i].valsSize; i++) {
            popHead(&head, &tmp);
        }
    }

    return 0;
}
