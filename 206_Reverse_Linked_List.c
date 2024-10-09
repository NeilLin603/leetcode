#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

#if 0 /* Iteration */
struct ListNode *reverseList(struct ListNode *head) {
    struct ListNode *pre = NULL, *next;
    while (head) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}
#else /* Recursion */
struct ListNode *reverseList(struct ListNode *head) {
    if (head && head->next) {
        struct ListNode *newHead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
    return head;
}
#endif

typedef struct ListNode Node_t;

Node_t *createList(int *vals, int valsSize) {
    Node_t *head = NULL;
    if (valsSize) {
        head = (Node_t *)malloc(sizeof(Node_t));
        head->val = *vals;
        head->next = createList(vals + 1, valsSize - 1);
    }
    return head;
}

void printList(Node_t *head, const char *title) {
    printf("%s [", title);
    if (head) {
        printf("%d", head->val);
        while (head->next) {
            head = head->next;
            printf(",%d", head->val);
        }
    }
    printf("]\n");
}

void freeList(Node_t *head) {
    if (head) {
        freeList(head->next);
        free(head);
    }
}

int main() {
    struct {
        int vals[5], valsSize;
    } tc[] = {
        {.vals = {1,2,3,4,5}, .valsSize = 5},
        {.vals = {1,2}, .valsSize = 2}
    };

    int tcSize = sizeof(tc) / sizeof(tc[0]);
    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Create a singly-linked list
        head = createList(tc[i].vals, tc[i].valsSize);

        // Input
        printList(head, "Input: head =");

        // Output
        head = reverseList(head);
        printList(head, "Output:");
        printf("\n");

        // Free list
        freeList(head);
    }

    return 0;
}
