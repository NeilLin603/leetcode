#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *ret = (int *)malloc(2 * sizeof(int)), sum;
    ret[0] = 1;
    ret[1] = numsSize;
    while (ret[0] < ret[1]) {
        sum = *(nums + ret[0] - 1) + *(nums + ret[1] - 1);
        if (sum < target) {
            ret[0]++;
        } else if (sum > target) {
            ret[1]--;
        } else {
            *returnSize = 2;
            return ret;
        }
    }
    free(ret);
    *returnSize = 0;
    return NULL;
}

void printArray(int *nums, int numsSize, char *name) {
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
        int nums[10], numsSize, target;
    } tc[] = {
        {.nums = {2,7,11,15}, .numsSize = 4, .target = 9},
        {.nums = {2,3,4}, .numsSize = 3, .target = 6},
        {.nums = {-1,0}, .numsSize = 2, .target = -1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    int *output, returnSize;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: numbers");
        printf(", target = %d\n", tc[i].target);

        // Output
        output = twoSum(tc[i].nums, tc[i].numsSize, tc[i].target, &returnSize);
        printArray(output, returnSize, "Output");
        printf("\n\n");

        // Free memory
        if (returnSize) {
            free(output);
        }
    }

    return 0;
}
