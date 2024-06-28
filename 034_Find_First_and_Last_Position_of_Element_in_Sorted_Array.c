#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
    int i = 0, j = numsSize - 1, k;
    int *ret = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;

    // Search the target value in nums
    while (i <= j) {
        k = i + j >> 1;
        if (target > nums[k]) {
            i = k + 1;
        } else if (target < nums[k]) {
            j = k - 1;
        } else {
            ret[0] = ret[1] = k;

            // Search the starting position
            while (i != ret[0]) {
                k = i + ret[0] >> 1;
                if (target != nums[k]) {
                    i = k + 1;
                } else {
                    ret[0] = k;
                }
            }

            // Search the ending position
            while (j != ret[1]) {
                k = j + ret[1] + 1 >> 1;
                if (target != nums[k]) {
                    j = k - 1;
                } else {
                    ret[1] = k;
                }
            }
            return ret;
        }
    }

    // No value matches
    ret[0] = ret[1] = -1;
    return ret;
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s[", name);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]");
}

int main() {
    struct {
        int nums[16], numsSize, target;
    } tc[] = {
        {.nums = {5,7,7,8,8,10}, .numsSize = 6, .target = 8},
        {.nums = {5,7,7,8,8,10}, .numsSize = 6, .target = 6},
        {.numsSize = 0, .target = 0}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    int *out, outSize;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums = ");
        printf(", target = %d\n", tc[i].target);

        // Output
        out = searchRange(tc[i].nums, tc[i].numsSize, tc[i].target, &outSize);
        printArray(out, outSize, "Output: ");
        printf("\n\n");

        free(out);
    }

    return 0;
}
