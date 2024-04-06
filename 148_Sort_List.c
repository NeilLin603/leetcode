#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

/**
 * Definition for singly-linked list.
 */
typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node_t;

struct ListNode* sortList(struct ListNode* head) {
    if (head) {
        struct ListNode *cur = head->next;
        while (cur) {
            if (cur->val < head->val) {
                SWAP(cur->val, head->val);
            }
            cur = cur->next;
        }
        sortList(head->next);
    }
    return head;
}

Node_t *createList(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    Node_t *head = (Node_t *)malloc(sizeof(Node_t));
    head->val = *nums;
    head->next = createList(nums + 1, numsSize - 1);
    return head;
}

void printList(Node_t *head, char *name) {
    printf("%s = ", name);
    while (head) {
        printf("(%d)->", head->val);
        head = head->next;
    }
    printf("null\n");
}

void freeList(Node_t **head) {
    Node_t *tmp;
    while (*head) {
        tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
}

int main() {
    struct {
        int nums[5], numsSize;
    } tc[] = {
        {.nums = {4,2,1,3}, .numsSize = 4},
        {.nums = {-1,5,3,4,0}, .numsSize = 5},
        {.numsSize = 0}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *head;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        head = createList(tc[i].nums, tc[i].numsSize);
        printList(head, "Input: head");

        head = sortList(head);
        printList(head, "Output");

        printf("\n");
        freeList(&head);
    }

    return 0;
}
