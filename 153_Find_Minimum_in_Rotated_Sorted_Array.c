#include <stdio.h>

//! ****************************************************************************
//! Solving concept: compare the middle element and the last element in the
//! array. If the middle one is greater, the minimum element is at the second-
//! half part of the array (not include the middle one). Otherwise, the minimum
//! element is at the first-half part of the array (include the middle one).
//! Follow this approach to narrow down the array recursively. Eventually, the
//! array will be one element left, which is the minimum one.
//!
//! Example 1:
//! [3,4,5,1,2], 5 > 2 => [1,2], 1 < 2 => [1]
//!
//! Example 2:
//! [4,5,6,7,0,1,2], 7 > 2 => [0,1,2], 1 < 2 => [0,1], 0 < 1 => [0]
//!
//! Example 3:
//! [11,13,15,17], 13 < 17 => [11,13], 11 < 13 => [11]
//!
//! Time complexity: O(log n), Space complexity: O(log n)
//! ****************************************************************************
int findMin(int *nums, int numsSize) {
    numsSize -= 1;
    int k = numsSize >> 1;
    if (nums[k] < nums[numsSize]) {
        return findMin(nums, k + 1);
    } else if (nums[k] > nums[numsSize]) {
        return findMin(nums + k + 1, numsSize - k);
    } else {
        return *nums;
    }
}

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
        int nums[10], numsSize;
    } tc[] = {
        {.nums = {3,4,5,1,2}, .numsSize = 5},
        {.nums = {4,5,6,7,0,1,2}, .numsSize = 7},
        {.nums = {11,13,15,17}, .numsSize = 4}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf("Output: %d\n\n", findMin(tc[i].nums, tc[i].numsSize));
    }
    return 0;
}
