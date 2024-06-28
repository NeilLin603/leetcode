#include <stdio.h>

//! ****************************************************************************
//! Solving concept:
//! Find the middle two nodes in the array, then select the greater one as the
//! new boundary point. Recursively find out the peak point.
//!
//! Example 2:
//! index   0   1   2   3   4   5   6
//! value
//! 6                           *
//! 5                       *
//! 4                               *
//! 3                  [*]
//! 2           *
//! 1       *      (*)
//!
//! [*] is greater than (*), which denotes it's climbing from (*) to [*] at the
//! middle of series. So we choose index 3 as the new lower bound. By using this
//! approach to narrow down the series recursively. Eventually the peak value at
//! index 5 shall be found out.
//! ****************************************************************************
#if 0 /* Recursion */
int findPeakElement(int *nums, int numsSize) {
    if (numsSize == 1) {
        return 0;
    }
    if (numsSize == 2) {
        return *nums > nums[1] ? 0 : 1;
    }
    int i = numsSize >> 1;
    return nums[i - 1] >= nums[i] ? findPeakElement(nums, i) :
                                    findPeakElement(nums + i, numsSize - i) + i;
}
#else /* Iteration (convert from recursion to improve speed) */
int findPeakElement(int *nums, int numsSize) {
    int i, index = 0;
    while (numsSize > 2) {
        i = numsSize >> 1;
        if (nums[i - 1] >= nums[i]) {
            numsSize = i;
        } else {
            nums += i;
            numsSize -= i;
            index += i;
        }
    }
    return numsSize == 1 || *nums > nums[1] ? index : index + 1;
}
#endif

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
        {.nums = {1,2,3,1}, .numsSize = 4},
        {.nums = {1,2,1,3,5,6,4}, .numsSize = 7}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input :nums");
        printf("Output: %d\n\n", findPeakElement(tc[i].nums, tc[i].numsSize));
    }

    return 0;
}
