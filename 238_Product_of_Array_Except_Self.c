#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize;
    int *ret = (int *)malloc(sizeof(int) * numsSize), temp = *ret = 1;
    for (int i = 1; i < numsSize; i++) {
        ret[i] = ret[i - 1] * nums[i - 1];
    }
    for (int i = numsSize - 2; i >= 0; i--) {
        ret[i] *= temp *= nums[i + 1];
    }
    return ret;
}

// (1)  2   3   4   [24]
//  1  (2)  3   4   [12]
//  1   2  (3)  4    [8]
//  1   2   3  (4)   [6]

void printArray(int *nums, int numsSize, char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]\n");
}

int main() {
    struct {
        int nums[16], numsSize;
    } tc[] = {
        {.nums = {1,2,3,4}, .numsSize = 4},
        {.nums = {-1,1,0,-3,3}, .numsSize = 5}
    };
    int tcSize = sizeof(tc) / sizeof(*tc), *out, outSize;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        printArray(tc[i].nums, tc[i].numsSize, "Input: nums"); // Input

        // Output
        out = productExceptSelf(tc[i].nums, tc[i].numsSize, &outSize);
        printArray(out, outSize, "Output");
        printf("\n");

        free(out); // Free output
    }

    return 0;
}
