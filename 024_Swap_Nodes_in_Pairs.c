#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! The submission code
//!*****************************************************************************
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

#define SWAP(a, b)                                                             \
    a ^= b;                                                                    \
    b ^= a;                                                                    \
    a ^= b

struct ListNode *swapPairs(struct ListNode *head) {
    if (head && head->next) {
        SWAP(head->val, head->next->val);
        head->next->next = swapPairs(head->next->next);
    }
    return head;
}

//!*****************************************************************************
//! General funcs for linked list
//!*****************************************************************************
typedef struct ListNode Node_t;

Node_t *createList(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    Node_t *head = (Node_t *)malloc(sizeof(Node_t));
    head->val = *nums;
    head->next = createList(nums + 1, numsSize - 1);
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

//!*****************************************************************************
//! Main function
//!*****************************************************************************
int main() {
    struct {
        int nums[10], numsSize;
    } tc[] = {
        {.nums = {1,2,3,4}, .numsSize = 4},
        {.numsSize = 0},
        {.nums = {1}, .numsSize = 1},
        {.nums = {1,2,3}, .numsSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        head = createList(tc[i].nums, tc[i].numsSize);
        printList(head, "Input: head =");

        // Output
        head = swapPairs(head);
        printList(head, "Output:");
        printf("\n");

        // Free list
        freeList(head);
    }

    return 0;
}
