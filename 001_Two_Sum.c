#include <stdio.h>
#include <stdlib.h>

//!****************************************************************************
//! Strategy: Use chaining (linked list) approach to deal with hash collisions.
//!****************************************************************************
//
// Start of the submission code
//
typedef struct Node {
    int idx, val;
    struct Node *next;
} Node_t;

/**
 * \brief Initialize a hash table, which is in form of a pointer to pointer.
 * \note Caller must calls freeHashTable() after use.
 */
Node_t **initHashTable(int size) {
    Node_t **hashTable = (Node_t **)malloc(sizeof(Node_t *) * size);
    while (size--) {
        *(hashTable + size) = NULL;
    }
    return hashTable;
}

void freeHashTable(Node_t **hashTable, int size) {
    Node_t *cur, *next;
    while (size--) {
        cur = *(hashTable + size);
        while (cur) {
            next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(hashTable);
}

/**
 * The hash function macro.
 */
#define hash(num, numsSize) (((num) & ~0x80000000) % (numsSize))

void insert(Node_t **bucket, int idx, int num) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->idx = idx;
    new->val = num;
    new->next = NULL;
    if (!*bucket) {
        *bucket = new;
        return;
    }
    Node_t *cur = *bucket;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new;
}

int search(Node_t *head, int num, int *idx) {
    while (head) {
        if (head->val == num) {
            *idx = head->idx;
            return 1;
        }
        head = head->next;
    }
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    Node_t **hashTable = initHashTable(numsSize);
    int *ret = (int *)malloc(sizeof(int) * (*returnSize = 2)), cmp;
    for (int i = 0; i < numsSize; i++) {
        cmp = target - *nums;

        // Hash hit
        if (search(*(hashTable + hash(cmp, numsSize)), cmp, ret)) {
            *(ret + 1) = i;
            break;
        }

        // Hash miss
        insert(hashTable + hash(*nums, numsSize), i, *nums);
        nums++;
    }
    freeHashTable(hashTable, numsSize);
    return ret;
}
//
// End of the submission code
//

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]\n");
} 

int main() {
    struct {
        int nums[16], numsSize, target;
    } tc[] = {
        {.nums = {2,7,11,15}, .numsSize = 4, .target = 9},
        {.nums = {3,2,4}, .numsSize = 3, .target = 6},
        {.nums = {3,3}, .numsSize = 2, .target = 6}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    int *ret, retSize;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums =");

        // Output
        ret = twoSum(tc[i].nums, tc[i].numsSize, tc[i].target, &retSize);
        printArray(ret, retSize, "Output:");
        printf("\n");

        // Free up the returned array
        free(ret);
    }

    return 0;
}
