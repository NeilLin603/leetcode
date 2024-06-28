#include <stdio.h>

//! ****************************************************************************
//! Solving concept:
//! 1. Consider i = the first index, j = the last index, k = the middle index of
//!    the series.
//! 2. Check if the middle number (nums[k]) is greater than the first number
//!    (nums[i]). If so, then each number in the first-half series (index i~k)
//!    is strictly ascending. Otherwise, the second-half series (index k~j) is
//!    strictly ascending.
//! 3. Check if the target number is within the half series with ascending order
//!    If so, keep narrowing down this half of the series in the same way.
//!    Otherwise, search the other half of the series for the target.
//!
//! Time complexity: O(log n), Space complexity: O(1)
//! ****************************************************************************
int search(int *nums, int numsSize, int target) {
    int i = 0, j = numsSize - 1, k, cond1, cond2;
    while (i <= j) {
        k = i + j >> 1;
        if (target == nums[k]) {
            return k;
        }
        cond1 = nums[k] >= nums[i];
        cond2 = cond1 ? target >= nums[i] && target < nums[k] :
                        target > nums[k] && target <= nums[j];
        if (cond1 ^ cond2) {
            i = k + 1;
        } else {
            j = k - 1;
        }
    }
    return -1;
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s = [", name);
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
        {.nums = {4,5,6,7,0,1,2}, .numsSize = 7, .target = 0},
        {.nums = {4,5,6,7,0,1,2}, .numsSize = 7, .target = 3},
        {.nums = {1}, .numsSize = 1, .target = 0},
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input :nums");
        printf(", target = %d\n", tc[i].target);

        // Output
        printf("Output: %d\n\n",
               search(tc[i].nums, tc[i].numsSize, tc[i].target));
    }

    return 0;
}
