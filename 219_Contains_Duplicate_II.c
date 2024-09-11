#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//
// Start of the submission code
//
/**
 * Definition of a list node.
 */
typedef struct Node {
    int index,
        value;
    struct Node *next;
} Node_t;

/**
 * Hash function macro.
 */
#define hash(num, size) (((num) + 1000000000) % (size))

Node_t **initTable(int size) {
    Node_t **table = (Node_t **)malloc(sizeof(Node_t *) * size);
    while (size--) {
        *(table + size) = NULL;
    }
    return table;
}

void freeTable(Node_t **table, int size) {
    Node_t *head, *tmp;
    while (size--) {
        head = *(table + size);
        while (head) {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
    }
    free(table);
}

bool containsNearbyDuplicate(int *nums, int numsSize, int k) {
    Node_t **table = initTable(numsSize), *pre, *cur;
    int hashVal;
    for (int i = 0; i < numsSize; i++) {
        // Look up hash table (traverse the list of the hashed bucket)
        hashVal = hash(*(nums + i), numsSize);
        cur = *(table + hashVal);
        pre = NULL;
        while (cur) {
            // If hash hit and the index diff <= k => free table and return true
            if (cur->value == *(nums + i) && i - cur->index <= k) {
                freeTable(table, numsSize);
                return true;
            }
            pre = cur;
            cur = cur->next;
        }

        // Hash miss => add the element to hash table
        if (pre) {
            cur = pre->next = (Node_t *)malloc(sizeof(Node_t));
        } else {
            cur = *(table + hashVal) = (Node_t *)malloc(sizeof(Node_t));
        }
        cur->index = i;
        cur->value = *(nums + i);
        cur->next = NULL;
    }
    freeTable(table, numsSize);
    return false;
}
//
// End of the submission code
//

void prinfArray(const int *nums, int numsSize, const char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]");
}

int main() {
    struct {
        int nums[8], numsSize, k;
    } tc[] = {
        {.nums = {1,2,3,1}, .numsSize = 4, .k = 3},
        {.nums = {1,0,1,1}, .numsSize = 4, .k = 1},
        {.nums = {1,2,3,1,2,3}, .numsSize = 6, .k = 2}
    };

    int tcSize = sizeof(tc) / sizeof(tc[0]);
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        prinfArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf(", k = %d\n", tc[i].k);

        // Output
        if (containsNearbyDuplicate(tc[i].nums, tc[i].numsSize, tc[i].k)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }
    return 0;
}
