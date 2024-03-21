#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node_t;

static inline void addNode(Node_t **head, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = *head;
    *head = new;
}

static inline int popNode(Node_t **head) {
    Node_t *ret = *head;
    *head = ret->next;
    int val = ret->val;
    free(ret);
    return val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lastVisitedIntegers(int *nums, int numsSize, int *returnSize) {
    Node_t *seen = NULL, *cur = NULL, *ans = NULL;
    int ansSize = 0;
    while (numsSize--) {
        if (*nums != -1) {
            addNode(&seen, *nums);
            cur = seen;
        } else {
            if (cur) {
                addNode(&ans, cur->val);
                cur = cur->next;
            } else {
                addNode(&ans, -1);
            }
            ansSize++;
        }
        nums++;
    }

    // Free list "seen"
    while (seen) {
        cur = seen;
        seen = cur->next;
        free(cur);
    }

    // Convert list "ans" to array
    int *result = (int *)malloc(sizeof(int) * ansSize);
    *returnSize = ansSize;
    while (ansSize--) {
        result[ansSize] = popNode(&ans);
    }
    return result;
}

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]\n");
}

int main() {
    struct TestCase {
        int nums[5], numsSize;
    } tc[] = {
        {.nums = {1,2,-1,-1,-1}, .numsSize = 5},
        {.nums = {1,-1,2,-1,-1}, .numsSize = 5}};
    int tcSize = sizeof(tc) / sizeof(tc[0]), *ans, returnSize;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        ans = lastVisitedIntegers(tc[i].nums, tc[i].numsSize, &returnSize);
        printArray(ans, returnSize, "Output");
        printf("\n");
        free(ans);
    }

    return 0;
}
